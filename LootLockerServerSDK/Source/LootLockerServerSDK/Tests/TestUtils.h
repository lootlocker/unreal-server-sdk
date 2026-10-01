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

		ULootLockerServerAuthRequest::StartSession(Delegate);

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

		return true;
	}
}
#endif
