// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerProgressionRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerPlayerProgressionRequest::ULootLockerServerPlayerProgressionRequest()
{
}

void ULootLockerServerPlayerProgressionRequest::GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForPlayer, { PlayerID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(Count > 0)
    {
        QueryParams.Add("count", FString::FromInt(Count));
    }
    if(!After.IsEmpty())
    {
        QueryParams.Add("after", After);
    }
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForPlayer, { PlayerID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerPlayerSingleProgressionResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsByKeyForPlayer, { PlayerID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::AddPointsProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::AddPointsToProgressionForPlayer, { PlayerID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::SubtractPointsFromProgressionForPlayer, { PlayerID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionWithRewardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ResetProgressionForPlayer, { PlayerID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequestBP, const FLootLockerServerDeletePlayerProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteProgressionForPlayer, { PlayerID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

