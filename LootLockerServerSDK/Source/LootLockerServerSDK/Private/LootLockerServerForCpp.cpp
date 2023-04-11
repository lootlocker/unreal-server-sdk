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
		LeaderboardKey,
		Name,
		DirectionMethod,
		EnableGameApiWrites,
		OverwriteScoreOnSubmit,
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

void ULootLockerServerCppInterface::InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerTriggerRequest::InvokeTriggerForPlayer(TriggerName, PlayerID, FLootLockerServerInvokeTriggerResponseBP(), OnCompletedRequest);
}
