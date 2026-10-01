// Copyright (c) 2021 LootLocker

#include "LootLockerServerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4

#include "LootLockerServerConfig.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "HAL/PlatformMisc.h"
#include "Misc/Guid.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace
{
	/** Serialize a JSON object to a compact string. */
	FString SerializeJson(const TSharedRef<FJsonObject>& Object)
	{
		FString Out;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
		FJsonSerializer::Serialize(Object, Writer);
		return Out;
	}

	/** Parse a JSON string into an object. Returns an invalid pointer on failure. */
	TSharedPtr<FJsonObject> ParseJson(const FString& Body)
	{
		TSharedPtr<FJsonObject> Json;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Body);
		if (!FJsonSerializer::Deserialize(Reader, Json))
		{
			return nullptr;
		}
		return Json;
	}
}

// ─── Lifecycle ────────────────────────────────────────────────────────────────

bool FLootLockerServerTestGame::CreateGame(FLootLockerServerTestGame& OutGame, const FString& TestName)
{
	// Shortcut: use a pre-existing server key from an env var (no admin credentials needed).
	const FString EnvKey = FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_SERVER_KEY"));
	if (!EnvKey.IsEmpty())
	{
		OutGame.ServerKey    = EnvKey;
		OutGame.GameDomainKey =
			FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_SERVER_DOMAIN_KEY"));
		OutGame.GameId            = 0;
		OutGame.DevelopmentGameId = 0;
		OutGame.ActiveGameId      = 0;
		OutGame.bUsingEnvKey      = true;
		UE_LOG(LogTemp, Log,
			TEXT("LootLockerServerTestGame: Using LOOTLOCKER_SERVER_KEY env var (skipping game creation)"));
		return true;
	}

	if (!FLootLockerServerAdminRequest::EnsureSignedIn())
	{
		return false;
	}

	// ── Create game ──────────────────────────────────────────────────────────
	const FString GameName = FString::Printf(TEXT("%s-%s"),
		TestName.IsEmpty() ? TEXT("UE-Server-CI") : *TestName,
		*FGuid::NewGuid().ToString(EGuidFormats::Short));

	TSharedRef<FJsonObject> CreateGameBody = MakeShared<FJsonObject>();
	CreateGameBody->SetStringField(TEXT("name"),            GameName);
	CreateGameBody->SetNumberField(TEXT("genre"),           1);
	CreateGameBody->SetNumberField(TEXT("organisation_id"), FLootLockerServerAdminRequest::OrganisationId);

	const FLootLockerServerAdminResponse CreateGameResponse =
		FLootLockerServerAdminRequest::Send(TEXT("v1/game"), TEXT("POST"), SerializeJson(CreateGameBody));

	if (!CreateGameResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateGame failed (%d): %s"),
			CreateGameResponse.StatusCode, *CreateGameResponse.Body);
		return false;
	}

	TSharedPtr<FJsonObject> CreateGameJson = ParseJson(CreateGameResponse.Body);
	if (!CreateGameJson.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: Failed to parse CreateGame response"));
		return false;
	}

	const TSharedPtr<FJsonObject>* GameObj;
	if (!CreateGameJson->TryGetObjectField(TEXT("game"), GameObj))
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateGame response missing 'game' field"));
		return false;
	}

	(*GameObj)->TryGetNumberField(TEXT("id"),         OutGame.GameId);
	(*GameObj)->TryGetStringField(TEXT("name"),       OutGame.GameName);
	(*GameObj)->TryGetStringField(TEXT("domain_key"), OutGame.GameDomainKey);

	const TSharedPtr<FJsonObject>* DevObj;
	if ((*GameObj)->TryGetObjectField(TEXT("development"), DevObj) && DevObj->IsValid())
	{
		(*DevObj)->TryGetNumberField(TEXT("id"), OutGame.DevelopmentGameId);
	}

	UE_LOG(LogTemp, Log,
		TEXT("LootLockerServerTestGame: Created game '%s' (id=%d, dev_id=%d)"),
		*OutGame.GameName, OutGame.GameId, OutGame.DevelopmentGameId);

	// Tests always run against the stage / dev environment so that nothing touches
	// the production environment of the created game.
	OutGame.SwitchToStageEnvironment();

	// POST server/player refuses platforms that are not enabled for the game, and a
	// freshly created game has none enabled.
	if (!OutGame.EnsureGuestPlatformEnabled())
	{
		return false;
	}

	return true;
}

bool FLootLockerServerTestGame::DeleteGame()
{
	if (bUsingEnvKey)
	{
		UE_LOG(LogTemp, Log,
			TEXT("LootLockerServerTestGame: DeleteGame skipped (game supplied via LOOTLOCKER_SERVER_KEY)"));
		return true;
	}

	if (GameId == 0)
	{
		return true;
	}

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(
			FString::Printf(TEXT("v1/game/%d"), GameId), TEXT("DELETE"));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("LootLockerServerTestGame: DeleteGame failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Deleted game %d"), GameId);
	return true;
}

// ─── Credentials ──────────────────────────────────────────────────────────────

bool FLootLockerServerTestGame::CreateServerKey()
{
	if (bUsingEnvKey)
	{
		// ServerKey was already populated from the environment.
		return true;
	}

	if (ActiveGameId == 0)
	{
		UE_LOG(LogTemp, Error,
			TEXT("LootLockerServerTestGame: CreateServerKey called before a game was created"));
		return false;
	}

	TSharedRef<FJsonObject> KeyBody = MakeShared<FJsonObject>();
	KeyBody->SetStringField(TEXT("api_type"), TEXT("server"));
	KeyBody->SetStringField(TEXT("name"),     TEXT("ci-server"));

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(
			TEXT("game/#GAMEID#/api_keys"), TEXT("POST"), SerializeJson(KeyBody));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateServerKey failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	TSharedPtr<FJsonObject> Json = ParseJson(Response.Body);
	if (!Json.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: Failed to parse CreateServerKey response"));
		return false;
	}

	Json->TryGetStringField(TEXT("api_key"), ServerKey);
	if (ServerKey.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateServerKey response missing api_key"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Created server key for game %d"), ActiveGameId);
	return true;
}

