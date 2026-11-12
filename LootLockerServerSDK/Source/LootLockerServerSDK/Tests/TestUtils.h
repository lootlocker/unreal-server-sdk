#pragma once

#include <chrono>
#include <future>

#include "CoreMinimal.h"
#include "HAL/PlatformMisc.h"
#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION > 4

#include "LootLockerServerConfig.h"
#include "LootLockerServerStateData.h"
#include "LootLockerServerTestGame.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerLeaderboardRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "ServerAPI/LootLockerServerTriggerRequest.h"

namespace test_util
{
	/** How long a synchronous helper waits for an SDK callback before giving up. */
	static constexpr int32 ResponseTimeoutSeconds = 60;

	template <typename ResponseType,typename DelegateType>
	static std::pair<std::promise<ResponseType>*,DelegateType> CreateDelegate()
	{
		std::promise<ResponseType>* ResponsePromise = new std::promise<ResponseType>();

		DelegateType Delegate =
			DelegateType::CreateLambda(
				[ResponsePromise](const ResponseType Response)
				{
					ResponsePromise->set_value(Response);
				});

		return make_pair(ResponsePromise,Delegate);
	}

	/**
	 * Wait up to TimeoutSeconds for the promise to be fulfilled, then return the value.
	 * On success the promise is deleted. On timeout the promise is intentionally leaked
	 * (the HTTP callback may still fire and call set_value on it later).
	 * Returns a default-constructed (success=false) ResponseType on timeout.
	 *
	 * A timed-out request is not cancelled, so its completion delegate can still run later and
	 * mutate shared session state (StartSession's inspector calls SetServerToken). Callers that
	 * write shared state from the callback must gate it on the current setup generation; see
	 * StartSession below.
	 */
	template <typename ResponseType>
	static ResponseType WaitAndGet(std::promise<ResponseType>* Promise, int32 TimeoutSeconds = ResponseTimeoutSeconds)
	{
		std::future<ResponseType> Future = Promise->get_future();
		if (Future.wait_for(std::chrono::seconds(TimeoutSeconds)) == std::future_status::timeout)
		{
			UE_LOG(LogTemp, Error,
				TEXT("test_util: SDK request timed out after %ds — the HTTP callback may still be in flight"),
				TimeoutSeconds);
			// Do NOT delete Promise: the in-flight callback may still call set_value.
			return ResponseType{};
		}
		ResponseType Result = Future.get();
		delete Promise;
		return Result;
	}

	/**
	 * Incremented for every StartSession attempt. A late callback from a timed-out attempt
	 * compares against this and skips writing the token, so it cannot authenticate the next
	 * test against the previous game.
	 */
	inline int32& SessionGeneration()
	{
		static int32 Generation = 0;
		return Generation;
	}

