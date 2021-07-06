// Copyright (c) 2021 LootLocker

#include "LootLockerServerManager.h"

void ULootLockerServerManager::SetConfig(FString LootLockerServerKey, bool OnDevelopmentMode, FString GameVersion, FString LootLockerVersion)
{
    ULootLockerServerConfig* config = GetMutableDefault<ULootLockerServerConfig>();
    config->LootLockerServerKey = LootLockerServerKey;
    config->OnDevelopmentMode = OnDevelopmentMode;
    config->GameVersion = GameVersion;
    config->LootLockerVersion = LootLockerVersion;
    config->SaveConfig();
}

void ULootLockerServerManager::StartSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerServerAuthRequest::StartSession(OnStartedSessionRequestCompleted);
}
void ULootLockerServerManager::MaintainSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerServerAuthRequest::MaintainSession(OnStartedSessionRequestCompleted);
}

void ULootLockerServerManager::GetAssetsToGame(const FServerAssetsResponseDelegateBP& OnGetAssetsRequestCompleted,
    int StartFromIndex, int ItemsCount, ELootLockerServerAssetFilter AssetFilter, bool IncludeUGC)
{
    ULootLockerServerAssetRequest::GetAssetsToGame(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, OnGetAssetsRequestCompleted, FServerAssetsResponseDelegate());
}

void ULootLockerServerManager::GetInventory(const FInventoryResponseBP& OnGetInventoryRequestCompleted, int PlayerId, int StartFromIndex, int ItemsCount)
{
    ULootLockerServerPlayerRequest::GetInventory(PlayerId, StartFromIndex, ItemsCount, OnGetInventoryRequestCompleted, FInventoryResponse());
}

void ULootLockerServerManager::AddAssetToPlayerInventory(const FAddAssetResponseBP& OnAddAssetRequestCompleted,
    int32 PlayerId, FLootLockerServerAddAssetData AddAssetData)
{
    ULootLockerServerPlayerRequest::AddAssetToPlayerInventory(PlayerId, AddAssetData, OnAddAssetRequestCompleted, FAddAssetResponse());
}

void ULootLockerServerManager::GetPlayerLoadout(const FGetPlayerLoadoutResponseBP& OnGetPlayerLoadoutRequestCompleted,
    int PlayerId)
{
    ULootLockerServerPlayerRequest::GetPlayerLoadout(PlayerId, OnGetPlayerLoadoutRequestCompleted, FGetPlayerLoadoutResponse());
}

void ULootLockerServerManager::EquipAssetForPlayerLoadout(const FEquipAssetResponseBP& OnRequestCompleted, int PlayerId,
    int InstanceId)
{
    ULootLockerServerPlayerRequest::EquipAssetForPlayerLoadout(PlayerId, InstanceId, OnRequestCompleted, FEquipAssetResponse());
}

void ULootLockerServerManager::UnequipAssetForPlayerLoadout(const FUnequipAssetResponseBP& OnRequestCompleted,
    int PlayerId, int LoadoutId)
{
    ULootLockerServerPlayerRequest::UnequipAssetForPlayerLoadout(PlayerId, LoadoutId, OnRequestCompleted, FUnequipAssetResponse());
}

void ULootLockerServerManager::GetPersistentStorage(const FGetPersistentStorageResponseBP& OnRequestCompleted,
    TArray<int> PlayerIds)
{
    ULootLockerServerStorageRequest::GetPersistentStorage(PlayerIds, OnRequestCompleted, FGetPersistentStorageResponse());
}

void ULootLockerServerManager::UpdatePersistentStorage(const FUpdatePersistentStorageResponseBP& OnCompletedRequest,
    FLootLockerServerPersistentStorageRequestData RequestData)
{
    ULootLockerServerStorageRequest::UpdatePersistentStorage(RequestData, OnCompletedRequest, FUpdatePersistentStorageResponse());
}

void ULootLockerServerManager::GetPlayerCharacters(const FCharactersResponseBP& OnCompletedRequestBP, int PlayerId)
{
    ULootLockerServerCharacterRequest::GetPlayerCharacters(PlayerId, OnCompletedRequestBP, FCharactersResponse());
}

void ULootLockerServerManager::GetInventoryToCharacter(const FCharacterInventoryResponseBP& OnCompletedRequestBP, int PlayerId,
    int CharacterId)
{
    ULootLockerServerCharacterRequest::GetInventoryToCharacter(PlayerId, CharacterId, OnCompletedRequestBP, FCharacterInventoryResponse());
}

void ULootLockerServerManager::GetCharacterLoadout(const FCharacterLoadoutResponseBP& OnCompletedRequestBP,
    int PlayerId, int CharacterId)
{
    ULootLockerServerCharacterRequest::GetCharacterLoadout(PlayerId, CharacterId, OnCompletedRequestBP, FCharacterLoadoutResponse());
}

