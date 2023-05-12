// Copyright (c) 2021 LootLocker


#include "LootLockerServerForCpp.h"

//Authentication
void ULootLockerServerForCpp::StartSession(const FLootLockerServerAuthResponseDelegate& OnCompleteRequest)
{
	ULootLockerServerAuthRequest::StartSession( FLootLockerServerAuthResponseBP(), OnCompleteRequest);
}

void ULootLockerServerForCpp::MaintainSession(const FLootLockerServerMaintainSessionResponseDelegate& OnCompleteRequest)
{
	ULootLockerServerAuthRequest::MaintainSession(FLootLockerServerMaintainSessionResponseBP(), OnCompleteRequest);
}

void ULootLockerServerForCpp::CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest)
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
	ULootLockerServerLeaderboardRequest::CreateLeaderboard(CreateLeaderboardRequest, FLootLockerServerCreateLeaderboardResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	const FLootLockerServerUpdateLeaderboardRequest UpdateLeaderboardRequest
	{
		NewLeaderboardKey,
		Name,
		DirectionMethod,
		EnableGameApiWrites,
		OverwriteScoreOnSubmit
	};
	ULootLockerServerLeaderboardRequest::UpdateLeaderboard(LeaderboardKey, UpdateLeaderboardRequest, FLootLockerServerUpdateLeaderboardResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerLeaderboardRequest::DeleteLeaderboard(LeaderboardKey, FLootLockerServerDeleteLeaderboardResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest)
{
	const FLootLockerServerLeaderboardSubmitScoreRequest SubmitScoreRequest
	{
		MemberID,
		Score,
		Metadata
	};
	ULootLockerServerLeaderboardRequest::SubmitScore(LeaderboardKey, SubmitScoreRequest, FLootLockerServerLeaderboardSubmitScoreResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetAllMemberRanks(const FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerLeaderboardRequest::GetAllMemberRanks(MemberID, Count, After, FLootLockerServerGetAllMemberRanksResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetScoresFromLeaderboard(FString LeaderboardKey, int Count, int After, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest) {
	ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(LeaderboardKey, Count, After, FLootLockerServerGetScoresFromLeaderboardResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerTriggerRequest::InvokeTriggerForPlayer(TriggerName, PlayerID, FLootLockerServerInvokeTriggerResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetPersistentStorageForPlayer(int PlayerID,	const FLootLockerServerGetPersistentStorageForPlayersResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(TArray{PlayerID}, FLootLockerServerGetPersistentStorageForPlayersResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(PlayerIDs, FLootLockerServerGetPersistentStorageForPlayersResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetEntirePublicPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, TArray<FString>(), FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::GetPublicPersistentStorageForPlayersAndKeys(PlayerIDs, Keys, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::UpdatePersistentStorageForPlayersAndKeys(StorageEntriesToUpdate, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs,	TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerStorageRequest::DeletePersistentStorageForPlayersAndKeys(PlayerIDs, Keys, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP(), OnCompletedRequest);
}

// Character

void ULootLockerServerForCpp::GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPlayerCharacters(PlayerID, FLootLockerServerGetPlayerCharacterResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPlayerCharacterInventory(PlayerID, CharacterID, FLootLockerServerGetCharacterInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPaginatedPlayerCharacterInventory(PlayerID, CharacterID, Count, After, FLootLockerServerGetCharacterInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::GetPlayerCharacterLoadout(PlayerID, CharacterID, FLootLockerServerGetCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(PlayerID, CharacterID, AssetInstanceID, FLootLockerServerEquipAssetToCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(PlayerID, CharacterID, AssetID, AssetVariationID, FLootLockerServerEquipAssetToCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(PlayerID, CharacterID, AssetID, RentalOptionID, FLootLockerServerEquipAssetToCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerForCpp::UnequipAssetFromPlayerLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerCharacterRequest::UnequipAssetFromPlayerLoadout(PlayerID, CharacterID, InstanceID, FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP(), OnCompletedRequest);
}
