// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerLeaderboardRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"

// Sets default values for this component's properties
ULootLockerServerLeaderboardRequest::ULootLockerServerLeaderboardRequest()
{
}

FString ULootLockerServerLeaderboardRequest::ListLeaderboards(int Count, int After, const FLootLockerServerListLeaderboardsResponseDelegate& OnCompletedRequest)
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
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListLeaderboardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ListLeaderboards, {}, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetLeaderboard, {LeaderboardKey}, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreateLeaderboardResponse>(CreateLeaderboardRequest, ULootLockerServerEndpoints::CreateLeaderboard, {}, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::UpdateLeaderboard(const FString& LeaderboardKey, const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequest, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerUpdateLeaderboardResponse>(UpdateLeaderboardRequest, ULootLockerServerEndpoints::UpdateLeaderboard, {LeaderboardKey}, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::DeleteLeaderboard(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteLeaderboard, {LeaderboardKey}, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::SubmitScore(const FString& LeaderboardKey, const FLootLockerServerLeaderboardSubmitScoreRequest& SubmitScoreRequest, const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerLeaderboardSubmitScoreResponse>(SubmitScoreRequest, ULootLockerServerEndpoints::SubmitScore, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::IncrementScore(const FString& LeaderboardKey, const FLootLockerServerLeaderboardIncrementScoreRequest& IncrementScoreRequest, const FLootLockerServerLeaderboardIncrementScoreResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerLeaderboardSubmitScoreResponse>(IncrementScoreRequest, ULootLockerServerEndpoints::IncrementScore, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::GetAllMemberRanks(const FString& MemberID, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAllMemberRanksResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllMemberRanks, { MemberID }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::GetPaginatedAllMemberRanks(const FString& MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
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
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAllMemberRanksResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllMemberRanks, { MemberID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(const FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetScoresFromLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetScoresFromLeaderboard, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::GetPaginatedScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("count", FString::FromInt(Count > 0 ? Count : 50));
	if (After > 0)
	{
		QueryParams.Add("after", FString::FromInt(After));
	}
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetScoresFromLeaderboardResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetScoresFromLeaderboard, { LeaderboardKey }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest) 
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerCreateLeaderboardScheduleRequest{CronExpression}, ULootLockerServerEndpoints::CreateLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseDelegate& OnCompletedRequest) 
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetLeaderboardScheduleResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteLeaderboardSchedule, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::RequestManualLeaderboardReset(const FString& LeaderboardKey, const FLootLockerServerCreateManualLeaderboardResetRequest& Request, const FLootLockerServerRequestManualLeaderboardResetResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerManualLeaderboardResetResponse>(Request, ULootLockerServerEndpoints::RequestManualLeaderboardReset, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::ListManualLeaderboardResets(const FString& LeaderboardKey, const FLootLockerServerListManualLeaderboardResetsResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListManualLeaderboardResetsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ListManualLeaderboardResets, { LeaderboardKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::GetManualLeaderboardReset(const FString& LeaderboardKey, const FString& ResetId, const FLootLockerServerGetManualLeaderboardResetResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerManualLeaderboardResetResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetManualLeaderboardReset, { LeaderboardKey, ResetId }, {}, OnCompletedRequest);
}

FString ULootLockerServerLeaderboardRequest::CancelManualLeaderboardReset(const FString& LeaderboardKey, const FString& ResetId, const FLootLockerServerCancelManualLeaderboardResetResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::CancelManualLeaderboardReset, { LeaderboardKey, ResetId }, {}, OnCompletedRequest);
}
