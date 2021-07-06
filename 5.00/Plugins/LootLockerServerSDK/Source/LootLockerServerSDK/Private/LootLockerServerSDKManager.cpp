// Copyright (c) 2021 LootLocker


#include "LootLockerServerSDKManager.h"

//Authentication
void ULootLockerServerSDKManager::StartSession(const FServerAuthResponse& OnCompleteRequest)
{
	ULootLockerServerAuthRequest::StartSession( FServerAuthResponseBP(), OnCompleteRequest);
}

void ULootLockerServerSDKManager::MaintainSession(const FServerAuthResponse& OnCompleteRequest)
{
	ULootLockerServerAuthRequest::MaintainSession(FServerAuthResponseBP(), OnCompleteRequest);
}

void ULootLockerServerSDKManager::GetAssetsToGame(const FServerAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex,
	int ItemsCount, ELootLockerServerAssetFilter AssetFilter, bool IncludeUGC)
{
	ULootLockerServerAssetRequest::GetAssetsToGame(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, FServerAssetsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::GetInventory(const FInventoryResponse& OnGetInventoryRequestCompleted,
	int PlayerId, int StartFromIndex, int ItemsCount)
{
	ULootLockerServerPlayerRequest::GetInventory(PlayerId, StartFromIndex, ItemsCount, FInventoryResponseBP(), OnGetInventoryRequestCompleted);
}

void ULootLockerServerSDKManager::AddAssetToPlayerInventory(const FAddAssetResponse& OnAddAssetRequestCompleted,
	int PlayerId, FLootLockerServerAddAssetData AddAssetData)
{
	ULootLockerServerPlayerRequest::AddAssetToPlayerInventory(PlayerId, AddAssetData, FAddAssetResponseBP(), OnAddAssetRequestCompleted);
}

void ULootLockerServerSDKManager::GetPlayerLoadout(const FGetPlayerLoadoutResponse& OnGetPlayerLoadoutRequestCompleted,
	int PlayerId)
{
	ULootLockerServerPlayerRequest::GetPlayerLoadout(PlayerId, FGetPlayerLoadoutResponseBP(), OnGetPlayerLoadoutRequestCompleted);
}

void ULootLockerServerSDKManager::EquipAssetForPlayerLoadout(const FEquipAssetResponse& OnRequestCompleted,
	int PlayerId, int InstanceId)
{
	ULootLockerServerPlayerRequest::EquipAssetForPlayerLoadout(PlayerId, InstanceId, FEquipAssetResponseBP(), OnRequestCompleted);
}

void ULootLockerServerSDKManager::UnequipAssetForPlayerLoadout(const FUnequipAssetResponse& OnRequestCompleted,
	int PlayerId, int LoadoutId)
{
	ULootLockerServerPlayerRequest::UnequipAssetForPlayerLoadout(PlayerId, LoadoutId, FUnequipAssetResponseBP(), OnRequestCompleted);
}

void ULootLockerServerSDKManager::GetPersistentStorage(const FGetPersistentStorageResponse& OnRequestCompleted,
	TArray<int> PlayerIds)
{
	ULootLockerServerStorageRequest::GetPersistentStorage(PlayerIds, FGetPersistentStorageResponseBP(), OnRequestCompleted);
}

void ULootLockerServerSDKManager::UpdatePersistentStorage(const FUpdatePersistentStorageResponse& OnCompletedRequest,
	FLootLockerServerPersistentStorageRequestData RequestData)
{
	ULootLockerServerStorageRequest::UpdatePersistentStorage(RequestData, FUpdatePersistentStorageResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::GetPlayerCharacters(const FCharactersResponse& OnCompletedRequest, int PlayerId)
{
	ULootLockerServerCharacterRequest::GetPlayerCharacters(PlayerId, FCharactersResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::GetInventoryToCharacter(const FCharacterInventoryResponse& OnCompletedRequest,
	int PlayerId, int CharacterId)
{
	ULootLockerServerCharacterRequest::GetInventoryToCharacter(PlayerId, CharacterId, FCharacterInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest, int PlayerId,
	int CharacterId)
{
	ULootLockerServerCharacterRequest::GetCharacterLoadout(PlayerId, CharacterId, FCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::EquipAssetForCharacterLoadout(const FEquipResponse& OnCompletedRequest,
	int PlayerId, int CharacterId, int InstanceId)
{
	ULootLockerServerCharacterRequest::EquipAssetForCharacterLoadout(PlayerId, CharacterId, InstanceId, FEquipResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::UnequipAssetForCharacterLoadout(const FUnequipResponse& OnCompletedRequest,
	int PlayerId, int CharacterId, int InstanceId)
{
	ULootLockerServerCharacterRequest::UnequipAssetForCharacterLoadout(PlayerId, CharacterId, InstanceId, FUnequipResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::GetPlayerHeroes(const FHeroesResponse& OnCompletedRequest, int PlayerId)
{
	ULootLockerServerHeroesRequest::GetPlayerHeroes(PlayerId, FHeroesResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::GetInventoryToHero(const FHeroInventoryResponse& OnCompletedRequest,
    int PlayerId, int HeroId)
{
	ULootLockerServerHeroesRequest::GetInventoryToHero(PlayerId, HeroId, FHeroInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::GetHeroLoadout(const FHeroLoadoutResponse& OnCompletedRequest, int PlayerId,
    int HeroId)
{
	ULootLockerServerHeroesRequest::GetHeroLoadout(PlayerId, HeroId, FHeroLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::EquipAssetForHeroLoadout(const FEquipHeroResponse& OnCompletedRequest,
    int PlayerId, int HeroId, int InstanceId)
{
	ULootLockerServerHeroesRequest::EquipAssetForHeroLoadout(PlayerId, HeroId, InstanceId, FEquipHeroResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::UnequipAssetForHeroLoadout(const FUnequipHeroResponse& OnCompletedRequest,
    int PlayerId, int HeroId, int InstanceId)
{
	ULootLockerServerHeroesRequest::UnequipAssetForHeroLoadout(PlayerId, HeroId, InstanceId, FUnequipHeroResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::InvokeTriggerOnBehalfOfPlayer(const FInvokeTriggerResponse& OnCompletedRequest,
	FString Name, int PlayerId)
{
	ULootLockerServerTriggerRequest::InvokeTriggerOnBehalfOfPlayer(Name, PlayerId, FInvokeTriggerResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::CreateLeaderboard(const FLootLockerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerLeaderboardRequestHandler::CreateLeaderboard(CreateLeaderboardRequest, FLootLockerCreateLeaderboardResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::UpdateLeaderboard(const FLootLockerUpdateLeaderboardRequest& UpdateLeaderboardRequests, int LeaderboardId, const FLootLockerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerLeaderboardRequestHandler::UpdateLeaderboard(UpdateLeaderboardRequests, LeaderboardId, FLootLockerUpdateLeaderboardResponseBP(), OnCompletedRequest);
}

void ULootLockerServerSDKManager::DeleteLeaderboard(int LeaderboardId, const FLootLockerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerLeaderboardRequestHandler::DeleteLeaderboard(LeaderboardId, FLootLockerDeleteLeaderboardResponseBP(), OnCompletedRequest);

}

void ULootLockerServerSDKManager::SubmitScore(FString MemberId, int LeaderboardId, int Score, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	FLootLockerSubmitScoreRequest score = FLootLockerSubmitScoreRequest();
	score.member_id = MemberId;
	score.score = Score;

	ULootLockerLeaderboardRequestHandler::SubmitScore(score, LeaderboardId, FLootLockerSubmitScoreResponseBP(), OnCompletedRequest);
}