void ULootLockerServerManager::EquipAssetForCharacterLoadout(const FEquipResponseBP& OnCompletedRequestBP, int PlayerId,
    int CharacterId, int InstanceId)
{
    ULootLockerServerCharacterRequest::EquipAssetForCharacterLoadout(PlayerId, CharacterId, InstanceId, OnCompletedRequestBP, FEquipResponse());
}

void ULootLockerServerManager::UnequipAssetForCharacterLoadout(const FUnequipResponseBP& OnCompletedRequestBP,
    int PlayerId, int CharacterId, int InstanceId)
{
    ULootLockerServerCharacterRequest::UnequipAssetForCharacterLoadout(PlayerId, CharacterId, InstanceId, OnCompletedRequestBP, FUnequipResponse());
}

void ULootLockerServerManager::GetPlayerHeroes(const FHeroesResponseBP& OnCompletedRequestBP, int PlayerId)
{
    ULootLockerServerHeroesRequest::GetPlayerHeroes(PlayerId, OnCompletedRequestBP, FHeroesResponse());
}

void ULootLockerServerManager::GetInventoryToHero(const FHeroInventoryResponseBP& OnCompletedRequestBP, int PlayerId,
    int HeroId)
{
    ULootLockerServerHeroesRequest::GetInventoryToHero(PlayerId, HeroId, OnCompletedRequestBP, FHeroInventoryResponse());
}

void ULootLockerServerManager::GetHeroLoadout(const FHeroLoadoutResponseBP& OnCompletedRequestBP,
    int PlayerId, int HeroId)
{
    ULootLockerServerHeroesRequest::GetHeroLoadout(PlayerId, HeroId, OnCompletedRequestBP, FHeroLoadoutResponse());
}

void ULootLockerServerManager::EquipAssetForHeroLoadout(const FEquipHeroResponseBP& OnCompletedRequestBP, int PlayerId,
    int HeroId, int InstanceId)
{
    ULootLockerServerHeroesRequest::EquipAssetForHeroLoadout(PlayerId, HeroId, InstanceId, OnCompletedRequestBP, FEquipHeroResponse());
}

void ULootLockerServerManager::UnequipAssetForHeroLoadout(const FUnequipHeroResponseBP& OnCompletedRequestBP,
    int PlayerId, int HeroId, int InstanceId)
{
    ULootLockerServerHeroesRequest::UnequipAssetForHeroLoadout(PlayerId, HeroId, InstanceId, OnCompletedRequestBP, FUnequipHeroResponse());
}

void ULootLockerServerManager::InvokeTriggerOnBehalfOfPlayer(const FInvokeTriggerResponseBP& OnCompletedRequestBP,
    FString Name, int PlayerId)
{
    ULootLockerServerTriggerRequest::InvokeTriggerOnBehalfOfPlayer(Name, PlayerId, OnCompletedRequestBP, FInvokeTriggerResponse());
}

 void ULootLockerServerManager::CreateLeaderboard(const FLootLockerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerCreateLeaderboardResponseBP& OnCompletedRequestBP )
 {
     ULootLockerServerLeaderboardRequest::CreateLeaderboard(CreateLeaderboardRequest, OnCompletedRequestBP, FLootLockerCreateLeaderboardResponseDelegate());
 }

 void ULootLockerServerManager::UpdateLeaderboard(const FLootLockerUpdateLeaderboardRequest& UpdateLeaderboardRequests, int LeaderboardId, const FLootLockerUpdateLeaderboardResponseBP& OnCompletedRequestBP)
 {
     ULootLockerServerLeaderboardRequest::UpdateLeaderboard(UpdateLeaderboardRequests, LeaderboardId, OnCompletedRequestBP, FLootLockerUpdateLeaderboardResponseDelegate());
 }

 void ULootLockerServerManager::DeleteLeaderboard(int LeaderboardId, const FLootLockerDeleteLeaderboardResponseBP& OnCompletedRequestBP )
 {
     ULootLockerServerLeaderboardRequest::DeleteLeaderboard(LeaderboardId, OnCompletedRequestBP, FLootLockerDeleteLeaderboardResponseDelegate());
 }

 void ULootLockerServerManager::SubmitScore(FString MemberId, int LeaderboardId, int Score, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP)
 {
     FLootLockerServerSubmitScoreRequest score = FLootLockerServerSubmitScoreRequest();
     score.member_id = MemberId;
     score.score = Score;

     ULootLockerServerLeaderboardRequest::SubmitScore(score, LeaderboardId, OnCompletedRequestBP, FLootLockerSubmitScoreResponseDelegate());
 }

 //void ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP)
 //{
 //}

 //void PickDropsFromDropTable(TArray<int> picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP)
 //{
 //}