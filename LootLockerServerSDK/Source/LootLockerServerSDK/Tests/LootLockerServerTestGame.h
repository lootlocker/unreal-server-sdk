// Copyright (c) 2021 LootLocker

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION > 4

#include "CoreMinimal.h"
#include "LootLockerServerAdminRequest.h"

/**
 * Credentials and metadata for a single admin-provisioned test game.
 *
 * The server SDK authenticates with a *server* API key (sent as the x-server-key
 * header), not a game key plus guest login. Provisioning therefore differs from the
 * game SDK's FLootLockerTestGame: a server key must be created explicitly via the
 * admin API before the SDK can be pointed at the game.
 *
 * Usage pattern:
 *
 *   // --- Setup ---
 *   FLootLockerServerTestGame Game;
 *   bool bOk = FLootLockerServerTestGame::CreateGame(Game, TEXT("MyTest"));
 *   bOk = bOk && Game.CreateServerKey();
 *   // Provision any feature-specific entities:
 *   bOk = bOk && Game.CreateLeaderboard(TEXT("my_lb"), TEXT("My Leaderboard"));
 *   Game.InitializeLootLockerServerSDK();   // points the SDK at the provisioned game
 *   test_util::StartSession();              // regular server session
 *
 *   // --- Teardown (always, even on failure) ---
 *   Game.DeleteGame();
 *
 * Environment-variable shortcut:
 *   If LOOTLOCKER_SERVER_KEY is set, CreateGame() skips admin provisioning and uses
 *   that key directly. DeleteGame() is a no-op in this case. Pair with
 *   LOOTLOCKER_SERVER_DOMAIN_KEY if the game has a domain key configured.
 */
struct FLootLockerServerTestGame
{
	// ─── Prod game ───────────────────────────────────────────────────────────
	int32   GameId = 0;
	FString GameName;
	FString GameDomainKey;

	// ─── Dev / stage game ────────────────────────────────────────────────────
	int32   DevelopmentGameId = 0;

	// ─── Active context (switches between prod and dev) ──────────────────────
	int32 ActiveGameId = 0;

	/** The server API key used to authenticate SDK calls against this game. */
	FString ServerKey;

	/** True when the game was supplied via LOOTLOCKER_SERVER_KEY rather than provisioned. */
	bool bUsingEnvKey = false;

	/** Platform used when provisioning players. */
	FString GuestPlatform = TEXT("guest");

	bool IsValid() const { return GameId != 0 || bUsingEnvKey; }

	void SwitchToProdEnvironment()
	{
		ActiveGameId = GameId;
		FLootLockerServerAdminRequest::ActiveGameId = GameId;
	}

	void SwitchToStageEnvironment()
	{
		ActiveGameId = DevelopmentGameId;
		FLootLockerServerAdminRequest::ActiveGameId = DevelopmentGameId;
	}

	// ─── Lifecycle ────────────────────────────────────────────────────────────

	/**
	 * Create an isolated test game via the admin API and populate OutGame.
	 *
	 * If LOOTLOCKER_SERVER_KEY is set the admin API is not called — that key is used
	 * directly and DeleteGame() becomes a no-op. Pair with
	 * LOOTLOCKER_SERVER_DOMAIN_KEY for the domain key.
	 *
	 * @param OutGame   Populated on success.
	 * @param TestName  Optional label embedded in the generated game name.
	 * @return false if sign-in or game creation fails.
	 */
	static bool CreateGame(FLootLockerServerTestGame& OutGame, const FString& TestName = TEXT(""));

	/**
	 * Delete this game via the admin API.
	 * Safe to call even when setup partially failed. Always call in test teardown.
	 * No-op when the game was supplied via LOOTLOCKER_SERVER_KEY.
	 */
	bool DeleteGame();

	// ─── Credentials ──────────────────────────────────────────────────────────

	/**
	 * Create a server API key for the active game and store it in ServerKey.
	 * Must be called after CreateGame() and before InitializeLootLockerServerSDK().
	 */
	bool CreateServerKey();

	/**
	 * Enable the guest platform for the active game.
	 *
	 * A freshly created game has no platforms enabled, and POST server/player rejects
	 * any platform that is not enabled for the game. CreateGame() calls this
	 * automatically for the stage game.
	 */
	bool EnsureGuestPlatformEnabled();

	// ─── Entity provisioning ──────────────────────────────────────────────────

	/**
	 * Create a player via the server API and return its identifiers.
	 * Requires a valid session (call test_util::StartSession() first).
	 * The guest platform must be enabled — see EnsureGuestPlatformEnabled().
	 *
	 * @param OutPlayerId    Populated with the numeric legacy player ID.
	 * @param OutPlayerUlid  Populated with the player ULID.
	 * @param PlatformId     Optional platform player identifier; a GUID is generated when empty.
	 */
	bool CreatePlayer(int32& OutPlayerId, FString& OutPlayerUlid, const FString& PlatformId = TEXT(""));

	/**
	 * Create a leaderboard via the server API.
	 * Requires a valid session (call test_util::StartSession() first).
	 *
	 * @param Key              Unique leaderboard key. Only a-z, 0-9 and underscores are allowed.
	 * @param Name             Display name.
	 * @param OutLeaderboardId Populated with the created leaderboard's numeric ID.
	 */
	bool CreateLeaderboard(const FString& Key, const FString& Name, int32& OutLeaderboardId);

	/**
	 * Create a trigger via the server API.
	 * Requires a valid session (call test_util::StartSession() first).
	 *
	 * @param Name      Display name.
	 * @param PlayerId  Numeric player ID the trigger is scoped to.
	 */
	bool CreateTrigger(const FString& Name, int32 PlayerId);

	/**
	 * Create a virtual currency via the admin API. Currency codes must be 1-3
	 * lowercase letters or digits.
	 *
	 * @param OutCurrencyId  Populated with the created currency's ULID.
	 */
	bool CreateCurrency(const FString& Name, const FString& Code, FString& OutCurrencyId);

	/**
	 * Create a progression via the admin API, with both game and API writes allowed.
	 *
	 * @param OutProgressionId  Populated with the created progression's ULID.
	 */
	bool CreateProgression(const FString& Key, const FString& Name, FString& OutProgressionId);

	// ─── SDK initialization ───────────────────────────────────────────────────

	/**
	 * Configure ULootLockerServerConfig with this game's credentials so that subsequent
	 * SDK calls target the provisioned game.
	 * Call this after CreateServerKey(), before test_util::StartSession().
	 */
	void InitializeLootLockerServerSDK() const;
};

#endif // ENGINE_MAJOR_VERSION > 4
