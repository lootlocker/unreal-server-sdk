// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerLeaderboardRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"

// Sets default values for this component's properties
ULootLockerServerLeaderboardRequest::ULootLockerServerLeaderboardRequest()
{
}

void ULootLockerServerLeaderboardRequest::ListLeaderboards(int Count, int After, const FLootLockerServerListLeaderboardsResponseBP& OnCompletedRequestBP, const FLootLockerServerListLeaderboardsResponseDelegate& OnCompletedRequest)
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
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerListLeaderboardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ListLeaderboards, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerGetLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetLeaderboard, {LeaderboardKey}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequestBP,const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreateLeaderboardResponse>(CreateLeaderboardRequest, ULootLockerServerEndpoints::CreateLeaderboard, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::UpdateLeaderboard(const FString& LeaderboardKey, const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequest, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerUpdateLeaderboardResponse>(UpdateLeaderboardRequest, ULootLockerServerEndpoints::UpdateLeaderboard, {LeaderboardKey}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::DeleteLeaderboard(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteLeaderboard, {LeaderboardKey}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::SubmitScore(const FString& LeaderboardKey, const FLootLockerServerLeaderboardSubmitScoreRequest& SubmitScoreRequest, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequestBP, const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerLeaderboardSubmitScoreResponse>(SubmitScoreRequest, ULootLockerServerEndpoints::SubmitScore, { LeaderboardKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetAllMemberRanks(const FString& MemberID, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequestBP, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAllMemberRanksResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllMemberRanks, { MemberID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetPaginatedAllMemberRanks(const FString& MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequestBP, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
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
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAllMemberRanksResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllMemberRanks, { MemberID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(const FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetScoresFromLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetScoresFromLeaderboard, { LeaderboardKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetPaginatedScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("count", FString::FromInt(Count > 0 ? Count : 50));
	if (After > 0)
	{
		QueryParams.Add("after", FString::FromInt(After));
	}
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetScoresFromLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetScoresFromLeaderboard, { LeaderboardKey }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequestBP, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequestBP, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest) 
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerCreateLeaderboardScheduleRequest{CronExpression}, ULootLockerServerEndpoints::CreateLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseBP& OnCompletedRequestBP, const FLootLockerServerDeleteLeaderboardScheduleResponseDelegate& OnCompletedRequest) 
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}
