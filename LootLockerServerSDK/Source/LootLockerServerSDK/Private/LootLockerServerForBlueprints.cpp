// Copyright (c) 2021 LootLocker

#include "LootLockerServerForBlueprints.h"

#include "LootLockerServerForCpp.h"

#include "Runtime/Launch/Resources/Version.h"
#if WITH_EDITOR && (PLATFORM_WINDOWS || PLATFORM_MAC) && ((ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >=2) || ENGINE_MAJOR_VERSION >= 6)
#include "Blueprint/BlueprintExceptionInfo.h"
#endif
#include "UObject/TextProperty.h"
#include "ServerAPI/LootLockerServerNotificationsRequest.h"
#include "Utils/LootLockerServerUtilities.h"

void ULootLockerServerForBlueprints::StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::StartSession(FLootLockerServerAuthResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::MaintainSession(FLootLockerServerMaintainSessionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerMaintainSessionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GameApiTokenExchange(const FString& GameApiSessionToken, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GameApiTokenExchange(GameApiSessionToken, FLootLockerServerTokenExchangeResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerTokenExchangeResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GameApiUserImpersonation(const FString& PlayerUlid, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GameApiUserImpersonation(PlayerUlid, FLootLockerServerTokenExchangeResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerTokenExchangeResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ListLeaderboards(int32 Count, int32 After, const FLootLockerServerListLeaderboardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ListLeaderboards(Count, After, FLootLockerServerListLeaderboardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListLeaderboardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetLeaderboard(LeaderboardKey, FLootLockerServerGetLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::CreateLeaderboard(LeaderboardKey, Name, Type, HasMetadata, DirectionMethod, EnableGameApiWrites, OverwriteScoreOnSubmit, FLootLockerServerCreateLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerCreateLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UpdateLeaderboard(LeaderboardKey, NewLeaderboardKey, Name, DirectionMethod, EnableGameApiWrites, OverwriteScoreOnSubmit, FLootLockerServerUpdateLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUpdateLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::DeleteLeaderboard(LeaderboardKey, FLootLockerServerDeleteLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::SubmitScore(LeaderboardKey, MemberID, Score, Metadata, FLootLockerServerLeaderboardSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerLeaderboardSubmitScoreResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetAllMemberRanks(const FString MemberID, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetAllMemberRanks(MemberID, FLootLockerServerGetAllMemberRanksResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAllMemberRanksResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedAllMemberRanks(const FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedAllMemberRanks(MemberID, Count, After, FLootLockerServerGetAllMemberRanksResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAllMemberRanksResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetScoresFromLeaderboard(const FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetScoresFromLeaderboard(LeaderboardKey, FLootLockerServerGetScoresFromLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetScoresFromLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedScoresFromLeaderboard(LeaderboardKey, Count, After, FLootLockerServerGetScoresFromLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetScoresFromLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetLeaderboardSchedule(LeaderboardKey, FLootLockerServerGetLeaderboardScheduleResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetLeaderboardScheduleResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::CreateLeaderboardSchedule(LeaderboardKey, CronExpression, FLootLockerServerGetLeaderboardScheduleResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetLeaderboardScheduleResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::DeleteLeaderboardSchedule(LeaderboardKey, FLootLockerServerDeleteLeaderboardScheduleResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::ListLeaderboardArchive(LeaderboardKey, FLootLockerServerLeaderboardArchiveResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerLeaderboardArchiveResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::GetLeaderboardArchive(Key, Count, After, FLootLockerServerLeaderboardArchiveDetailResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerLeaderboardArchiveDetailsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::InvokeTriggerForPlayer(TriggerName, PlayerID, FLootLockerServerInvokeTriggerResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerInvokeTriggerResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPersistentStorageForPlayer(int PlayerID, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPersistentStorageForPlayer(PlayerID, FLootLockerServerGetPersistentStorageForPlayersResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPersistentStorageForPlayersResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPersistentStorageForPlayers(PlayerIDs, FLootLockerServerGetPersistentStorageForPlayersResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPersistentStorageForPlayersResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetEntirePublicPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetEntirePublicPersistentStorageForPlayers(PlayerIDs, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, Keys, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UpdatePersistentStorageForPlayersAndKeys(StorageEntriesToUpdate, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::DeletePersistentStorageForPlayersAndKeys(PlayerIDs, Keys, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Character

void ULootLockerServerForBlueprints::GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerCharacters(PlayerID, FLootLockerServerGetPlayerCharacterResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerCharactersResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerCharacterInventory(PlayerID, CharacterID, FLootLockerServerGetCharacterInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetCharacterInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedPlayerCharacterInventory(PlayerID, CharacterID, Count, After, FLootLockerServerGetCharacterInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetCharacterInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerCharacterLoadout(PlayerID, CharacterID, FLootLockerServerGetCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(PlayerID, CharacterID, AssetInstanceID, FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(PlayerID, CharacterID, AssetID, AssetVariationID, FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(PlayerID, CharacterID, AssetID, RentalOptionID, FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UnequipAssetFromPlayerCharacterLoadout(PlayerID, CharacterID, InstanceID, FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUnequipAssetFromCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Heroes

void ULootLockerServerForBlueprints::GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerHeroes(PlayerID, FLootLockerServerGetPlayerHeroResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerHeroesResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerHeroInventory(PlayerID, HeroID, FLootLockerServerGetHeroInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetHeroInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedPlayerHeroInventory(PlayerID, HeroID, Count, After, FLootLockerServerGetHeroInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetHeroInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerHeroLoadout(PlayerID, HeroID, FLootLockerServerGetHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(PlayerID, HeroID, AssetInstanceID, FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(PlayerID, HeroID, AssetID, AssetVariationID, FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(PlayerID, HeroID, AssetID, RentalOptionID, FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UnequipAssetFromPlayerHeroLoadout(PlayerID, HeroID, InstanceID, FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUnequipAssetFromHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player Inventory

void ULootLockerServerForBlueprints::GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetUniversalInventory(FLootLockerServerGetUniversalInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetUniversalInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerInventory(PlayerID, FLootLockerServerGetPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedPlayerInventory(PlayerID, Count, After, FLootLockerServerGetPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerLoadout(PlayerID, FLootLockerServerGetPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetId(PlayerID, AssetID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetInstanceId(PlayerID, AssetInstanceID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(PlayerID, AssetID, AssetVariationID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(PlayerID, AssetID, RentalOptionID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UnequipAssetFromPlayerLoadout(PlayerID, InstanceID, FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUnequipAssetFromPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetID(PlayerID, AssetID, FLootLockerServerAddAssetToPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAddAssetToPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetIDAndVariationID(PlayerID, AssetID, VariationID, FLootLockerServerAddAssetToPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAddAssetToPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(PlayerID, AssetID, RentalOptionID, FLootLockerServerAddAssetToPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAddAssetToPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetID(PlayerID, AssetsToAdd, AssetsToRemove, FLootLockerServerAlterPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAlterPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(PlayerID, AssetsToAdd, AssetsToRemove, FLootLockerServerAlterPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAlterPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(PlayerID, AssetsToAdd, AssetsToRemove, FLootLockerServerAlterPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAlterPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Assets
void ULootLockerServerForBlueprints::GetAssets(bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest) 
{
    ULootLockerServerForCpp::GetAssets(FLootLockerServerGetAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), IncludeUGC);
}

void ULootLockerServerForBlueprints::GetPaginatedAssets(int Count, int After, bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedAssets(Count, After, FLootLockerServerGetAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), IncludeUGC);
}

void ULootLockerServerForBlueprints::GetAssetsByContext(int Count, int After, int Context, bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest)
{
    ULootLockerServerForCpp::GetAssetsByContext(Count, After, Context, FLootLockerServerGetAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), IncludeUGC);
}

void ULootLockerServerForBlueprints::ListAssets(const FLootLockerServerListAssetsRequest& Request, int PerPage, int Page, const FLootLockerServerListAssetsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ListAssets(Request, PerPage, Page, FLootLockerServerListAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ListAssetsWithDefaultParameters(const FLootLockerServerListAssetsResponseBP& OnCompletedRequest)
{
    ListAssets(FLootLockerServerListAssetsRequest(), 0, 0, OnCompletedRequest);
}

void ULootLockerServerForBlueprints::ListContexts(int PerPage, int Page, const FLootLockerServerListContextsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ListContexts(PerPage, Page, FLootLockerServerListContextsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListContextsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Asset Instances
void ULootLockerServerForBlueprints::GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetKeyValuePairsFromAssetInstance(PlayerID, AssetInstanceID, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetAssetInstanceKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairItemResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AddKeyValuePairToAssetInstance(PlayerID, AssetInstanceID, Key, Value, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UpdateKeyValuePairsOnAssetInstance(PlayerID, AssetInstanceID, KeyValuePairs, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UpdateKeyValuePairOnAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, Key, Value, FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairItemResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::DeleteKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Friends
void ULootLockerServerForBlueprints::ListFriendsForPlayer(const FString& PlayerULID, int Page, int PerPage, const FLootLockerServerListFriendsResponseBP& OnCompletedRequest)
{
    ULootLockerServerFriendsRequest::ListFriends(PlayerULID, Page, PerPage, FLootLockerServerListFriendsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListFriendsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Connected Accounts
void ULootLockerServerForBlueprints::ListConnectedAccounts(const TArray<FString>& PlayerULIDs, const TArray<int>& LegacyPlayerIDs, const FLootLockerServerListConnectedAccountsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ListConnectedAccounts(PlayerULIDs, LegacyPlayerIDs, FLootLockerServerListConnectedAccountsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListConnectedAccountsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Drop Tables
void ULootLockerServerForBlueprints::ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ComputeAndLockDropTable(PlayerID, DropTableID, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ComputeAndLockDropTableForTag(PlayerID, DropTableID, Tag, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ComputeAndLockDropTableWithAssetInformation(PlayerID, DropTableID, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ComputeAndLockDropTableForTagWithAssetInformation(PlayerID, DropTableID, Tag, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::PickDropsFromDropTable(PlayerID, DropTableID, DropTableItemIDsToPick, FLootLockerServerPickFromDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPickFromDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player
void ULootLockerServerForBlueprints::LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequest) 
{
    ULootLockerServerForCpp::LookupPlayerNames(IdsToLookUp, FLootLockerServerPlayerNameLookupResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerPlayerNameLookupResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPlayerInfoFromGameSessionToken(GameSessionTokensToLookUp, FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::CreatePlayer(ELootLockerServerCreatePlayerPlatforms Platform, const FString& PlatformPlayerIdentifier, const FLootLockerServerCreatePlayerResponseBP& OnCompletedRequest) 
{
    ULootLockerServerForCpp::CreatePlayer(Platform, PlatformPlayerIdentifier, FLootLockerServerCreatePlayerResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerCreatePlayerResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player Files
void ULootLockerServerForBlueprints::ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ListFilesForPlayer(PlayerID, FLootLockerServerPlayerFileListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerFileListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetFileForPlayerByID(PlayerID, FileID, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::DeleteFileForPlayerByID(PlayerID, FileID, FLootLockerServerPlayerFileDeleteResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerFileDeleteResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UploadFileForPlayer(PlayerID, FilePath, Purpose, IsPublic, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UploadRawDataToPlayerFile(PlayerID, RawData, FileName, Purpose, IsPublic, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UpdateFileForPlayer(PlayerID, FileID, FilePath, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::UpdatePlayerFileWithRawData(PlayerID, FileID, RawData, FileName, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Game Progressions
void ULootLockerServerForBlueprints::GetProgressions(const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetProgressions(FLootLockerServerGameProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGameProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedProgressions(Count, After, FLootLockerServerGameProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGameProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetProgressionByKey(ProgressionKey, FLootLockerServerSingleGameProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleGameProgressionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetTiersForProgression(ProgressionKey, FLootLockerServerProgressionTiersResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerProgressionTiersResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedTiersForProgression(ProgressionKey, Count, After, FLootLockerServerProgressionTiersResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerProgressionTiersResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player Progressions

void ULootLockerServerForBlueprints::GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetProgressionsForPlayer(PlayerID, FLootLockerServerPlayerProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedProgressionsForPlayer(PlayerID, Count, After, FLootLockerServerPlayerProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetProgressionForPlayerByKey(PlayerID, ProgressionKey, FLootLockerServerSinglePlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AddPointsToProgressionForPlayer(PlayerID, ProgressionKey, Amount, FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::SubtractPointsFromProgressionForPlayer(PlayerID, ProgressionKey, Amount, FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ResetProgressionForPlayer(PlayerID, ProgressionKey, FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::DeleteProgressionForPlayer(PlayerID, ProgressionKey, FLootLockerServerDeletePlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Character Progressions

void ULootLockerServerForBlueprints::GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetProgressionsForCharacter(PlayerID, CharacterID, FLootLockerServerCharacterProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerCharacterProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetPaginatedProgressionsForCharacter(PlayerID, CharacterID, Count, After, FLootLockerServerCharacterProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerCharacterProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::GetProgressionForCharacterByKey(PlayerID, CharacterID, ProgressionKey, FLootLockerServerSingleCharacterProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::AddPointsToProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::SubtractPointsFromProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ResetProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::DeleteProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, FLootLockerServerDeleteCharacterProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

//Asset Instance Progression

void ULootLockerServerForBlueprints::GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::GetProgressionForAssetInstance(PlayerId, AssetInstanceId, FLootLockerServerInstanceProgressionListResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerInstanceProgressionListResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::GetPaginatedProgressionForAssetInstance(PlayerId, AssetInstanceId, Count, After, FLootLockerServerInstanceProgressionListResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerInstanceProgressionListResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::GetProgressionByKeyForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, FLootLockerServerSingleInstanceProgressionResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::AddPointsToProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionWithRewardsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::SubtractPointsFromProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionWithRewardsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::ResetProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionWithRewardsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

void ULootLockerServerForBlueprints::DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseBP& OnCompletedRequestBP)
{
    ULootLockerServerForCpp::DeleteProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, FLootLockerServerDeleteInstanceProgressionResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

// Currencies
void ULootLockerServerForBlueprints::ListCurrencies(const FLootLockerServerListCurrenciesResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::ListCurrencies(FLootLockerServerListCurrenciesResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListCurrenciesResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Balances

void ULootLockerServerForBlueprints::ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseBP& OnComplete)
{
    ULootLockerServerForCpp::ListBalancesInWallet(WalletID, FLootLockerServerListBalancesForWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerListBalancesForWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

void ULootLockerServerForBlueprints::GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseBP& OnComplete)
{
    ULootLockerServerForCpp::GetWalletByWalletID(WalletID, FLootLockerServerGetWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerGetWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

void ULootLockerServerForBlueprints::GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseBP& OnComplete)
{
    ULootLockerServerForCpp::GetWalletByHolderID(HolderULID, HolderType, FLootLockerServerGetWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerGetWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

void ULootLockerServerForBlueprints::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseBP& OnComplete)
{
    ULootLockerServerForCpp::CreditBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerServerCreditWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerCreditWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

void ULootLockerServerForBlueprints::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseBP& OnComplete)
{
    ULootLockerServerForCpp::DebitBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerServerDebitWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerDebitWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

// Metadata

void ULootLockerServerForBlueprints::ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete)
{
    ULootLockerServerForCpp::ListMetadata(Source, SourceID, Page, PerPage, FLootLockerServerListMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerListMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
}

void ULootLockerServerForBlueprints::ListMetadataWithTags(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete)
{
    ULootLockerServerForCpp::ListMetadataWithTags(Source, SourceID, Tags, Page, PerPage, FLootLockerServerListMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerListMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
}

void ULootLockerServerForBlueprints::GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerServerGetMetadataResponseBP& OnComplete)
{
    ULootLockerServerForCpp::GetMetadata(Source, SourceID, Key, FLootLockerServerGetMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerGetMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
}

void ULootLockerServerForBlueprints::GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerServerGetMultisourceMetadataResponseBP& OnComplete)
{
    ULootLockerServerForCpp::GetMultisourceMetadata(SourcesAndKeysToGet, FLootLockerServerGetMultisourceMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerGetMultisourceMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
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
    ULootLockerServerForCpp::SetMetadata(Source, SourceID, MetadataToActionsToPerform, FLootLockerServerSetMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerSetMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }));
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

// Notifications

DEFINE_FUNCTION(ULootLockerServerForBlueprints::execSendNotificationToPlayer)
{
    Stack.MostRecentProperty = nullptr;
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.StepCompiledIn<FProperty>(nullptr);
    FProperty* ContentProperty = Stack.MostRecentProperty;
    void* ContentAddress = Stack.MostRecentPropertyAddress;
    void* ContentContainerAddress =
#if ((ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >=2) || ENGINE_MAJOR_VERSION >= 6)
        Stack.MostRecentPropertyContainer;
#else
        Stack.Locals; // In editor versions < 5.2 the convenience property MostRecentPropertyContainer doesn't exist. But from my testing, when we utilize this property (for parsing value literal inputs) this is equal to Stack.Locals
#endif

    PARAM_PASSED_BY_REF(NotificationType, FStrProperty, FString);
    PARAM_PASSED_BY_VAL(Priority, FEnumProperty, ELootLockerServerNotificationPriority);
    PARAM_PASSED_BY_REF(RecipientPlayerUlid, FStrProperty, FString);
    PARAM_PASSED_BY_REF(Properties, FArrayProperty, TArray<FLootLockerServerNotificationProperty>);
    PARAM_PASSED_BY_REF(OnCompletedRequest, FDelegateProperty, FLootLockerServerSendNotificationsResponseBP);

    P_FINISH;

    P_NATIVE_BEGIN;
    TArray<FFieldClass*> UnsupportedContentTypes{
        FSetProperty::StaticClass(),
        FMapProperty::StaticClass(),
        FWeakObjectProperty::StaticClass(),
        FLazyObjectProperty::StaticClass(),
        FObjectProperty::StaticClass(),
        FSoftObjectProperty::StaticClass(),
        FEnumProperty::StaticClass(),
        FByteProperty::StaticClass(),
        FMulticastDelegateProperty::StaticClass(),
        FInterfaceProperty::StaticClass(),
        FFieldPathProperty::StaticClass(),
    };
    bool isSupportedType = true;
    for (FFieldClass* UnsupportedContentType : UnsupportedContentTypes)
    {
        if (ContentProperty->IsA(UnsupportedContentType))
        {
            FString err = FString::Format(TEXT("Type {0} is not supported by this node"), { UnsupportedContentType->GetFName().ToString() });

#if WITH_EDITOR && (PLATFORM_WINDOWS || PLATFORM_MAC) && ((ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >=2) || ENGINE_MAJOR_VERSION >= 6)
            const FBlueprintExceptionInfo ExceptionInfo(
                EBlueprintExceptionType::AccessViolation,
                FText::FromString(err)
            );
            FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
#endif
            FLootLockerServerSendNotificationsResponse ErrorResponse = LootLockerServerResponseFactory::Error<FLootLockerServerSendNotificationsResponse>(err, LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT);
            OnCompletedRequest.ExecuteIfBound(ErrorResponse);
            isSupportedType = false;
        }	    
    }

	if (isSupportedType)
    {
	    if (ContentProperty->IsA(FNumericProperty::StaticClass()))
	    {
		    if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(ContentProperty))
		    {
	            if (NumericProperty->IsFloatingPoint())
	            {
	                ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, *ContentProperty->ContainerPtrToValuePtr<double>(ContentContainerAddress), Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                    OnCompletedRequest.ExecuteIfBound(Response);
                }));
	            }
	            else
	            {
		            if (ContentProperty->IsA(FInt64Property::StaticClass()))
	                {
	                    ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, *ContentProperty->ContainerPtrToValuePtr<long long>(ContentContainerAddress), Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                        OnCompletedRequest.ExecuteIfBound(Response);
                    }));
	                } else
	                {
	                    ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, *ContentProperty->ContainerPtrToValuePtr<int>(ContentContainerAddress), Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                        OnCompletedRequest.ExecuteIfBound(Response);
                    }));
	                }
	            }
		    }
	    }
	    else if (ContentProperty->IsA(FBoolProperty::StaticClass()))
	    {
	        ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, *ContentProperty->ContainerPtrToValuePtr<bool>(ContentContainerAddress), Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
            OnCompletedRequest.ExecuteIfBound(Response);
        }));
	    }
	    else if (ContentProperty->IsA(FStrProperty::StaticClass()))
	    {
	        ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, *ContentProperty->ContainerPtrToValuePtr<FString>(ContentContainerAddress), Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
            OnCompletedRequest.ExecuteIfBound(Response);
        }));
	    }
	    else if (ContentProperty->IsA(FNameProperty::StaticClass()))
	    {
	        ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, ContentProperty->ContainerPtrToValuePtr<FName>(ContentContainerAddress)->ToString(), Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
            OnCompletedRequest.ExecuteIfBound(Response);
        }));
	    }
        else if (ContentProperty->IsA(FTextProperty::StaticClass()))
        {
            ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, ContentProperty->ContainerPtrToValuePtr<FText>(ContentContainerAddress)->ToString(), Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                OnCompletedRequest.ExecuteIfBound(Response);
            }));
        }
	    else if (ContentProperty->IsA(FStructProperty::StaticClass()))
	    {
	        if (FStructProperty* StructProperty = CastField<FStructProperty>(ContentProperty))
	        {
	            TSharedPtr<FJsonObject> Out = MakeShared<FJsonObject>();
	            if (FJsonObjectConverter::UStructToJsonAttributes(StructProperty->Struct, ContentAddress, Out->Values))
	            {
                    TSharedPtr<FJsonValue> JsonValue = MakeShared<FJsonValueObject>(Out);
	                ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, JsonValue, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                        OnCompletedRequest.ExecuteIfBound(Response);
                    }));
	            }
	        }
	    }
	    else if (ContentProperty->IsA(FArrayProperty::StaticClass()))
	    {
	        FArrayProperty* ArrayProperty = CastField<FArrayProperty>(ContentProperty);
	        if (ArrayProperty->Inner->IsA(FNumericProperty::StaticClass()))
	        {
	            if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(ArrayProperty->Inner))
	            {
	                if (NumericProperty->IsFloatingPoint())
	                {
	                    TArray<double> DecimalArrVal;
	                    ArrayProperty->CopyCompleteValueToScriptVM(&DecimalArrVal, ContentAddress);
	                    ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, DecimalArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                        OnCompletedRequest.ExecuteIfBound(Response);
                    }));
	                }
	                else
	                {
	                    if (ArrayProperty->Inner->IsA(FInt64Property::StaticClass()))
	                    {
	                        TArray<long long> IntArrVal;
	                        ArrayProperty->CopyCompleteValueToScriptVM(&IntArrVal, ContentAddress);
	                        ULootLockerServerForCpp::SendNotificationToPlayerWithLargeIntArrayContent(NotificationType, Priority, RecipientPlayerUlid, IntArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                            OnCompletedRequest.ExecuteIfBound(Response);
                        }));
	                    }
	                    else
	                    {
	                        TArray<int> IntArrVal;
	                        ArrayProperty->CopyCompleteValueToScriptVM(&IntArrVal, ContentAddress);
	                        ULootLockerServerForCpp::SendNotificationToPlayerWithIntArrayContent(NotificationType, Priority, RecipientPlayerUlid, IntArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                            OnCompletedRequest.ExecuteIfBound(Response);
                        }));
	                    }
	                }
	            }
	        }
	        else if (ArrayProperty->Inner->IsA(FBoolProperty::StaticClass()))
	        {
	            TArray<bool> BoolArrVal;
	            ArrayProperty->CopyCompleteValueToScriptVM(&BoolArrVal, ContentAddress);
	            ULootLockerServerForCpp::SendNotificationToPlayerWithBoolArrayContent(NotificationType, Priority, RecipientPlayerUlid, BoolArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                OnCompletedRequest.ExecuteIfBound(Response);
            }));
	        }
	        else if (ArrayProperty->Inner->IsA(FStrProperty::StaticClass()))
	        {
	            TArray<FString> StringArrVal;
	            ArrayProperty->CopyCompleteValueToScriptVM(&StringArrVal, ContentAddress);
	            ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, StringArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                OnCompletedRequest.ExecuteIfBound(Response);
            }));
	        }
	        else if (ArrayProperty->Inner->IsA(FNameProperty::StaticClass()))
	        {
	            TArray<FName> NameArrVal;
	            ArrayProperty->CopyCompleteValueToScriptVM(&NameArrVal, ContentAddress);
	            TArray<FString> StringArrVal;
	            for (FName& name : NameArrVal)
	            {
	                StringArrVal.Add(name.ToString());
	            }
	            ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, StringArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                OnCompletedRequest.ExecuteIfBound(Response);
            }));
	        }
            else if (ArrayProperty->Inner->IsA(FTextProperty::StaticClass()))
            {
                TArray<FText> TextArrVal;
                ArrayProperty->CopyCompleteValueToScriptVM(&TextArrVal, ContentAddress);
                TArray<FString> StringArrVal;
                for (FText& name : TextArrVal)
                {
                    StringArrVal.Add(name.ToString());
                }
                ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, StringArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                    OnCompletedRequest.ExecuteIfBound(Response);
                }));
            }
	        else if (ArrayProperty->Inner->IsA(FStructProperty::StaticClass()))
	        {
	            if (FStructProperty* StructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
	            {
	                TArray<TSharedPtr<FJsonValue>> JsonArrVal = TArray<TSharedPtr<FJsonValue>>();
	                FScriptArrayHelper ArrayHelper(ArrayProperty, StructProperty->ContainerPtrToValuePtr<void>(ContentAddress));
	                for (int i = 0; i < ArrayHelper.Num(); ++i)
	                {
	                    TSharedPtr<FJsonObject> Out = MakeShared<FJsonObject>();
	                    if (FJsonObjectConverter::UStructToJsonAttributes(StructProperty->Struct, ArrayHelper.GetRawPtr(i), Out->Values))
	                    {
	                        JsonArrVal.Add(MakeShared<FJsonValueObject>(Out));
	                    }
	                }
	                ULootLockerServerForCpp::SendNotificationToPlayer(NotificationType, Priority, RecipientPlayerUlid, JsonArrVal, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
                    OnCompletedRequest.ExecuteIfBound(Response);
                }));
	            }
	        }
	    }
    }

    P_NATIVE_END;
}

void ULootLockerServerForBlueprints::SendNotificationToPlayerWithoutContent(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, 
    const FString& RecipientPlayerUlid,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequest)
{
    ULootLockerServerForCpp::SendNotificationToPlayerWithoutContent(NotificationType, Priority, RecipientPlayerUlid, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}
