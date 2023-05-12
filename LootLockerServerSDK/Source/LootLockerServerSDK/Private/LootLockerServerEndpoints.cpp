// Copyright (c) 2021 LootLocker

#include "LootLockerServerEndpoints.h"

#include "LootLockerServerConfig.h"

FString ULootLockerServerEndpoints::GameBaseUrl = "https://{domainKey}api.lootlocker.io/server/";

//Auth
FLootLockerServerEndPoint ULootLockerServerEndpoints::StartSession = InitEndpoint("session", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MaintainingSession = InitEndpoint("ping", ELootLockerServerHTTPMethod::GET);

//Leaderboards
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateLeaderboard = InitEndpoint("leaderboards", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubmitScore = InitEndpoint("leaderboards/{0}/submit", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetAllMemberRanks = InitEndpoint("leaderboards/member/{0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetScoresFromLeaderboard = InitEndpoint("leaderboards/{0}/list", ELootLockerServerHTTPMethod::GET);

//Player Lookup
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
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeletePlayerFile = InitEndpoint("players/{player_id}/files/{file_id}", ELootLockerServerHTTPMethod::DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UploadPlayerFile = InitEndpoint("players/{player_id}/files", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdatePlayerFile = InitEndpoint("players/{player_id}/files/{file_id}", ELootLockerServerHTTPMethod::GET);

//Triggers
FLootLockerServerEndPoint ULootLockerServerEndpoints::InvokeTriggerForPlayer = InitEndpoint("trigger", ELootLockerServerHTTPMethod::POST);

// Characters
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerCharacters = InitEndpoint("player/{0}/characters", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetCharacterInventory = InitEndpoint("player/{0}/character/{1}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnequipAssetFromCharacterLoadout = InitEndpoint("player/{0}/characters/{1}/loadout/{2}", ELootLockerServerHTTPMethod::DELETE);

// Heroes
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetPlayerHeroes = InitEndpoint("player/{0}/heroes", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetHeroInventory = InitEndpoint("player/{0}/heroes{1}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::GetHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::EquipAssetToHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UnequipAssetFromHeroLoadout = InitEndpoint("player/{0}/heroes/{1}/loadout/{2}", ELootLockerServerHTTPMethod::GET);

// TODO: Remove
FLootLockerServerEndPoint ULootLockerServerEndpoints::TBD = InitEndpoint("tbd", ELootLockerServerHTTPMethod::GET);

FLootLockerServerEndPoint ULootLockerServerEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method)
{
	FLootLockerServerEndPoint Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