	/**
	 * Start a server session against the game currently configured in ULootLockerServerConfig.
	 * The server SDK authenticates with the server key, so there is no player login step here.
	 *
	 * Assumes ULootLockerServerConfig has been populated (for example by
	 * FLootLockerServerTestGame::InitializeLootLockerServerSDK()).
	 *
	 * @return true when a session token was obtained.
	 */
	inline bool StartSession()
	{
		// Allow a server key supplied through the environment to configure the SDK without
		// project settings. Tests that call InitializeLootLockerServerSDK() first do not
		// need this — the config is already set before StartSession() is reached.
		const FString EnvKey = FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_SERVER_KEY"));
		if (!EnvKey.IsEmpty())
		{
			ULootLockerServerConfig* Config = GetMutableDefault<ULootLockerServerConfig>();
			Config->LootLockerServerKey = EnvKey;
			if (Config->GameVersion.IsEmpty())
			{
				Config->GameVersion = TEXT("0.0.0.1");
			}
			const FString DomainKey =
				FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_SERVER_DOMAIN_KEY"));
			if (!DomainKey.IsEmpty())
			{
				Config->LootLockerDomainKey = DomainKey;
			}
		}

		// Drop any token left over from a previous test so it cannot mask a provisioning
		// failure by authenticating against the wrong game.
		ULootLockerServerStateData::ClearState();

		const auto [Promise, Delegate] =
			CreateDelegate<FLootLockerServerAuthenticationResponse, FLootLockerServerAuthResponseDelegate>();

		// Copy out of the structured binding: C++17 does not allow capturing a structured binding
		// in a lambda, and UE 5.0/5.2 compile this header as C++17.
		FLootLockerServerAuthResponseDelegate InnerDelegate = Delegate;

		// Capture the generation for this attempt. A late callback from a timed-out attempt sees a
		// newer generation and must not write the token, or the next test would authenticate
		// against the previous game.
		const int32 AttemptGeneration = ++SessionGeneration();
		FLootLockerServerAuthResponseDelegate GatedDelegate =
			FLootLockerServerAuthResponseDelegate::CreateLambda(
				[InnerDelegate, AttemptGeneration](const FLootLockerServerAuthenticationResponse Response)
				{
					if (SessionGeneration() != AttemptGeneration)
					{
						UE_LOG(LogTemp, Warning,
							TEXT("test_util: ignoring a late session response from a superseded setup attempt"));
						return;
					}
					InnerDelegate.ExecuteIfBound(Response);
				});

		ULootLockerServerAuthRequest::StartSession(GatedDelegate);

		const FLootLockerServerAuthenticationResponse Response = WaitAndGet(Promise);
		if (!Response.Success)
		{
			UE_LOG(LogTemp, Error, TEXT("test_util: StartSession failed"));
			return false;
		}
		return !Response.Token.IsEmpty();
	}

	/**
	 * Discard the current server session token.
	 *
	 * The server SDK exposes no end-session endpoint (server sessions expire on their
	 * own), so this only clears local state.
	 */
	inline void EndSession()
	{
		ULootLockerServerStateData::ClearState();
	}

	/**
	 * Provision an isolated game and bring the SDK up against it.
	 *
	 * On success Game holds a valid, fully provisioned game with a server key and the
	 * SDK is configured and authenticated, ready for tests to run. On failure the
	 * caller should report the error and skip the test body — check Game.IsValid().
	 *
	 * Always pair with Game.DeleteGame() in teardown.
	 */
	inline bool SetupTestGame(FLootLockerServerTestGame& Game, const FString& TestName)
	{
		// Game is reused across every LatentIt in a spec, so a previous test's success must not
		// leak into this one: clear the flag before setup so a failure below leaves IsValid() false.
		Game.bSetupComplete = false;

		if (!FLootLockerServerTestGame::CreateGame(Game, TestName))
		{
			UE_LOG(LogTemp, Error, TEXT("test_util: CreateGame failed for '%s'"), *TestName);
			return false;
		}

		if (!Game.CreateServerKey())
		{
			return false;
		}

		Game.InitializeLootLockerServerSDK();

		if (!StartSession())
		{
			return false;
		}

		// Only now is the game usable by a test body. Kept separate from the game
		// identity so teardown can still delete a game whose later steps failed.
		Game.bSetupComplete = true;
		return true;
	}

	// ─── Server-API entity helpers ────────────────────────────────────────────
	//
	// These go through the SDK's own transport (and therefore the server session),
	// unlike FLootLockerServerTestGame's admin-API helpers.

