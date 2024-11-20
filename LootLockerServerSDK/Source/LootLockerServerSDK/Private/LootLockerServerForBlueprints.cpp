// Copyright (c) 2021 LootLocker

#include "LootLockerServerForBlueprints.h"

#include "Utils/LootLockerServerUtilities.h"

void ULootLockerServerForBlueprints::StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequest)
{
    ULootLockerServerAuthRequest::StartSession(OnCompletedRequest);
}


void ULootLockerServerForBlueprints::MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequest)
{
    ULootLockerServerAuthRequest::MaintainSession(OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::GetLeaderboard(LeaderboardKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequest)
{
    FLootLockerServerCreateLeaderboardRequest CreateLeaderboardRequest(LeaderboardKey, Name, DirectionMethod, EnableGameApiWrites, OverwriteScoreOnSubmit);
    CreateLeaderboardRequest.Type = Type;
    CreateLeaderboardRequest.Has_metadata = HasMetadata;

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

void ULootLockerServerForBlueprints::GetAllMemberRanks(const FString MemberID, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::GetAllMemberRanks(MemberID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedAllMemberRanks(const FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::GetPaginatedAllMemberRanks(MemberID, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetScoresFromLeaderboard(const FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(LeaderboardKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::GetPaginatedScoresFromLeaderboard(LeaderboardKey, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::GetLeaderboardSchedule(LeaderboardKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::CreateLeaderboardSchedule(LeaderboardKey, CronExpression, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::DeleteLeaderboardSchedule(LeaderboardKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::CreateLeaderboardReward(const FString& LeaderboardKey, const FString& RewardId, const ELootLockerServerLeaderboardRewardEntityKind& RewardKind, TArray<FLootLockerServerLeaderboardDetailPredicates> Predicates, const FLootLockerServerCreateLeaderboardRewardResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::CreateLeaderboardReward(LeaderboardKey, RewardId, RewardKind, Predicates, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeleteLeaderboardReward(const FString& LeaderboardKey, const FString& RewardId, const FLootLockerServerDeleteLeaderboardRewardResponseBP& OnCompletedRequest)
{
    ULootLockerServerLeaderboardRequest::DeleteLeaderboardReward(LeaderboardKey, RewardId, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP)
{
    ULootLockerServerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(Key, Count, After, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseBP& OnCompletedRequest)
{
    ULootLockerServerTriggerRequest::InvokeTriggerForPlayer(TriggerName, PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPersistentStorageForPlayer(int PlayerID, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest)
{
    ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(TArray<int>{ PlayerID }, OnCompletedRequest);
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

// Asset Instances
void ULootLockerServerForBlueprints::GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerAssetRequest::GetKeyValuePairsFromAssetInstance(PlayerID, AssetInstanceID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest)
{
    ULootLockerServerAssetRequest::GetAssetInstanceKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerAssetRequest::AddKeyValuePairToAssetInstance(PlayerID, AssetInstanceID, Key, Value, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerAssetRequest::UpdateKeyValuePairsOnAssetInstance(PlayerID, AssetInstanceID, KeyValuePairs, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest)
{
    ULootLockerServerAssetRequest::UpdateKeyValuePairOnAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, Key, Value, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerAssetRequest::DeleteKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, OnCompletedRequest);
}

// Drop Tables
void ULootLockerServerForBlueprints::ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerDropTableRequest::ComputeAndLockDropTable(PlayerID, DropTableID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTag(PlayerID, DropTableID, Tag, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerDropTableRequest::ComputeAndLockDropTableWithAssetInformation(PlayerID, DropTableID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTagWithAssetInformation(PlayerID, DropTableID, Tag, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerDropTableRequest::PickDropsFromDropTable(PlayerID, DropTableID, DropTableItemIDsToPick, OnCompletedRequest);
}

// Player
void ULootLockerServerForBlueprints::LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequest) 
{
    ULootLockerServerPlayerRequest::LookupPlayerNames(IdsToLookUp, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerRequest::GetPlayerInfoFromGameSessionToken(GameSessionTokensToLookUp, OnCompletedRequest);
}

// Player Files
void ULootLockerServerForBlueprints::ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerFileRequest::ListFilesForPlayer(PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerFileRequest::GetFileForPlayerByID(PlayerID, FileID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerFileRequest::DeleteFileForPlayerByID(PlayerID, FileID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerFileRequest::UploadFileForPlayer(PlayerID, FilePath, Purpose, IsPublic, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(PlayerID, RawData, FileName, Purpose, IsPublic, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerFileRequest::UpdateFileForPlayer(PlayerID, FileID, FilePath, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerFileRequest::UpdatePlayerFileWithRawData(PlayerID, FileID, RawData, FileName, OnCompletedRequest);
}

// Purchases
void ULootLockerServerForBlueprints::CheckPurchaseStatusForPlayerByID(int PlayerID, int PurchaseID, const FLootLockerServerPurchaseStatusResponseBP& OnCompletedRequest)
{
    ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByID(PlayerID, PurchaseID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::CheckPurchaseStatusForPlayerByPlatformTransactionID(int PlayerID, int PlatformTransactionID, const FLootLockerServerPurchaseStatusResponseBP& OnCompletedRequest)
{
    ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByPlatformTransactionID(PlayerID, PlatformTransactionID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::CheckPurchaseStatusForPlayerByIDWith_IncludeProducts(int PlayerID, int PurchaseID, const FLootLockerServerPurchaseStatusWithProductsResponseBP& OnCompletedRequest)
{
    ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByIDWith_IncludeProducts(PlayerID, PurchaseID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::CheckPurchaseStatusForPlayerByPlatformTransactionID_IncludeProducts(int PlayerID, int PlatformTransactionID, const FLootLockerServerPurchaseStatusWithProductsResponseBP& OnCompletedRequest)
{
    ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByPlatformTransactionID_IncludeProducts(PlayerID, PlatformTransactionID, OnCompletedRequest);
}

// Game Progressions
void ULootLockerServerForBlueprints::GetProgressions(const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerGameProgressionRequest::GetProgressions(OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerGameProgressionRequest::GetPaginatedProgressions(Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerGameProgressionRequest::GetProgressionByKey(ProgressionKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerServerGameProgressionRequest::GetTiersForProgression(ProgressionKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerServerGameProgressionRequest::GetPaginatedTiersForProgression(ProgressionKey, Count, After, OnCompletedRequest);
}

// Player Progressions

void ULootLockerServerForBlueprints::GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerProgressionRequest::GetProgressionsForPlayer(PlayerID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerProgressionRequest::GetPaginatedProgressionsForPlayer(PlayerID, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerProgressionRequest::GetProgressionForPlayerByKey(PlayerID, ProgressionKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerProgressionRequest::AddPointsToProgressionForPlayer(PlayerID, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerProgressionRequest::SubtractPointsFromProgressionForPlayer(PlayerID, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerProgressionRequest::ResetProgressionForPlayer(PlayerID, ProgressionKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerPlayerProgressionRequest::DeleteProgressionForPlayer(PlayerID, ProgressionKey, OnCompletedRequest);
}

// Character Progressions

void ULootLockerServerForBlueprints::GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterProgressionRequest::GetProgressionsForCharacter(PlayerID, CharacterID, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterProgressionRequest::GetPaginatedProgressionsForCharacter(PlayerID, CharacterID, Count, After, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterProgressionRequest::GetProgressionForCharacterByKey(PlayerID, CharacterID, ProgressionKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterProgressionRequest::AddPointsToProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterProgressionRequest::SubtractPointsFromProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterProgressionRequest::ResetProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerCharacterProgressionRequest::DeleteProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, OnCompletedRequest);
}

//Asset Instance Progression

void ULootLockerServerForBlueprints::GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerInstanceProgressionRequest::GetProgressionForAssetInstance(PlayerId, AssetInstanceId, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerInstanceProgressionRequest::GetPaginatedProgressionForAssetInstance(PlayerId, AssetInstanceId, Count, After, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerInstanceProgressionRequest::GetProgressionByKeyForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerInstanceProgressionRequest::AddPointsToProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerInstanceProgressionRequest::SubtractPointsFromProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerInstanceProgressionRequest::ResetProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, OnCompletedRequestBP);
}

void ULootLockerServerForBlueprints::DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerInstanceProgressionRequest::DeleteProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, OnCompletedRequestBP);
}

// Currencies
void ULootLockerServerForBlueprints::ListCurrencies(const FLootLockerServerListCurrenciesResponseBP& OnCompletedRequest)
{
    ULootLockerServerCurrencyRequest::ListCurrencies(OnCompletedRequest);
}

// Balances

void ULootLockerServerForBlueprints::ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseBP& OnComplete)
{
    ULootLockerServerBalanceRequest::ListBalancesInWallet(WalletID, OnComplete);
}

void ULootLockerServerForBlueprints::GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseBP& OnComplete)
{
    ULootLockerServerBalanceRequest::GetWalletByWalletID(WalletID, OnComplete);
}

void ULootLockerServerForBlueprints::GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseBP& OnComplete)
{
    ULootLockerServerBalanceRequest::GetWalletByHolderID(HolderULID, HolderType, OnComplete);
}

void ULootLockerServerForBlueprints::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseBP& OnComplete)
{
    ULootLockerServerBalanceRequest::CreditBalanceToWallet(WalletID, CurrencyID, Amount, OnComplete);
}

void ULootLockerServerForBlueprints::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseBP& OnComplete)
{
    ULootLockerServerBalanceRequest::DebitBalanceToWallet(WalletID, CurrencyID, Amount, OnComplete);
}

// Metadata

void ULootLockerServerForBlueprints::ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete)
{
    ULootLockerServerMetadataRequest::ListMetadata(Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

void ULootLockerServerForBlueprints::ListMetadataWithTags(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete)
{
    ULootLockerServerMetadataRequest::ListMetadata(Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, OnComplete);
}

void ULootLockerServerForBlueprints::GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerServerGetMetadataResponseBP& OnComplete)
{
    ULootLockerServerMetadataRequest::GetMetadata(Source, SourceID, Key, IgnoreFiles, OnComplete);
}

void ULootLockerServerForBlueprints::ParseLootLockerServerMetadataEntry(const FLootLockerServerMetadataEntry& Entry,
                                                                        ELootLockerServerMetadataParserOutputTypes& MetadataTypeSwitch,
                                                                        FString& StringValue, int& IntegerValue,
                                                                        float& FloatValue, FString& NumberString, bool& BoolValue,
                                                                        FString& JsonStringValue,
                                                                        FLootLockerServerMetadataBase64Value& Base64Value,
                                                                        FString& ErrorMessage, FLootLockerServerMetadataEntry& OutEntry)
{
    MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnError;
    StringValue = "";
    BoolValue = false;
    IntegerValue = 0;
    FloatValue = 0.0f;
    NumberString = "";
    JsonStringValue = "";
    Base64Value = FLootLockerServerMetadataBase64Value();
    ErrorMessage = "Unknown Error";
    OutEntry = Entry;
    FString ValueToParse;
    if (!Entry.TryGetSerializedValue(ValueToParse))
    {
        ErrorMessage = FString::Format(TEXT("Couldn't get serialized value for type: \"{0}\""), { static_cast<int>(Entry.Type) }); ;
        return;
    }
    switch (Entry.Type)
    {
    case ELootLockerServerMetadataTypes::String:
    {
        if (Entry.TryGetValueAsString(StringValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnString;
            return;
        }
        ErrorMessage = "Value \"" + ValueToParse + "\" could not be parsed";
        return;
    }
    case ELootLockerServerMetadataTypes::Number:
    {
        if (!FCString::IsNumeric(*ValueToParse))
        {
            ErrorMessage = "Could not parse value \"" + ValueToParse + "\" as Number because it is not numeric";
            return;
        }
        // Parse as float
        if (ValueToParse.Contains(".") && Entry.TryGetValueAsFloat(FloatValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnFloat;
            return;
        }
        // Parse as int
        if (Entry.TryGetValueAsInteger(IntegerValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnInteger;
            return;
        }
        //Treat as non int or float value, likely BigInt or BigDecimal
        MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnNumber;
        NumberString = ValueToParse;
        return;
    }
    case ELootLockerServerMetadataTypes::Bool:
    {
        if (Entry.TryGetValueAsBool(BoolValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnBool;
            return;
        }
        ErrorMessage = "Value \"" + ValueToParse + "\" could not be parsed as boolean value";
        return;
    }
    case ELootLockerServerMetadataTypes::Json:
    {
        TSharedPtr<FJsonObject> JsonObject = nullptr;
        if (Entry.TryGetValueAsJsonObject(JsonObject) && JsonObject.IsValid())
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnJson;
            JsonStringValue = ValueToParse;
            return;
        }
        TArray<TSharedPtr<FJsonValue>> OutputJsonArray;
        if (Entry.TryGetValueAsJsonArray(OutputJsonArray))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnJson;
            JsonStringValue = ValueToParse;
            return;
        }
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because it is not a valid Json String";
        return;
    }
    case ELootLockerServerMetadataTypes::Base64:
    {
        if (Entry.TryGetValueAsBase64(Base64Value) && !Base64Value.Content_type.IsEmpty())
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnBase64;
            return;
        }
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because it is not a valid LootLockerServer Metadata Base64 Object";
        return;
    }
    default:
    {
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because the type \"" + ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerMetadataTypes"), static_cast<int32>(Entry.Type)) + "\" was not recognized by the parser";
        return;
    }
    }
}

void ULootLockerServerForBlueprints::SetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerServerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerServerSetMetadataResponseBP& OnComplete)
{
    ULootLockerServerMetadataRequest::SetMetadata(Source, SourceID, MetadataToActionsToPerform, OnComplete);
}

FLootLockerServerSetMetadataAction ULootLockerServerForBlueprints::MakeMetadataActionString(ELootLockerServerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerServerSetMetadataAction{ Action, FLootLockerServerMetadataEntry::MakeStringEntry(Key, Tags, Access, Value) };
}

FLootLockerServerSetMetadataAction ULootLockerServerForBlueprints::MakeMetadataActionFloat(ELootLockerServerMetadataActions Action, const FString& Key, const float& Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerServerSetMetadataAction{ Action, FLootLockerServerMetadataEntry::MakeFloatEntry(Key, Tags, Access, Value) };
}

FLootLockerServerSetMetadataAction ULootLockerServerForBlueprints::MakeMetadataActionInteger(ELootLockerServerMetadataActions Action, const FString& Key, const int Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerServerSetMetadataAction{Action, FLootLockerServerMetadataEntry::MakeIntegerEntry(Key, Tags, Access, Value)};
}

FLootLockerServerSetMetadataAction ULootLockerServerForBlueprints::MakeMetadataActionBool(ELootLockerServerMetadataActions Action, const FString& Key, const bool Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerServerSetMetadataAction{Action, FLootLockerServerMetadataEntry::MakeBoolEntry(Key, Tags, Access, Value)};
}

void ULootLockerServerForBlueprints::MakeMetadataActionJson(ELootLockerServerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access, bool& Succeeded, FLootLockerServerSetMetadataAction& ConstructedEntry)
{
    TArray<TSharedPtr<FJsonValue>> JsonArrayValue;
    if(LootLockerServerUtilities::JsonArrayFromFString(Value, JsonArrayValue))
    {
        ConstructedEntry = FLootLockerServerSetMetadataAction{Action, FLootLockerServerMetadataEntry::MakeJsonArrayEntry(Key, Tags, Access, JsonArrayValue)};
        Succeeded = true;
        return;
    }

    TSharedPtr<FJsonObject> JsonObjectValue = LootLockerServerUtilities::JsonObjectFromFString(Value);
    if(JsonObjectValue.IsValid())
    {
         ConstructedEntry = FLootLockerServerSetMetadataAction{Action, FLootLockerServerMetadataEntry::MakeJsonObjectEntry(Key, Tags, Access, *JsonObjectValue)};
         Succeeded = true;
         return;
    }
    Succeeded = false;
}

FLootLockerServerSetMetadataAction ULootLockerServerForBlueprints::MakeMetadataActionBase64(ELootLockerServerMetadataActions Action, const FString& Key, const FLootLockerServerMetadataBase64Value& Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerServerSetMetadataAction{Action, FLootLockerServerMetadataEntry::MakeBase64Entry(Key, Tags, Access, Value)};
}

void ULootLockerServerForBlueprints::GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerServerGetMultisourceMetadataResponseBP& OnComplete)
{
    ULootLockerServerMetadataRequest::GetMultisourceMetadata(SourcesAndKeysToGet, IgnoreFiles, OnComplete);
}
