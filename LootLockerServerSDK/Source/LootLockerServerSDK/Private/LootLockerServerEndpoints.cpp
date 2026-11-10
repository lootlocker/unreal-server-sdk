// Copyright (c) 2021 LootLocker

#include "LootLockerServerEndpoints.h"

#ifdef LOOTLOCKER_USE_LOCAL_DEVENV
FString ULootLockerServerEndpoints::GameBaseUrl = "http://localhost:8080/";
#else
FString ULootLockerServerEndpoints::GameBaseUrl = "https://{domainKey}api.lootlocker.com/";
#endif
FString ULootLockerServerEndpoints::ServerApiUrlSuffix = "server/";
FString ULootLockerServerEndpoints::ClientApiUrlSuffix = "client/";

//Auth
FLootLockerServerEndPoint ULootLockerServerEndpoints::StartSession = InitEndpoint("session", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MaintainingSession = InitEndpoint("ping", ELootLockerServerHTTPMethod::LL_GET);

//Leaderboards
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListLeaderboards = InitEndpoint("leaderboards", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateLeaderboard = InitEndpoint("leaderboards", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::LL_PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::LL_DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubmitScore = InitEndpoint("leaderboards/{0}/submit", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::IncrementScore = InitEndpoint("leaderboards/{0}/increment", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAllMemberRanks = InitEndpoint("leaderboards/member/{0}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetScoresFromLeaderboard = InitEndpoint("leaderboards/{0}/list", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListLeaderboardArchive = InitEndpoint("leaderboards/{0}/archive/list", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetLeaderboardArchive = InitEndpoint("leaderboards/archive/read", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetLeaderboardSchedule = InitEndpoint("leaderboards/{0}/schedule", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateLeaderboardSchedule = InitEndpoint("leaderboards/{0}/schedule", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteLeaderboardSchedule = InitEndpoint("leaderboards/{0}/schedule", ELootLockerServerHTTPMethod::LL_DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::RequestManualLeaderboardReset = InitEndpoint("leaderboards/{0}/reset", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListManualLeaderboardResets = InitEndpoint("leaderboards/{0}/reset", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetManualLeaderboardReset = InitEndpoint("leaderboards/{0}/reset/{1}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CancelManualLeaderboardReset = InitEndpoint("leaderboards/{0}/reset/{1}", ELootLockerServerHTTPMethod::LL_DELETE);

// Assets
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAssets = InitEndpoint("assets", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListAssets = InitEndpoint("assets/artful-alpaca/v1", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListContexts = InitEndpoint("contexts/v1", ELootLockerServerHTTPMethod::LL_GET);

// Asset Instances
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairs = InitEndpoint("player/{0}/assets/instances/{1}/storage", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairById = InitEndpoint("player/{0}/assets/instances/{1}/storage/{2}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddKeyValuePairToAssetInstance = InitEndpoint("player/{0}/assets/instances/{1}/storage", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateKeyValuePairs = InitEndpoint("player/{0}/assets/instances/{1}/storage", ELootLockerServerHTTPMethod::LL_PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateKeyValuePairById = InitEndpoint("player/{0}/assets/instances/{1}/storage/{2}", ELootLockerServerHTTPMethod::LL_PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteKeyValuePairById = InitEndpoint("player/{0}/assets/instances/{1}/storage/{2}", ELootLockerServerHTTPMethod::LL_DELETE);

//Asset Instance Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAllInstanceProgressions = InitEndpoint("players/{0}/assets/instances/{1}/progressions", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetSingleInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddPointsToInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}/points/add", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubtractPointsFromInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}/points/subtract", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ResetInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}/reset", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteInstanceProgression = InitEndpoint("players/{0}/assets/instances/{1}/progressions/{2}", ELootLockerServerHTTPMethod::LL_DELETE);

// Droptables
FLootLockerServerEndPoint ULootLockerServerEndpoints::ComputeAndLockDropTable = InitEndpoint("player/{0}/droptables/{1}/compute", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::PickDropsFromDropTable = InitEndpoint("player/{0}/droptables/{1}/pick", ELootLockerServerHTTPMethod::LL_POST);

// Friends
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListFriends = InitEndpoint("player/friends/{0}", ELootLockerServerHTTPMethod::LL_GET);

// Player Operations
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreatePlayer = InitEndpoint("player", ELootLockerServerHTTPMethod::LL_POST);

//Player Lookup
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerInfoFromGameSessionToken = InitEndpoint("player/info/token", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::LookupMultiplePlayerNamesUsingIDs = InitEndpoint("players/lookup/name", ELootLockerServerHTTPMethod::LL_GET);

// Connected Accounts
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListConnectedAccounts = InitEndpoint("connected-accounts/v1/list", ELootLockerServerHTTPMethod::LL_POST);

//Player Inventory
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetUniversalInventory = InitEndpoint("inventory/universal", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerInventory = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddAssetToPlayerInventory = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AlterPlayerInventory = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::LL_PATCH);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerLoadout = InitEndpoint("player/{0}/loadout", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToPlayerLoadout = InitEndpoint("player/{0}/loadout", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnEquipAssetFromPlayerLoadout = InitEndpoint("player/{0}/loadout/{1}", ELootLockerServerHTTPMethod::LL_DELETE);

//Player persistent storage
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerPersistentStorage = InitEndpoint("players/storage", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetMultiplePlayersPublicPersistentStorageValues = InitEndpoint("players/storage/lookup", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdatePlayerPersistentStorage = InitEndpoint("players/storage", ELootLockerServerHTTPMethod::LL_PATCH);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeletePlayerPersistentStorage = InitEndpoint("players/storage", ELootLockerServerHTTPMethod::LL_DELETE);

//Player Files
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListPlayerFiles = InitEndpoint("players/{0}/files", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerFileById = InitEndpoint("players/{0}/files/{1}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeletePlayerFile = InitEndpoint("players/{0}/files/{1}", ELootLockerServerHTTPMethod::LL_DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UploadPlayerFile = InitEndpoint("players/{0}/files", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdatePlayerFile = InitEndpoint("players/{0}/files/{1}", ELootLockerServerHTTPMethod::LL_PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListPlayerFileRevisions = InitEndpoint("players/{0}/files/{1}/revisions", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerFileRevision = InitEndpoint("players/{0}/files/{1}/revisions/{2}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::PromotePlayerFileRevision = InitEndpoint("players/{0}/files/{1}/revisions/{2}/current", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerFileByKey = InitEndpoint("players/{0}/files/key/{1}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListPlayerFileRevisionsByKey = InitEndpoint("players/{0}/files/key/{1}/revisions", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerFileRevisionByKey = InitEndpoint("players/{0}/files/key/{1}/revisions/{2}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::PromotePlayerFileRevisionByKey = InitEndpoint("players/{0}/files/key/{1}/revisions/{2}/current", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeletePlayerFileByKey = InitEndpoint("players/{0}/files/key/{1}", ELootLockerServerHTTPMethod::LL_DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreatePlayerFileDownloadLink = InitEndpoint("players/{0}/files/{1}/download-link/v1", ELootLockerServerHTTPMethod::LL_POST);

//Triggers
FLootLockerServerEndPoint ULootLockerServerEndpoints::InvokeTriggerForPlayer = InitEndpoint("trigger", ELootLockerServerHTTPMethod::LL_POST);

// Characters
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerCharacters = InitEndpoint("player/{0}/characters", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetCharacterInventory = InitEndpoint("player/{0}/characters/{1}/inventory", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnequipAssetFromCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout/{2}", ELootLockerServerHTTPMethod::LL_DELETE);

// Heroes
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerHeroes = InitEndpoint("player/{0}/heroes", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetHeroInventory = InitEndpoint("player/{0}/heroes/{1}/inventory", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnequipAssetFromHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout/{2}", ELootLockerServerHTTPMethod::LL_DELETE);

// Purchases
FLootLockerServerEndPoint ULootLockerServerEndpoints::CheckPurchaseStatus = InitEndpoint("player/{0}/purhcase/{1}", ELootLockerServerHTTPMethod::LL_GET);

// Game Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAllProgressions = InitEndpoint("progressions", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgression = InitEndpoint("progressions/{0}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionTiers = InitEndpoint("progressions/{0}/tiers", ELootLockerServerHTTPMethod::LL_GET);

// Player Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsForPlayer = InitEndpoint("players/{0}/progressions", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsByKeyForPlayer = InitEndpoint("players/{0}/progressions/{1}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddPointsToProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}/points/add", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubtractPointsFromProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}/points/subtract", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ResetProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}/reset", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteProgressionForPlayer = InitEndpoint("players/{0}/progressions/{1}", ELootLockerServerHTTPMethod::LL_DELETE);

// Character Progressions
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetProgressionsByKeyForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::AddPointsToProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}/points/add", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubtractPointsFromProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}/points/subtract", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ResetProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}/reset", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteProgressionForCharacter = InitEndpoint("players/{0}/characters/{1}/progressions/{2}", ELootLockerServerHTTPMethod::LL_DELETE);

// Currencies
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListCurrencies = InitEndpoint("currencies", ELootLockerServerHTTPMethod::LL_GET);

// Catalogs
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListCatalogItemsByKey = InitEndpoint("catalogs/inspired-ibex/v1/key/{0}/prices", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListCatalogItemsById = InitEndpoint("catalogs/inspired-ibex/v1/catalog/items", ELootLockerServerHTTPMethod::LL_POST);

// Balances
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListBalancesInWallet = InitEndpoint("balances/wallet/{0}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetWalletByWalletId = InitEndpoint("wallet/{0}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetWalletByHolderId = InitEndpoint("wallet/holder/{0}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreditBalanceToWallet = InitEndpoint("balances/credit", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DebitBalanceToWallet = InitEndpoint("balances/debit", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateWallet = InitEndpoint("wallet", ELootLockerServerHTTPMethod::LL_POST);

// Metadata
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListMetadata = InitEndpoint("metadata/source/{0}/id/{1}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MetadataActions = InitEndpoint("metadata/", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetMultisourceMetadata = InitEndpoint("metadata/multisource", ELootLockerServerHTTPMethod::LL_POST);

// Token Exchange
FLootLockerServerEndPoint ULootLockerServerEndpoints::TokenExchange = InitEndpoint("v3/oauth/token", ELootLockerServerHTTPMethod::LL_POST, ClientApiUrlSuffix);

// Notifications
FLootLockerServerEndPoint ULootLockerServerEndpoints::SendNotification = InitEndpoint("notifications/v1", ELootLockerServerHTTPMethod::LL_POST);

// Items
FLootLockerServerEndPoint ULootLockerServerEndpoints::ListPlayerInventoryItems = InitEndpoint("player/inventory/v1/{0}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerInventoryItem = InitEndpoint("player/inventory/v1/{0}/{1}", ELootLockerServerHTTPMethod::LL_GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeletePlayerInventoryItem = InitEndpoint("player/inventory/v1/{0}/{1}", ELootLockerServerHTTPMethod::LL_DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GrantItemToPlayerInventory = InitEndpoint("player/inventory/v1/{0}/grant", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SplitPlayerInventoryItemStack = InitEndpoint("player/inventory/v1/{0}/{1}/split", ELootLockerServerHTTPMethod::LL_POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MergePlayerInventoryItemStacks = InitEndpoint("player/inventory/v1/{0}/merge", ELootLockerServerHTTPMethod::LL_POST);

FLootLockerServerEndPoint ULootLockerServerEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method, const FString& BaseUrlSuffix /* = ServerApiUrlSuffix*/)
{
	FLootLockerServerEndPoint Result;
	Result.endpoint = GameBaseUrl + BaseUrlSuffix + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
