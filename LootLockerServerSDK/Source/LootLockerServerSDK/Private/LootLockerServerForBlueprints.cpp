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

FString ULootLockerServerForBlueprints::StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::StartSession(FLootLockerServerAuthResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::MaintainSession(FLootLockerServerMaintainSessionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerMaintainSessionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GameApiTokenExchange(const FString& GameApiSessionToken, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GameApiTokenExchange(GameApiSessionToken, FLootLockerServerTokenExchangeResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerTokenExchangeResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GameApiUserImpersonation(const FString& PlayerUlid, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GameApiUserImpersonation(PlayerUlid, FLootLockerServerTokenExchangeResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerTokenExchangeResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ListLeaderboards(int32 Count, int32 After, const FLootLockerServerListLeaderboardsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ListLeaderboards(Count, After, FLootLockerServerListLeaderboardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListLeaderboardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetLeaderboard(LeaderboardKey, FLootLockerServerGetLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::CreateLeaderboard(LeaderboardKey, Name, Type, HasMetadata, DirectionMethod, EnableGameApiWrites, OverwriteScoreOnSubmit, FLootLockerServerCreateLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerCreateLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UpdateLeaderboard(LeaderboardKey, NewLeaderboardKey, Name, DirectionMethod, EnableGameApiWrites, OverwriteScoreOnSubmit, FLootLockerServerUpdateLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUpdateLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::DeleteLeaderboard(LeaderboardKey, FLootLockerServerDeleteLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::SubmitScore(LeaderboardKey, MemberID, Score, Metadata, FLootLockerServerLeaderboardSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerLeaderboardSubmitScoreResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetAllMemberRanks(const FString MemberID, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetAllMemberRanks(MemberID, FLootLockerServerGetAllMemberRanksResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAllMemberRanksResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedAllMemberRanks(const FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedAllMemberRanks(MemberID, Count, After, FLootLockerServerGetAllMemberRanksResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAllMemberRanksResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetScoresFromLeaderboard(const FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetScoresFromLeaderboard(LeaderboardKey, FLootLockerServerGetScoresFromLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetScoresFromLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedScoresFromLeaderboard(LeaderboardKey, Count, After, FLootLockerServerGetScoresFromLeaderboardResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetScoresFromLeaderboardResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetLeaderboardSchedule(LeaderboardKey, FLootLockerServerGetLeaderboardScheduleResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetLeaderboardScheduleResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::CreateLeaderboardSchedule(LeaderboardKey, CronExpression, FLootLockerServerGetLeaderboardScheduleResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetLeaderboardScheduleResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::DeleteLeaderboardSchedule(LeaderboardKey, FLootLockerServerDeleteLeaderboardScheduleResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::ListLeaderboardArchive(LeaderboardKey, FLootLockerServerLeaderboardArchiveResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerLeaderboardArchiveResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::GetLeaderboardArchive(Key, Count, After, FLootLockerServerLeaderboardArchiveDetailResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerLeaderboardArchiveDetailsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::InvokeTriggerForPlayer(TriggerName, PlayerID, FLootLockerServerInvokeTriggerResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerInvokeTriggerResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPersistentStorageForPlayer(int PlayerID, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPersistentStorageForPlayer(PlayerID, FLootLockerServerGetPersistentStorageForPlayersResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPersistentStorageForPlayersResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPersistentStorageForPlayers(PlayerIDs, FLootLockerServerGetPersistentStorageForPlayersResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPersistentStorageForPlayersResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetEntirePublicPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetEntirePublicPersistentStorageForPlayers(PlayerIDs, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, Keys, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UpdatePersistentStorageForPlayersAndKeys(StorageEntriesToUpdate, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::DeletePersistentStorageForPlayersAndKeys(PlayerIDs, Keys, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Character

FString ULootLockerServerForBlueprints::GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerCharacters(PlayerID, FLootLockerServerGetPlayerCharacterResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerCharactersResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerCharacterInventory(PlayerID, CharacterID, FLootLockerServerGetCharacterInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetCharacterInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedPlayerCharacterInventory(PlayerID, CharacterID, Count, After, FLootLockerServerGetCharacterInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetCharacterInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerCharacterLoadout(PlayerID, CharacterID, FLootLockerServerGetCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(PlayerID, CharacterID, AssetInstanceID, FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(PlayerID, CharacterID, AssetID, AssetVariationID, FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(PlayerID, CharacterID, AssetID, RentalOptionID, FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UnequipAssetFromPlayerCharacterLoadout(PlayerID, CharacterID, InstanceID, FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUnequipAssetFromCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Heroes

FString ULootLockerServerForBlueprints::GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerHeroes(PlayerID, FLootLockerServerGetPlayerHeroResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerHeroesResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerHeroInventory(PlayerID, HeroID, FLootLockerServerGetHeroInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetHeroInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedPlayerHeroInventory(PlayerID, HeroID, Count, After, FLootLockerServerGetHeroInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetHeroInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerHeroLoadout(PlayerID, HeroID, FLootLockerServerGetHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(PlayerID, HeroID, AssetInstanceID, FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(PlayerID, HeroID, AssetID, AssetVariationID, FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(PlayerID, HeroID, AssetID, RentalOptionID, FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UnequipAssetFromPlayerHeroLoadout(PlayerID, HeroID, InstanceID, FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUnequipAssetFromHeroLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player Inventory

FString ULootLockerServerForBlueprints::GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetUniversalInventory(FLootLockerServerGetUniversalInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetUniversalInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerInventory(PlayerID, FLootLockerServerGetPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedPlayerInventory(PlayerID, Count, After, FLootLockerServerGetPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerLoadout(PlayerID, FLootLockerServerGetPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetId(PlayerID, AssetID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetInstanceId(PlayerID, AssetInstanceID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(PlayerID, AssetID, AssetVariationID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(PlayerID, AssetID, RentalOptionID, FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerEquipAssetToPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UnequipAssetFromPlayerLoadout(PlayerID, InstanceID, FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerUnequipAssetFromPlayerLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetID(PlayerID, AssetID, FLootLockerServerAddAssetToPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAddAssetToPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetIDAndVariationID(PlayerID, AssetID, VariationID, FLootLockerServerAddAssetToPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAddAssetToPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(PlayerID, AssetID, RentalOptionID, FLootLockerServerAddAssetToPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAddAssetToPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetID(PlayerID, AssetsToAdd, AssetsToRemove, FLootLockerServerAlterPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAlterPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(PlayerID, AssetsToAdd, AssetsToRemove, FLootLockerServerAlterPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAlterPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(PlayerID, AssetsToAdd, AssetsToRemove, FLootLockerServerAlterPlayerInventoryResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAlterPlayerInventoryResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Assets
FString ULootLockerServerForBlueprints::GetAssets(bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest) 
{
    return ULootLockerServerForCpp::GetAssets(FLootLockerServerGetAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), IncludeUGC);
}

FString ULootLockerServerForBlueprints::GetPaginatedAssets(int Count, int After, bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedAssets(Count, After, FLootLockerServerGetAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), IncludeUGC);
}

FString ULootLockerServerForBlueprints::GetAssetsByContext(int Count, int After, int Context, bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP &OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetAssetsByContext(Count, After, Context, FLootLockerServerGetAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGetAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), IncludeUGC);
}

FString ULootLockerServerForBlueprints::ListAssets(const FLootLockerServerListAssetsRequest& Request, int PerPage, int Page, const FLootLockerServerListAssetsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ListAssets(Request, PerPage, Page, FLootLockerServerListAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListAssetsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ListAssetsWithDefaultParameters(const FLootLockerServerListAssetsResponseBP& OnCompletedRequest)
{
    return ListAssets(FLootLockerServerListAssetsRequest(), 0, 0, OnCompletedRequest);
}

FString ULootLockerServerForBlueprints::ListContexts(int PerPage, int Page, const FLootLockerServerListContextsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ListContexts(PerPage, Page, FLootLockerServerListContextsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListContextsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Asset Instances
FString ULootLockerServerForBlueprints::GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetKeyValuePairsFromAssetInstance(PlayerID, AssetInstanceID, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetAssetInstanceKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairItemResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AddKeyValuePairToAssetInstance(PlayerID, AssetInstanceID, Key, Value, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UpdateKeyValuePairsOnAssetInstance(PlayerID, AssetInstanceID, KeyValuePairs, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UpdateKeyValuePairOnAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, Key, Value, FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairItemResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::DeleteKeyValuePairFromAssetInstanceById(PlayerID, AssetInstanceID, KeyValuePairID, FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerAssetInstanceKeyValuePairsListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Friends
FString ULootLockerServerForBlueprints::ListFriendsForPlayer(const FString& PlayerULID, int Page, int PerPage, const FLootLockerServerListFriendsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ListFriendsForPlayer(PlayerULID, Page, PerPage, FLootLockerServerListFriendsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListFriendsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Connected Accounts
FString ULootLockerServerForBlueprints::ListConnectedAccounts(const TArray<FString>& PlayerULIDs, const TArray<int>& LegacyPlayerIDs, const FLootLockerServerListConnectedAccountsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ListConnectedAccounts(PlayerULIDs, LegacyPlayerIDs, FLootLockerServerListConnectedAccountsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListConnectedAccountsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Drop Tables
FString ULootLockerServerForBlueprints::ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ComputeAndLockDropTable(PlayerID, DropTableID, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ComputeAndLockDropTableForTag(PlayerID, DropTableID, Tag, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ComputeAndLockDropTableWithAssetInformation(PlayerID, DropTableID, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ComputeAndLockDropTableForTagWithAssetInformation(PlayerID, DropTableID, Tag, FLootLockerServerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerComputeAndLockDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::PickDropsFromDropTable(PlayerID, DropTableID, DropTableItemIDsToPick, FLootLockerServerPickFromDropTableResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPickFromDropTableResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player
FString ULootLockerServerForBlueprints::LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequest) 
{
    return ULootLockerServerForCpp::LookupPlayerNames(IdsToLookUp, FLootLockerServerPlayerNameLookupResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerPlayerNameLookupResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPlayerInfoFromGameSessionToken(GameSessionTokensToLookUp, FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::CreatePlayer(ELootLockerServerCreatePlayerPlatforms Platform, const FString& PlatformPlayerIdentifier, const FLootLockerServerCreatePlayerResponseBP& OnCompletedRequest) 
{
    return ULootLockerServerForCpp::CreatePlayer(Platform, PlatformPlayerIdentifier, FLootLockerServerCreatePlayerResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerServerCreatePlayerResponse Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player Files
FString ULootLockerServerForBlueprints::ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ListFilesForPlayer(PlayerID, FLootLockerServerPlayerFileListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerFileListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetFileForPlayerByID(PlayerID, FileID, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::DeleteFileForPlayerByID(PlayerID, FileID, FLootLockerServerPlayerFileDeleteResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerFileDeleteResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UploadFileForPlayer(PlayerID, FilePath, Purpose, IsPublic, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UploadRawDataToPlayerFile(PlayerID, RawData, FileName, Purpose, IsPublic, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UpdateFileForPlayer(PlayerID, FileID, FilePath, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::UpdatePlayerFileWithRawData(PlayerID, FileID, RawData, FileName, FLootLockerServerSinglePlayerFileResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerFileResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Game Progressions
FString ULootLockerServerForBlueprints::GetProgressions(const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetProgressions(FLootLockerServerGameProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGameProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedProgressions(Count, After, FLootLockerServerGameProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerGameProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetProgressionByKey(ProgressionKey, FLootLockerServerSingleGameProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleGameProgressionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetTiersForProgression(ProgressionKey, FLootLockerServerProgressionTiersResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerProgressionTiersResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedTiersForProgression(ProgressionKey, Count, After, FLootLockerServerProgressionTiersResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerProgressionTiersResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Player Progressions

FString ULootLockerServerForBlueprints::GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetProgressionsForPlayer(PlayerID, FLootLockerServerPlayerProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedProgressionsForPlayer(PlayerID, Count, After, FLootLockerServerPlayerProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerPlayerProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetProgressionForPlayerByKey(PlayerID, ProgressionKey, FLootLockerServerSinglePlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AddPointsToProgressionForPlayer(PlayerID, ProgressionKey, Amount, FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::SubtractPointsFromProgressionForPlayer(PlayerID, ProgressionKey, Amount, FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ResetProgressionForPlayer(PlayerID, ProgressionKey, FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSinglePlayerProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::DeleteProgressionForPlayer(PlayerID, ProgressionKey, FLootLockerServerDeletePlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Character Progressions

FString ULootLockerServerForBlueprints::GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetProgressionsForCharacter(PlayerID, CharacterID, FLootLockerServerCharacterProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerCharacterProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetPaginatedProgressionsForCharacter(PlayerID, CharacterID, Count, After, FLootLockerServerCharacterProgressionListResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerCharacterProgressionListResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::GetProgressionForCharacterByKey(PlayerID, CharacterID, ProgressionKey, FLootLockerServerSingleCharacterProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::AddPointsToProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::SubtractPointsFromProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, Amount, FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ResetProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSingleCharacterProgressionWithRewardsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::DeleteProgressionForCharacter(PlayerID, CharacterID, ProgressionKey, FLootLockerServerDeleteCharacterProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

//Asset Instance Progression

FString ULootLockerServerForBlueprints::GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::GetProgressionForAssetInstance(PlayerId, AssetInstanceId, FLootLockerServerInstanceProgressionListResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerInstanceProgressionListResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::GetPaginatedProgressionForAssetInstance(PlayerId, AssetInstanceId, Count, After, FLootLockerServerInstanceProgressionListResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerInstanceProgressionListResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::GetProgressionByKeyForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, FLootLockerServerSingleInstanceProgressionResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::AddPointsToProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionWithRewardsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::SubtractPointsFromProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, Amount, FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionWithRewardsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::ResetProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerSingleInstanceProgressionWithRewardsResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerForBlueprints::DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseBP& OnCompletedRequestBP)
{
    return ULootLockerServerForCpp::DeleteProgressionForAssetInstance(PlayerId, AssetInstanceId, ProgressionKey, FLootLockerServerDeleteInstanceProgressionResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerServerResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

// Currencies
FString ULootLockerServerForBlueprints::ListCurrencies(const FLootLockerServerListCurrenciesResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::ListCurrencies(FLootLockerServerListCurrenciesResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerListCurrenciesResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

// Balances

FString ULootLockerServerForBlueprints::ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::ListBalancesInWallet(WalletID, FLootLockerServerListBalancesForWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerListBalancesForWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

FString ULootLockerServerForBlueprints::GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::GetWalletByWalletID(WalletID, FLootLockerServerGetWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerGetWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

FString ULootLockerServerForBlueprints::GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::GetWalletByHolderID(HolderULID, HolderType, FLootLockerServerGetWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerGetWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

FString ULootLockerServerForBlueprints::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::CreditBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerServerCreditWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerCreditWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

FString ULootLockerServerForBlueprints::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::DebitBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerServerDebitWalletResponseDelegate::CreateLambda(
        [OnComplete](const FLootLockerServerDebitWalletResponse& Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }
    ));
}

// Metadata

FString ULootLockerServerForBlueprints::ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::ListMetadata(Source, SourceID, Page, PerPage, FLootLockerServerListMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerListMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
}

FString ULootLockerServerForBlueprints::ListMetadataWithTags(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::ListMetadataWithTags(Source, SourceID, Tags, Page, PerPage, FLootLockerServerListMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerListMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
}

FString ULootLockerServerForBlueprints::GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerServerGetMetadataResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::GetMetadata(Source, SourceID, Key, FLootLockerServerGetMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerGetMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
}

FString ULootLockerServerForBlueprints::GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerServerGetMultisourceMetadataResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::GetMultisourceMetadata(SourcesAndKeysToGet, FLootLockerServerGetMultisourceMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerGetMultisourceMetadataResponse& Response) {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles);
}

FString ULootLockerServerForBlueprints::ParseLootLockerServerMetadataEntry(const FLootLockerServerMetadataEntry& Entry,
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
        return "";
    }
    switch (Entry.Type)
    {
    case ELootLockerServerMetadataTypes::String:
    {
        if (Entry.TryGetValueAsString(StringValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnString;
            return "";
        }
        ErrorMessage = "Value \"" + ValueToParse + "\" could not be parsed";
        return "";
    }
    case ELootLockerServerMetadataTypes::Number:
    {
        if (!FCString::IsNumeric(*ValueToParse))
        {
            ErrorMessage = "Could not parse value \"" + ValueToParse + "\" as Number because it is not numeric";
            return "";
        }
        // Parse as float
        if (ValueToParse.Contains(".") && Entry.TryGetValueAsFloat(FloatValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnFloat;
            return "";
        }
        // Parse as int
        if (Entry.TryGetValueAsInteger(IntegerValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnInteger;
            return "";
        }
        //Treat as non int or float value, likely BigInt or BigDecimal
        MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnNumber;
        NumberString = ValueToParse;
        return "";
    }
    case ELootLockerServerMetadataTypes::Bool:
    {
        if (Entry.TryGetValueAsBool(BoolValue))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnBool;
            return "";
        }
        ErrorMessage = "Value \"" + ValueToParse + "\" could not be parsed as boolean value";
        return "";
    }
    case ELootLockerServerMetadataTypes::Json:
    {
        TSharedPtr<FJsonObject> JsonObject = nullptr;
        if (Entry.TryGetValueAsJsonObject(JsonObject) && JsonObject.IsValid())
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnJson;
            JsonStringValue = ValueToParse;
            return "";
        }
        TArray<TSharedPtr<FJsonValue>> OutputJsonArray;
        if (Entry.TryGetValueAsJsonArray(OutputJsonArray))
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnJson;
            JsonStringValue = ValueToParse;
            return "";
        }
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because it is not a valid Json String";
        return "";
    }
    case ELootLockerServerMetadataTypes::Base64:
    {
        if (Entry.TryGetValueAsBase64(Base64Value) && !Base64Value.Content_type.IsEmpty())
        {
            MetadataTypeSwitch = ELootLockerServerMetadataParserOutputTypes::OnBase64;
            return "";
        }
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because it is not a valid LootLockerServer Metadata Base64 Object";
        return "";
    }
    default:
    {
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because the type \"" + ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerMetadataTypes"), static_cast<int32>(Entry.Type)) + "\" was not recognized by the parser";
        return "";
    }
    }
}

FString ULootLockerServerForBlueprints::SetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerServerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerServerSetMetadataResponseBP& OnComplete)
{
    return ULootLockerServerForCpp::SetMetadata(Source, SourceID, MetadataToActionsToPerform, FLootLockerServerSetMetadataResponseDelegate::CreateLambda([OnComplete](const FLootLockerServerSetMetadataResponse& Response) {
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

FString ULootLockerServerForBlueprints::MakeMetadataActionJson(ELootLockerServerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access, bool& Succeeded, FLootLockerServerSetMetadataAction& ConstructedEntry)
{
    TArray<TSharedPtr<FJsonValue>> JsonArrayValue;
    if(LootLockerServerUtilities::JsonArrayFromFString(Value, JsonArrayValue))
    {
        ConstructedEntry = FLootLockerServerSetMetadataAction{Action, FLootLockerServerMetadataEntry::MakeJsonArrayEntry(Key, Tags, Access, JsonArrayValue)};
        Succeeded = true;
        return "";
    }

    TSharedPtr<FJsonObject> JsonObjectValue = LootLockerServerUtilities::JsonObjectFromFString(Value);
    if(JsonObjectValue.IsValid())
    {
         ConstructedEntry = FLootLockerServerSetMetadataAction{Action, FLootLockerServerMetadataEntry::MakeJsonObjectEntry(Key, Tags, Access, *JsonObjectValue)};
         Succeeded = true;
         return "";
    }
    Succeeded = false;
    return "";
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

FString ULootLockerServerForBlueprints::SendNotificationToPlayerWithoutContent(const FString& NotificationType,
	ELootLockerServerNotificationPriority Priority, 
    const FString& RecipientPlayerUlid,
	const TArray<FLootLockerServerNotificationProperty>& Properties,
	const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequest)
{
    return ULootLockerServerForCpp::SendNotificationToPlayerWithoutContent(NotificationType, Priority, RecipientPlayerUlid, Properties, FLootLockerServerSendNotificationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServerSendNotificationsResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}
