// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerLeaderboardRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"

// Sets default values for this component's properties
ULootLockerServerLeaderboardRequest::ULootLockerServerLeaderboardRequest()
{
}

void ULootLockerServerLeaderboardRequest::ListLeaderboards(int Count, int After, const FLootLockerServerListLeaderboardsResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	if(Count > 0)
	{
		QueryParams.Add("count", FString::FromInt(Count));
	}
	if (After > 0)
	{
		QueryParams.Add("after", FString::FromInt(After));
	}
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerListLeaderboardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ListLeaderboards, {}, QueryParams, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetLeaderboard, {LeaderboardKey}, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreateLeaderboardResponse>(CreateLeaderboardRequest, ULootLockerServerEndpoints::CreateLeaderboard, {}, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::UpdateLeaderboard(const FString& LeaderboardKey, const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequest, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerUpdateLeaderboardResponse>(UpdateLeaderboardRequest, ULootLockerServerEndpoints::UpdateLeaderboard, {LeaderboardKey}, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::DeleteLeaderboard(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteLeaderboard, {LeaderboardKey}, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::SubmitScore(const FString& LeaderboardKey, const FLootLockerServerLeaderboardSubmitScoreRequest& SubmitScoreRequest, const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerLeaderboardSubmitScoreResponse>(SubmitScoreRequest, ULootLockerServerEndpoints::SubmitScore, { LeaderboardKey }, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetAllMemberRanks(const FString& MemberID, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAllMemberRanksResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllMemberRanks, { MemberID }, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetPaginatedAllMemberRanks(const FString& MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	if(Count > 0)
	{
		QueryParams.Add("count", FString::FromInt(Count));
	}
	if (After > 0)
	{
		QueryParams.Add("after", FString::FromInt(After));
	}
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAllMemberRanksResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllMemberRanks, { MemberID }, QueryParams, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(const FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetScoresFromLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetScoresFromLeaderboard, { LeaderboardKey }, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetPaginatedScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("count", FString::FromInt(Count > 0 ? Count : 50));
	if (After > 0)
	{
		QueryParams.Add("after", FString::FromInt(After));
	}
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetScoresFromLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetScoresFromLeaderboard, { LeaderboardKey }, QueryParams, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest) 
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerCreateLeaderboardScheduleRequest{CronExpression}, ULootLockerServerEndpoints::CreateLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseDelegate& OnCompletedRequest) 
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequest);
}
