// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerLeaderboardRequest.h"

#include "LootLockerServerSDK/Private/Utils/LootLockerServerUtilities.h"
#include "LootLockerServerEndpoints.h"

ULootLockerServerHttpClient* ULootLockerServerLeaderboardRequest::HttpClient = nullptr;

// Sets default values for this component's properties
ULootLockerServerLeaderboardRequest::ULootLockerServerLeaderboardRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerLeaderboardRequest::CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequestBP,const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
	LootLockerServerAPIUtilities<FLootLockerServerCreateLeaderboardResponse>::CallAPI(HttpClient, CreateLeaderboardRequest, ULootLockerServerEndpoints::CreateLeaderboard, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::UpdateLeaderboard(const FString& LeaderboardKey, const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequest, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	LootLockerServerAPIUtilities<FLootLockerServerUpdateLeaderboardResponse>::CallAPI(HttpClient, UpdateLeaderboardRequest, ULootLockerServerEndpoints::UpdateLeaderboard, {LeaderboardKey}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::DeleteLeaderboard(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	LootLockerServerAPIUtilities<FLootLockerServerResponse>::CallAPI(HttpClient, FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteLeaderboard, {LeaderboardKey}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::SubmitScore(const FString& LeaderboardKey, const FLootLockerServerLeaderboardSubmitScoreRequest& SubmitScoreRequest, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequestBP, const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest)
{
	LootLockerServerAPIUtilities<FLootLockerServerLeaderboardSubmitScoreResponse>::CallAPI(HttpClient, SubmitScoreRequest, ULootLockerServerEndpoints::SubmitScore, { LeaderboardKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetAllMemberRanks(const FString& MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequestBP, const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
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
	LootLockerServerAPIUtilities<FLootLockerServerGetAllMemberRanksResponse>::CallAPI(HttpClient, FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllMemberRanks, { MemberID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardRequest::GetScoresFromLeaderboard(const FString LeaderboardKey, const int Count, const int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("count", FString::FromInt(Count > 0 ? Count : 50));
	if (After > 0)
	{
		QueryParams.Add("after", FString::FromInt(After));
	}
	LootLockerServerAPIUtilities<FLootLockerServerGetScoresFromLeaderboardResponse>::CallAPI(HttpClient, FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetScoresFromLeaderboard, { LeaderboardKey }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
