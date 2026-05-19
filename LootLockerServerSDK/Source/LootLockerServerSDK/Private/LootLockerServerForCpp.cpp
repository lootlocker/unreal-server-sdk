// Copyright (c) 2021 LootLocker


#include "LootLockerServerForCpp.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"
#include "ServerAPI/LootLockerServerDropTableRequest.h"
#include "ServerAPI/LootLockerServerGameProgressionRequest.h"
#include "ServerAPI/LootLockerServerPlayerFileRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"

//Authentication
FString ULootLockerServerForCpp::StartSession(const FLootLockerServerAuthResponseDelegate& OnCompleteRequest)
{
    return ULootLockerServerAuthRequest::StartSession(OnCompleteRequest);
}

FString ULootLockerServerForCpp::MaintainSession(const FLootLockerServerMaintainSessionResponseDelegate& OnCompleteRequest)
{
    return ULootLockerServerAuthRequest::MaintainSession(OnCompleteRequest);
}

FString ULootLockerServerForCpp::GameApiTokenExchange(const FString& GameApiSessionToken, const FLootLockerServerTokenExchangeResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerOAuthRequest::GameApiTokenExchange(GameApiSessionToken, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GameApiUserImpersonation(const FString& PlayerUlid, const FLootLockerServerTokenExchangeResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerOAuthRequest::GameApiUserImpersonation(PlayerUlid, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ListLeaderboards(const FLootLockerServerListLeaderboardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::ListLeaderboards(0, 0, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ListLeaderboards(int32 Count, int32 After, const FLootLockerServerListLeaderboardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::ListLeaderboards(Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::GetLeaderboard(LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
    FLootLockerServerCreateLeaderboardRequest CreateLeaderboardRequest(LeaderboardKey, Name, DirectionMethod, EnableGameApiWrites, OverwriteScoreOnSubmit);
    CreateLeaderboardRequest.Type = Type;
    CreateLeaderboardRequest.Has_metadata = HasMetadata;
    return ULootLockerServerLeaderboardRequest::CreateLeaderboard(CreateLeaderboardRequest, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
    const FLootLockerServerUpdateLeaderboardRequest UpdateLeaderboardRequest(
        NewLeaderboardKey.IsEmpty() ? LeaderboardKey : NewLeaderboardKey,
        Name,
        DirectionMethod,
        EnableGameApiWrites,
        OverwriteScoreOnSubmit
    );
    return ULootLockerServerLeaderboardRequest::UpdateLeaderboard(LeaderboardKey, UpdateLeaderboardRequest, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::DeleteLeaderboard(LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest)
{
    const FLootLockerServerLeaderboardSubmitScoreRequest SubmitScoreRequest
    {
        MemberID,
        Score,
        Metadata
    };
    return ULootLockerServerLeaderboardRequest::SubmitScore(LeaderboardKey, SubmitScoreRequest, OnCompletedRequest);
}

FString ULootLockerServerForCpp::IncrementScore(FString LeaderboardKey, FString MemberID, int Amount, const FLootLockerServerLeaderboardIncrementScoreResponseDelegate& OnCompletedRequest)
{
    const FLootLockerServerLeaderboardIncrementScoreRequest IncrementScoreRequest
    {
        MemberID,
        Amount
    };
    return ULootLockerServerLeaderboardRequest::IncrementScore(LeaderboardKey, IncrementScoreRequest, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetAllMemberRanks(const FString MemberID, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::GetAllMemberRanks(MemberID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedAllMemberRanks(const FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::GetPaginatedAllMemberRanks(MemberID, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetScoresFromLeaderboard(FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest) {
    return ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedScoresFromLeaderboard(FString LeaderboardKey, int Count, int After, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest) {
    return ULootLockerServerLeaderboardRequest::GetPaginatedScoresFromLeaderboard(LeaderboardKey, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::GetLeaderboardSchedule(LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::CreateLeaderboardSchedule(LeaderboardKey, CronExpression, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardRequest::DeleteLeaderboardSchedule(LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(Key, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerTriggerRequest::InvokeTriggerForPlayer(TriggerName, PlayerID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPersistentStorageForPlayer(int PlayerID,	const FLootLockerServerGetPersistentStorageForPlayersResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(TArray<int>{PlayerID}, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(PlayerIDs, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetEntirePublicPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerStorageRequest::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, TArray<FString>(), OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerStorageRequest::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, Keys, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerStorageRequest::UpdatePersistentStorageForPlayersAndKeys(StorageEntriesToUpdate, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs,	TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerStorageRequest::DeletePersistentStorageForPlayersAndKeys(PlayerIDs, Keys, OnCompletedRequest);
}

// Character

FString ULootLockerServerForCpp::GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::GetPlayerCharacters(PlayerID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::GetPlayerCharacterInventory(PlayerID, CharacterID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::GetPaginatedPlayerCharacterInventory(PlayerID, CharacterID, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::GetPlayerCharacterLoadout(PlayerID, CharacterID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(PlayerID, CharacterID, AssetInstanceID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(PlayerID, CharacterID, AssetID, AssetVariationID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(PlayerID, CharacterID, AssetID, RentalOptionID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterRequest::UnequipAssetFromPlayerCharacterLoadout(PlayerID, CharacterID, InstanceID, OnCompletedRequest);
}

// Heroes

FString ULootLockerServerForCpp::GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::GetPlayerHeroes(PlayerID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::GetPlayerHeroInventory(PlayerID, HeroID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::GetPaginatedPlayerHeroInventory(PlayerID, HeroID, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::GetPlayerHeroLoadout(PlayerID, HeroID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(PlayerID, HeroID, AssetInstanceID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(PlayerID, HeroID, AssetID, AssetVariationID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(PlayerID, HeroID, AssetID, RentalOptionID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHeroRequest::UnequipAssetFromPlayerHeroLoadout(PlayerID, HeroID, InstanceID, OnCompletedRequest);
}

// Player Inventory

FString ULootLockerServerForCpp::GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::GetUniversalInventory(OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::GetPlayerInventory(PlayerID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::GetPaginatedPlayerInventory(PlayerID, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::GetPlayerLoadout(PlayerID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetId(PlayerID, AssetID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetInstanceId(PlayerID, AssetInstanceID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(PlayerID, AssetID, AssetVariationID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(PlayerID, AssetID, RentalOptionID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::UnequipAssetFromPlayerLoadout(PlayerID, InstanceID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetID(PlayerID, AssetID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndVariationID(PlayerID, AssetID, VariationID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(PlayerID, AssetID, RentalOptionID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetID(PlayerID, AssetsToAdd, AssetsToRemove, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(PlayerID, AssetsToAdd, AssetsToRemove, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(PlayerID, AssetsToAdd, AssetsToRemove, OnCompletedRequest);
}

// Assets
FString ULootLockerServerForCpp::GetAssets(const FLootLockerServerGetAssetsResponseDelegate &OnCompletedRequest, bool IncludeUGC) 
{
    return ULootLockerServerAssetRequest::GetAssets(0, 0, -1, IncludeUGC, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedAssets(int Count, int After, const FLootLockerServerGetAssetsResponseDelegate &OnCompletedRequest, bool IncludeUGC) 
{
    return ULootLockerServerAssetRequest::GetAssets(Count, After, -1, IncludeUGC, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetAssetsByContext(int Count, int After, int Context, const FLootLockerServerGetAssetsResponseDelegate &OnCompletedRequest, bool IncludeUGC)
{
    return ULootLockerServerAssetRequest::GetAssets(Count, After, Context, IncludeUGC, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ListAssets(const FLootLockerServerListAssetsRequest& Request, int PerPage, int Page, const FLootLockerServerListAssetsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::ListAssets(Request, PerPage, Page, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ListAssetsWithDefaultParameters(const FLootLockerServerListAssetsResponseDelegate& OnCompletedRequest)
{
    return ListAssets(FLootLockerServerListAssetsRequest(), 0, 0, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ListContexts(int PerPage, int Page, const FLootLockerServerListContextsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::ListContexts(PerPage, Page, OnCompletedRequest);
}

// Asset Instances
FString ULootLockerServerForCpp::GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::GetKeyValuePairsFromAssetInstance(PlayerID, AssetInstanceID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::GetAssetInstanceKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::AddKeyValuePairToAssetInstance(PlayerID, AssetInstanceID, Key, Value, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::UpdateKeyValuePairsOnAssetInstance(PlayerID, AssetInstanceID, KeyValuePairs, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::UpdateKeyValuePairOnAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, Key, Value, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerAssetRequest::DeleteKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, OnCompletedRequest);
}

// Friends

FString ULootLockerServerForCpp::ListFriendsForPlayer(const FString& PlayerULID, int Page, int PerPage, const FLootLockerServerListFriendsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerFriendsRequest::ListFriends(PlayerULID, Page, PerPage, OnCompletedRequest);
}

// Connected Accounts
FString ULootLockerServerForCpp::ListConnectedAccounts(const TArray<FString>& PlayerULIDs, const TArray<int>& LegacyPlayerIDs, const FLootLockerServerListConnectedAccountsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerConnectedAccountsRequest::ListConnectedAccounts(PlayerULIDs, LegacyPlayerIDs, OnCompletedRequest);
}

// Drop Tables
FString ULootLockerServerForCpp::ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerDropTableRequest::ComputeAndLockDropTable(PlayerID, DropTableID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTag(PlayerID, DropTableID, Tag, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerDropTableRequest::ComputeAndLockDropTableWithAssetInformation(PlayerID, DropTableID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTagWithAssetInformation(PlayerID, DropTableID, Tag, OnCompletedRequest);
}

FString ULootLockerServerForCpp::PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerDropTableRequest::PickDropsFromDropTable(PlayerID, DropTableID, DropTableItemIDsToPick, OnCompletedRequest);
}

// Player
FString ULootLockerServerForCpp::LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerPlayerRequest::LookupPlayerNames(IdsToLookUp, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerRequest::GetPlayerInfoFromGameSessionToken(GameSessionTokensToLookUp, OnCompletedRequest);
}

FString ULootLockerServerForCpp::CreatePlayer(ELootLockerServerCreatePlayerPlatforms Platform, const FString& PlatformPlayerIdentifier, const FLootLockerServerCreatePlayerResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerPlayerRequest::CreatePlayer(Platform, PlatformPlayerIdentifier, OnCompletedRequest);
}

// Player Files
FString ULootLockerServerForCpp::ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerFileRequest::ListFilesForPlayer(PlayerID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerFileRequest::GetFileForPlayerByID(PlayerID, FileID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerFileRequest::DeleteFileForPlayerByID(PlayerID, FileID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerFileRequest::UploadFileForPlayer(PlayerID, FilePath, Purpose, IsPublic, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(PlayerID, RawData, FileName, Purpose, IsPublic, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerFileRequest::UpdateFileForPlayer(PlayerID, FileID, FilePath, OnCompletedRequest);
}

FString ULootLockerServerForCpp::UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerFileRequest::UpdatePlayerFileWithRawData(PlayerID, FileID, RawData, FileName, OnCompletedRequest);
}

// Game Progressions
FString ULootLockerServerForCpp::GetProgressions(const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerGameProgressionRequest::GetProgressions(OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerGameProgressionRequest::GetPaginatedProgressions(Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerGameProgressionRequest::GetProgressionByKey(ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerGameProgressionRequest::GetTiersForProgression(ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerGameProgressionRequest::GetPaginatedTiersForProgression(ProgressionKey, Count, After, OnCompletedRequest);
}


// Player Progressions

FString ULootLockerServerForCpp::GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerProgressionRequest::GetProgressionsForPlayer(PlayerID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerProgressionRequest::GetPaginatedProgressionsForPlayer(PlayerID, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerProgressionRequest::GetProgressionForPlayerByKey(PlayerID, ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerProgressionRequest::AddPointsToProgressionForPlayer(PlayerID, ProgressionKey, Amount, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerProgressionRequest::SubtractPointsFromProgressionForPlayer(PlayerID, ProgressionKey, Amount, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerProgressionRequest::ResetProgressionForPlayer(PlayerID, ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerPlayerProgressionRequest::DeleteProgressionForPlayer(PlayerID, ProgressionKey, OnCompletedRequest);
}

// Character Progressions

FString ULootLockerServerForCpp::GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterProgressionRequest::GetProgressionsForCharacter(PlayerID, CharacterID, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterProgressionRequest::GetPaginatedProgressionsForCharacter(PlayerID, CharacterID, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterProgressionRequest::GetProgressionForCharacterByKey(PlayerID, CharacterID, ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterProgressionRequest::AddPointsToProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterProgressionRequest::SubtractPointsFromProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterProgressionRequest::ResetProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCharacterProgressionRequest::DeleteProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, OnCompletedRequest);
}

//Instance Progression

FString ULootLockerServerForCpp::GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerInstanceProgressionRequest::GetProgressionForAssetInstance(PlayerId, AssetInstanceId, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerInstanceProgressionRequest::GetPaginatedProgressionForAssetInstance(PlayerId, AssetInstanceId, Count, After, OnCompletedRequest);
}

FString ULootLockerServerForCpp::GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerInstanceProgressionRequest::GetProgressionByKeyForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerInstanceProgressionRequest::AddPointsToProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerInstanceProgressionRequest::SubtractPointsFromProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

FString ULootLockerServerForCpp::ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerInstanceProgressionRequest::ResetProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

FString ULootLockerServerForCpp::DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerInstanceProgressionRequest::DeleteProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

// Currencies
FString ULootLockerServerForCpp::ListCurrencies(const FLootLockerServerListCurrenciesResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCurrencyRequest::ListCurrencies(OnCompletedRequest);
}

// Catalogs
FString ULootLockerServerForCpp::ListCatalogItemsByKey(const FString& CatalogKey, int Count, const FString& After, const FLootLockerServerListCatalogPricesResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerCatalogRequest::ListCatalogItemsByKey(CatalogKey, Count, After, OnCompletedRequest);
}

// Balances

FString ULootLockerServerForCpp::ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseDelegate& OnComplete)
{
    return ULootLockerServerBalanceRequest::ListBalancesInWallet(WalletID, OnComplete);
}

FString ULootLockerServerForCpp::GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
{
    return ULootLockerServerBalanceRequest::GetWalletByWalletID(WalletID, OnComplete);
}

FString ULootLockerServerForCpp::GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
{
    return ULootLockerServerBalanceRequest::GetWalletByHolderID(HolderULID, HolderType, OnComplete);
}

FString ULootLockerServerForCpp::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseDelegate& OnComplete)
{
    return ULootLockerServerBalanceRequest::CreditBalanceToWallet(WalletID, CurrencyID, Amount, OnComplete);
}

FString ULootLockerServerForCpp::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseDelegate& OnComplete)
{
    return ULootLockerServerBalanceRequest::DebitBalanceToWallet(WalletID, CurrencyID, Amount, OnComplete);
}

// Metadata

FString ULootLockerServerForCpp::ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FLootLockerServerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    return ULootLockerServerMetadataRequest::ListMetadata(Source, SourceID, -1, -1, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

FString ULootLockerServerForCpp::ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FLootLockerServerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    return ULootLockerServerMetadataRequest::ListMetadata(Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

FString ULootLockerServerForCpp::ListMetadataWithTags(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const FLootLockerServerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    return ULootLockerServerMetadataRequest::ListMetadata(Source, SourceID, -1, -1, FString(), Tags, IgnoreFiles, OnComplete);
}

FString ULootLockerServerForCpp::ListMetadataWithTags(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const FLootLockerServerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    return ULootLockerServerMetadataRequest::ListMetadata(Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, OnComplete);
}

FString ULootLockerServerForCpp::GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const FLootLockerServerGetMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    return ULootLockerServerMetadataRequest::GetMetadata(Source, SourceID, Key, IgnoreFiles, OnComplete);
}

FString ULootLockerServerForCpp::GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const FLootLockerServerGetMultisourceMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    return ULootLockerServerMetadataRequest::GetMultisourceMetadata(SourcesAndKeysToGet, IgnoreFiles, OnComplete);
}

FString ULootLockerServerForCpp::SetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerServerSetMetadataAction>& MetadataToActionsToPerform,	const FLootLockerServerSetMetadataResponseDelegate& OnComplete)
{
    return ULootLockerServerMetadataRequest::SetMetadata(Source, SourceID, MetadataToActionsToPerform, OnComplete);
}

// Notifications

FString ULootLockerServerForCpp::SendNotificationToPlayerWithoutContent(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithoutContent(NotificationType, Priority, RecipientPlayerUlid, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, bool Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithBoolContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, int Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithIntContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, long long Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithLargeIntContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, double Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithDoubleContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, float Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithFloatContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const char* Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithStringContent(NotificationType, Priority, RecipientPlayerUlid, FString(Content), Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const FString& Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithStringContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid,
	const TSharedPtr<FJsonValue>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithJsonContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayerWithBoolArrayContent(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<bool>& Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithBoolArrayContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayerWithIntArrayContent(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<int>& Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithIntArrayContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayerWithLargeIntArrayContent(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid,
	const TArray<long long>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithLargeIntArrayContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<double>& Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithDoubleArrayContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<float>& Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithFloatArrayContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FString>& Content,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithStringArrayContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}

FString ULootLockerServerForCpp::SendNotificationToPlayer(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid,
	const TArray<TSharedPtr<FJsonValue>>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithJsonArrayContent(NotificationType, Priority, RecipientPlayerUlid, Content, Properties, OnCompletedRequest);
}