// ─── Entity provisioning ──────────────────────────────────────────────────────

bool FLootLockerServerTestGame::EnsureGuestPlatformEnabled()
{
	if (ActiveGameId == 0)
	{
		UE_LOG(LogTemp, Error,
			TEXT("LootLockerServerTestGame: EnsureGuestPlatformEnabled called before a game was created"));
		return false;
	}

	// A freshly created game has no platforms enabled, and POST server/player rejects
	// any platform that is not enabled for the game.
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetBoolField(TEXT("enabled"), true);

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(
			FString::Printf(TEXT("game/#GAMEID#/platforms/%s"), *GuestPlatform),
			TEXT("PUT"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: EnsureGuestPlatformEnabled failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Enabled '%s' platform for game %d"),
		*GuestPlatform, ActiveGameId);
	return true;
}

bool FLootLockerServerTestGame::CreatePlayer(int32& OutPlayerId, FString& OutPlayerUlid, const FString& PlatformId)
{
	const FString EffectivePlatformId =
		PlatformId.IsEmpty() ? FGuid::NewGuid().ToString() : PlatformId;

	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("platform"),          GuestPlatform);
	Body->SetStringField(TEXT("player_identifier"), EffectivePlatformId);

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(TEXT("server/player"), TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreatePlayer failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	TSharedPtr<FJsonObject> Json = ParseJson(Response.Body);
	if (!Json.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: Failed to parse CreatePlayer response"));
		return false;
	}

	Json->TryGetNumberField(TEXT("player_id"),   OutPlayerId);
	Json->TryGetStringField(TEXT("player_ulid"), OutPlayerUlid);

	if (OutPlayerId == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreatePlayer response missing player_id"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Created player %d (%s)"),
		OutPlayerId, *OutPlayerUlid);
	return true;
}

bool FLootLockerServerTestGame::CreateLeaderboard(const FString& Key, const FString& Name, int32& OutLeaderboardId)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("key"),                     Key);
	Body->SetStringField(TEXT("name"),                    Name);
	Body->SetStringField(TEXT("direction_method"),        TEXT("descending"));
	Body->SetStringField(TEXT("type"),                    TEXT("player"));
	Body->SetBoolField(TEXT("enable_game_api_writes"),    true);
	Body->SetBoolField(TEXT("overwrite_score_on_submit"), true);

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(TEXT("server/leaderboards"), TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateLeaderboard failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	OutLeaderboardId = 0;
	if (TSharedPtr<FJsonObject> Json = ParseJson(Response.Body); Json.IsValid())
	{
		Json->TryGetNumberField(TEXT("id"), OutLeaderboardId);
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Created leaderboard '%s' (id=%d)"),
		*Key, OutLeaderboardId);
	return true;
}

bool FLootLockerServerTestGame::CreateTrigger(const FString& Name, int32 PlayerId)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("name"), Name);
	Body->SetNumberField(TEXT("player_id"), PlayerId);

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(TEXT("server/trigger"), TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateTrigger failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Created trigger '%s'"), *Name);
	return true;
}

bool FLootLockerServerTestGame::CreateCurrency(const FString& Name, const FString& Code, FString& OutCurrencyId)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("name"),                     Name);
	Body->SetStringField(TEXT("code"),                     Code);
	Body->SetNumberField(TEXT("game_id"),                  ActiveGameId);
	Body->SetStringField(TEXT("initial_denomination_name"), TEXT("Coin"));

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(TEXT("game/#GAMEID#/currencies/currency"),
			TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateCurrency failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	OutCurrencyId.Reset();
	if (TSharedPtr<FJsonObject> Json = ParseJson(Response.Body); Json.IsValid())
	{
		Json->TryGetStringField(TEXT("id"), OutCurrencyId);
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Created currency '%s' (%s)"), *Name, *Code);
	return true;
}

bool FLootLockerServerTestGame::CreateProgression(const FString& Key, const FString& Name, FString& OutProgressionId)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("key"),               Key);
	Body->SetStringField(TEXT("name"),              Name);
	Body->SetBoolField(TEXT("active"),              true);
	Body->SetBoolField(TEXT("allow_game_writes"),   true);
	Body->SetBoolField(TEXT("allow_api_writes"),    true);

	const FLootLockerServerAdminResponse Response =
		FLootLockerServerAdminRequest::Send(TEXT("game/#GAMEID#/progressions"),
			TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerServerTestGame: CreateProgression failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	OutProgressionId.Reset();
	if (TSharedPtr<FJsonObject> Json = ParseJson(Response.Body); Json.IsValid())
	{
		Json->TryGetStringField(TEXT("id"), OutProgressionId);
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerServerTestGame: Created progression '%s'"), *Key);
	return true;
}

// ─── SDK initialization ───────────────────────────────────────────────────────

void FLootLockerServerTestGame::InitializeLootLockerServerSDK() const
{
	ULootLockerServerConfig* Config = GetMutableDefault<ULootLockerServerConfig>();
	Config->LootLockerServerKey = ServerKey;
	Config->LootLockerDomainKey = GameDomainKey;
	if (Config->GameVersion.IsEmpty())
	{
		Config->GameVersion = TEXT("0.0.0.1");
	}
}

#endif // ENGINE_MAJOR_VERSION > 4
