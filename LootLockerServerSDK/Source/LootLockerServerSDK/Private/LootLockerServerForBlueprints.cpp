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
		LeaderboardKey,
		Name,
		DirectionMethod,
		EnableGameApiWrites,
		OverwriteScoreOnSubmit,
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
