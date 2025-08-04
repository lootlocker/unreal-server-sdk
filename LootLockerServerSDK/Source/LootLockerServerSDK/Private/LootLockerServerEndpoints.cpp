// Copyright (c) 2021 LootLocker

#include "LootLockerServerEndpoints.h"

#ifdef LOOTLOCKER_USE_STAGE_URL
FString ULootLockerServerEndpoints::GameBaseUrl = "https://{domainKey}api.stage.internal.dev.lootlocker.cloud/";
#else
FString ULootLockerServerEndpoints::GameBaseUrl = "https://{domainKey}api.lootlocker.com/";
#endif
FString ULootLockerServerEndpoints::ServerApiUrlSuffix = "server/";
FString ULootLockerServerEndpoints::ClientApiUrlSuffix = "client/";

//Auth
FLootLockerServerEndPoint ULootLockerServerEndpoints::StartSession = InitEndpoint("session", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MaintainingSession = InitEndpoint("ping", ELootLockerServerHTTPMethod::GET);

//Leaderboards
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListLeaderboards = InitEndpoint("leaderboards", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateLeaderboard = InitEndpoint("leaderboards", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubmitScore = InitEndpoint("leaderboards/{0}/submit", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAllMemberRanks = InitEndpoint("leaderboards/member/{0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetScoresFromLeaderboard = InitEndpoint("leaderboards/{0}/list", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListLeaderboardArchive = InitEndpoint("leaderboards/{0}/archive/list", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetLeaderboardArchive = InitEndpoint("leaderboards/archive/read", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetLeaderboardSchedule = InitEndpoint("leaderboards/{0}/schedule", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateLeaderboardSchedule = InitEndpoint("leaderboards/{0}/schedule", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteLeaderboardSchedule = InitEndpoint("leaderboards/{0}/schedule", ELootLockerServerHTTPMethod::DELETE);

// Assets
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAssets = InitEndpoint("assets", ELootLockerServerHTTPMethod::GET);

// Asset Instances
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairs = InitEndpoint("player/{0}/assets/instances/{1}/storage", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairById = InitEndpoint("player/{0}/assets/instances/{1}/storage/{2}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddKeyValuePairToAssetInstance = InitEndpoint("player/{0}/assets/instances/{1}/storage", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateKeyValuePairs = InitEndpoint("player/{0}/assets/instances/{1}/storage", ELootLockerServerHTTPMethod::PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateKeyValuePairById = InitEndpoint("player/{0}/assets/instances/{1}/storage/{2}", ELootLockerServerHTTPMethod::PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteKeyValuePairById = InitEndpoint("player/{0}/assets/instances/{1}/storage/{2}", ELootLockerServerHTTPMethod::DELETE);

//Asset Instance Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAllInstanceProgressions = InitEndpoint("players/{0}/assets/instances/{1}/progressions", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetSingleInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddPointsToInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}/points/add", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubtractPointsFromInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}/points/subtract", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ResetInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}/reset", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}", ELootLockerServerHTTPMethod::DELETE);

// Droptables
FLootLockerServerEndPoint ULootLockerServerEndpoints::ComputeAndLockDropTable = InitEndpoint("player/{0}/droptables/{1}/compute", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::PickDropsFromDropTable = InitEndpoint("player/{0}/droptables/{1}/pick", ELootLockerServerHTTPMethod::POST);

//Player Lookup
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerInfoFromGameSessionToken = InitEndpoint("player/info/token", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::LookupMultiplePlayerNamesUsingIDs = InitEndpoint("players/lookup/name", ELootLockerServerHTTPMethod::GET);

//Player Inventory
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetUniversalInventory = InitEndpoint("inventory/universal", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerInventory = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddAssetToPlayerInventory = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AlterPlayerInventory = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::PATCH);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerLoadout = InitEndpoint("player/{0}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToPlayerLoadout = InitEndpoint("player/{0}/loadout", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnEquipAssetFromPlayerLoadout = InitEndpoint("player/{0}/loadout/{1}", ELootLockerServerHTTPMethod::DELETE);

//Player persistent storage
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerPersistentStorage = InitEndpoint("players/storage", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetMultiplePlayersPublicPersistentStorageValues = InitEndpoint("players/storage/lookup", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdatePlayerPersistentStorage = InitEndpoint("players/storage", ELootLockerServerHTTPMethod::PATCH);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeletePlayerPersistentStorage = InitEndpoint("players/storage", ELootLockerServerHTTPMethod::DELETE);

//Player Files
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListPlayerFiles = InitEndpoint("players/{0}/files", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerFileById = InitEndpoint("players/{0}/files/{1}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeletePlayerFile = InitEndpoint("players/{0}/files/{1}", ELootLockerServerHTTPMethod::DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UploadPlayerFile = InitEndpoint("players/{0}/files", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdatePlayerFile = InitEndpoint("players/{0}/files/{1}", ELootLockerServerHTTPMethod::PUT);

//Triggers
FLootLockerServerEndPoint ULootLockerServerEndpoints::InvokeTriggerForPlayer = InitEndpoint("trigger", ELootLockerServerHTTPMethod::POST);

// Characters
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerCharacters = InitEndpoint("player/{0}/characters", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetCharacterInventory = InitEndpoint("player/{0}/characters/{1}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnequipAssetFromCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout/{2}", ELootLockerServerHTTPMethod::DELETE);

// Heroes
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerHeroes = InitEndpoint("player/{0}/heroes", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetHeroInventory = InitEndpoint("player/{0}/heroes/{1}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnequipAssetFromHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout/{2}", ELootLockerServerHTTPMethod::DELETE);

// Purchases
FLootLockerServerEndPoint ULootLockerServerEndpoints::CheckPurchaseStatus = InitEndpoint("player/{0}/purhcase/{1}", ELootLockerServerHTTPMethod::GET);

// Game Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAllProgressions = InitEndpoint("progressions", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgression = InitEndpoint("progressions/{0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionTiers = InitEndpoint("progressions/{0}/tiers", ELootLockerServerHTTPMethod::GET);

// Player Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsForPlayer = InitEndpoint("players/{0}/progressions", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsByKeyForPlayer = InitEndpoint("players/{0}/progressions/{1}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddPointsToProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}/points/add", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubtractPointsFromProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}/points/subtract", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ResetProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}/reset", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}", ELootLockerServerHTTPMethod::DELETE);

// Character Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsByKeyForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddPointsToProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}/points/add", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubtractPointsFromProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}/points/subtract", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ResetProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}/reset", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}", ELootLockerServerHTTPMethod::DELETE);

// Currencies
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListCurrencies = InitEndpoint("currencies", ELootLockerServerHTTPMethod::GET);

// Balances
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListBalancesInWallet = InitEndpoint("balances/wallet/{0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetWalletByWalletId = InitEndpoint("wallet/{0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetWalletByHolderId = InitEndpoint("wallet/holder/{0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreditBalanceToWallet = InitEndpoint("balances/credit", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DebitBalanceToWallet = InitEndpoint("balances/debit", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateWallet = InitEndpoint("wallet", ELootLockerServerHTTPMethod::POST);

// Metadata
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListMetadata = InitEndpoint("metadata/source/{0}/id/{1}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MetadataActions = InitEndpoint("metadata/", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetMultisourceMetadata = InitEndpoint("metadata/multisource", ELootLockerServerHTTPMethod::POST);

// Token Exchange
FLootLockerServerEndPoint ULootLockerServerEndpoints::TokenExchange = InitEndpoint("v3/oauth/token", ELootLockerServerHTTPMethod::POST, ClientApiUrlSuffix);

// Notifications
FLootLockerServerEndPoint ULootLockerServerEndpoints::SendNotification = InitEndpoint("notifications/v1", ELootLockerServerHTTPMethod::POST);

FLootLockerServerEndPoint ULootLockerServerEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method, const FString& BaseUrlSuffix /* = ServerApiUrlSuffix*/)
{
	FLootLockerServerEndPoint Result;
	Result.endpoint = GameBaseUrl + BaseUrlSuffix + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