	/**
	 * Create a player through the server API.
	 * Requires a started session and the guest platform enabled on the game.
	 *
	 * @param OutPlayerId    Populated with the numeric legacy player ID.
	 * @param OutPlayerUlid  Populated with the player ULID.
	 * @param PlatformId     Optional platform player identifier; a GUID is generated when empty.
	 */
	inline bool CreatePlayer(int32& OutPlayerId, FString& OutPlayerUlid, const FString& PlatformId = TEXT(""))
	{
		const FString EffectivePlatformId =
			PlatformId.IsEmpty() ? FGuid::NewGuid().ToString() : PlatformId;

		const auto [Promise, Delegate] =
			CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

		ULootLockerServerPlayerRequest::CreatePlayer(
			ELootLockerServerCreatePlayerPlatforms::Guest, EffectivePlatformId, Delegate);

		const FLootLockerServerCreatePlayerResponse Response = WaitAndGet(Promise);
		if (!Response.Success || Response.Player_id == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("test_util: CreatePlayer failed (%d): %s"),
				Response.StatusCode, *Response.FullTextFromServer);
			return false;
		}

		OutPlayerId = Response.Player_id;
		OutPlayerUlid = Response.Player_ulid;
		return true;
	}

	/**
	 * Create a leaderboard through the server API.
	 * Requires a started session.
	 *
	 * @param Key   Unique leaderboard key. Only a-z, 0-9 and underscores are allowed.
	 * @param Name  Display name.
	 */
	inline bool CreateLeaderboard(const FString& Key, const FString& Name)
	{
		FLootLockerServerCreateLeaderboardRequest Request;
		Request.Key = Key;
		Request.Name = Name;
		Request.Type = ELootLockerServerLeaderboardType::player;
		Request.Direction_method = ELootLockerServerLeaderboardDirection::descending;
		Request.Enable_game_api_writes = true;
		Request.Overwrite_score_on_submit = true;

		const auto [Promise, Delegate] =
			CreateDelegate<FLootLockerServerCreateLeaderboardResponse, FLootLockerServerCreateLeaderboardResponseDelegate>();

		ULootLockerServerLeaderboardRequest::CreateLeaderboard(Request, Delegate);

		const FLootLockerServerCreateLeaderboardResponse Response = WaitAndGet(Promise);
		if (!Response.Success)
		{
			UE_LOG(LogTemp, Error, TEXT("test_util: CreateLeaderboard '%s' failed (%d): %s"),
				*Key, Response.StatusCode, *Response.FullTextFromServer);
			return false;
		}
		return true;
	}

	/**
	 * Delete a leaderboard through the server API.
	 * Requires a started session.
	 */
	inline bool DeleteLeaderboard(const FString& Key)
	{
		const auto [Promise, Delegate] =
			CreateDelegate<FLootLockerServerResponse, FLootLockerServerDeleteLeaderboardResponseDelegate>();

		ULootLockerServerLeaderboardRequest::DeleteLeaderboard(Key, Delegate);

		const FLootLockerServerResponse Response = WaitAndGet(Promise);
		if (!Response.Success)
		{
			UE_LOG(LogTemp, Error, TEXT("test_util: DeleteLeaderboard '%s' failed (%d): %s"),
				*Key, Response.StatusCode, *Response.FullTextFromServer);
			return false;
		}
		return true;
	}

	/**
	 * Invoke a trigger for a player through the server API.
	 * Requires a started session. Triggers are fire-and-forget: a success response
	 * does not imply any reward was granted.
	 */
	inline bool InvokeTriggerForPlayer(const FString& TriggerName, int32 PlayerId)
	{
		const auto [Promise, Delegate] =
			CreateDelegate<FLootLockerServerInvokeTriggerResponse, FLootLockerServerInvokeTriggerResponseDelegate>();

		ULootLockerServerTriggerRequest::InvokeTriggerForPlayer(TriggerName, PlayerId, Delegate);

		const FLootLockerServerInvokeTriggerResponse Response = WaitAndGet(Promise);
		if (!Response.Success)
		{
			UE_LOG(LogTemp, Error, TEXT("test_util: InvokeTriggerForPlayer '%s' failed (%d): %s"),
				*TriggerName, Response.StatusCode, *Response.FullTextFromServer);
			return false;
		}
		return true;
	}
}
#endif
