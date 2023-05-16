// Copyright (c) 2021 LootLocker

#include "LootLockerServerForBlueprints.h"

void ULootLockerServerForBlueprints::StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequest)
{
    ULootLockerServerAuthRequest::StartSession(OnCompletedRequest);
}
void ULootLockerServerForBlueprints::MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequest)
{
    ULootLockerServerAuthRequest::MaintainSession(OnCompletedRequest);
}

void ULootLockerServerForBlueprints::CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequest)
{
	const FLootLockerServerCreateLeaderboardRequest CreateLeaderboardRequest
	{
        { LeaderboardKey,
            Name,
            DirectionMethod,
            EnableGameApiWrites,
            OverwriteScoreOnSubmit },
		Type,
		HasMetadata,
	};
	ULootLockerServerLeaderboardRequest::CreateLeaderboard(CreateLeaderboardRequest, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequest)
{
	const FLootLockerServerUpdateLeaderboardRequest UpdateLeaderboardRequest
	{
		NewLeaderboardKey.IsEmpty() ? LeaderboardKey : NewLeaderboardKey,
		Name,
		DirectionMethod,
		EnableGameApiWrites,
		OverwriteScoreOnSubmit
	};
	ULootLockerServerLeaderboardRequest::UpdateLeaderboard(LeaderboardKey, UpdateLeaderboardRequest, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequest)
{
	ULootLockerServerLeaderboardRequest::DeleteLeaderboard(LeaderboardKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequest)
{
	const FLootLockerServerLeaderboardSubmitScoreRequest SubmitScoreRequest
	{
		MemberID,
		Score,
		Metadata
	};
	ULootLockerServerLeaderboardRequest::SubmitScore(LeaderboardKey, SubmitScoreRequest, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetAllMemberRanks(const FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest)
{
	ULootLockerServerLeaderboardRequest::GetAllMemberRanks(MemberID, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest)
{
	ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(LeaderboardKey, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseBP& OnCompletedRequest)
{
	ULootLockerServerTriggerRequest::InvokeTriggerForPlayer(TriggerName, PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPersistentStorageForPlayer(int PlayerID, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(TArray{ PlayerID }, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(PlayerIDs, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetEntirePublicPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, TArray<FString>(), OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, Keys, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::UpdatePersistentStorageForPlayersAndKeys(StorageEntriesToUpdate, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::DeletePersistentStorageForPlayersAndKeys(PlayerIDs, Keys, OnCompletedRequest);
}

// Character

void ULootLockerServerForBlueprints::GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPlayerCharacters(PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPlayerCharacterInventory(PlayerID, CharacterID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPaginatedPlayerCharacterInventory(PlayerID, CharacterID, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPlayerCharacterLoadout(PlayerID, CharacterID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(PlayerID, CharacterID, AssetInstanceID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(PlayerID, CharacterID, AssetID, AssetVariationID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(PlayerID, CharacterID, AssetID, RentalOptionID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::UnequipAssetFromPlayerCharacterLoadout(PlayerID, CharacterID, InstanceID, OnCompletedRequest);
}

// Heroes

void ULootLockerServerForBlueprints::GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::GetPlayerHeroes(PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::GetPlayerHeroInventory(PlayerID, HeroID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::GetPaginatedPlayerHeroInventory(PlayerID, HeroID, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::GetPlayerHeroLoadout(PlayerID, HeroID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(PlayerID, HeroID, AssetInstanceID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(PlayerID, HeroID, AssetID, AssetVariationID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(PlayerID, HeroID, AssetID, RentalOptionID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerHeroRequest::UnequipAssetFromPlayerHeroLoadout(PlayerID, HeroID, InstanceID, OnCompletedRequest);
}

// Player Inventory

void ULootLockerServerForBlueprints::GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::GetUniversalInventory(OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::GetPlayerInventory(PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::GetPaginatedPlayerInventory(PlayerID, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::GetPlayerLoadout(PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetId(PlayerID, AssetID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetInstanceId(PlayerID, AssetInstanceID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(PlayerID, AssetID, AssetVariationID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(PlayerID, AssetID, RentalOptionID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::UnequipAssetFromPlayerLoadout(PlayerID, InstanceID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetID(PlayerID, AssetID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndVariationID(PlayerID, AssetID, VariationID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(PlayerID, AssetID, RentalOptionID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetID(PlayerID, AssetsToAdd, AssetsToRemove, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(PlayerID, AssetsToAdd, AssetsToRemove, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
	ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(PlayerID, AssetsToAdd, AssetsToRemove, OnCompletedRequest);
}

// Assets
void ULootLockerServerForBlueprints::GetAssets(const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest) 
{
	ULootLockerServerAssetRequest::GetAssets(OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedAssets(int Count, int After, const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest) 
{
	ULootLockerServerAssetRequest::GetPaginatedAssets(Count, After, OnCompletedRequest);
}
