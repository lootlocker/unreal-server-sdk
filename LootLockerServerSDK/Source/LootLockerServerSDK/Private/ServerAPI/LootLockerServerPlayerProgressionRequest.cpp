// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerProgressionRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerPlayerProgressionRequest::ULootLockerServerPlayerProgressionRequest()
{
}

void ULootLockerServerPlayerProgressionRequest::GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForPlayer, { PlayerID }, {}, FLootLockerServerPlayerProgressionListResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest)
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForPlayer, { PlayerID }, QueryParams, FLootLockerServerPlayerProgressionListResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsByKeyForPlayer, { PlayerID, ProgressionKey }, {}, FLootLockerServerSinglePlayerProgressionResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::AddPointsToProgressionForPlayer, { PlayerID, ProgressionKey }, {}, FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::SubtractPointsFromProgressionForPlayer, { PlayerID, ProgressionKey }, {}, FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerProgressionWithRewardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ResetProgressionForPlayer, { PlayerID, ProgressionKey }, {}, FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerProgressionRequest::DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteProgressionForPlayer, { PlayerID, ProgressionKey }, {}, FLootLockerServerDeletePlayerProgressionResponseBP(), OnCompletedRequest);
}

