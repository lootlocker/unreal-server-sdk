// Copyright (c) 2021 LootLocker

#include "LootLockerServerGameEndpoints.h"

#include "LootLockerServerConfig.h"

FString ULootLockerServerGameEndpoints::GameBaseUrl = "https://api.lootlocker.io/server/";

//Auth
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::StartSessionEndpoint = InitEndpoint("session", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::MaintainingSessionEndpoint = InitEndpoint("ping", ELootLockerServerHTTPMethod::GET);

FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetAssetsToGameEndpoint = InitEndpoint("assets", ELootLockerServerHTTPMethod::GET);
//Player Inventory
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetPlayerInventoryEndpoint = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::AddAssetsToPlayerInventoryEndpoint = InitEndpoint("player/{0}/inventory", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetPlayerLoadoutEndpoint = InitEndpoint("player/{0}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::EquipAssetToPlayerLoadoutEndpoint = InitEndpoint("player/{0}/loadout", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::UnEquipAssetToPlayerLoadoutEndpoint = InitEndpoint("player/{0}/loadout/{1}", ELootLockerServerHTTPMethod::DELETE);
//Player persisitent storage
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetPersistentStorageEndpoint = InitEndpoint("players/storage?player_ids={0}", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::UpdatePersistentStorageEndpoint = InitEndpoint("players/storage", ELootLockerServerHTTPMethod::PATCH);
//Characters & Heroes
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetPlayerCharactersEndpoint = InitEndpoint("player/{0}/characters", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetInventorytoCharacterEndpoint = InitEndpoint("player/{0}/character/{1}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetCharacterLoadoutEndpoint = InitEndpoint("player/{0}/characters/{1}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::EquipAssetforCharacterLoadoutEndpoint = InitEndpoint("player/{0}/character/{1}/loadout", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::UnequipAssetforCharacterLoadoutEndpoint = InitEndpoint("player/{0}/character/{1}/loadout/{2}", ELootLockerServerHTTPMethod::DELETE);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetPlayerHeroesEndpoint = InitEndpoint("player/{0}/heroes", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetInventorytoHeroEndpoint = InitEndpoint("player/{0}/hero/{1}/inventory", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::GetHeroLoadoutEndpoint = InitEndpoint("player/{0}/hero/{1}/loadout", ELootLockerServerHTTPMethod::GET);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::EquipAssetforHeroLoadoutEndpoint = InitEndpoint("player/{0}/hero/{1}/loadout", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::UnequipAssetforHeroLoadoutEndpoint = InitEndpoint("player/{0}/hero/{1}/loadout/{2}", ELootLockerServerHTTPMethod::DELETE);
//Trigger
FLootLockerServerEndPoints ULootLockerServerGameEndpoints::InvokeTriggeronBehalfofPlayerEndpoint = InitEndpoint("trigger", ELootLockerServerHTTPMethod::POST);

FLootLockerServerEndPoints ULootLockerServerGameEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method)
{
	FLootLockerServerEndPoints Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
