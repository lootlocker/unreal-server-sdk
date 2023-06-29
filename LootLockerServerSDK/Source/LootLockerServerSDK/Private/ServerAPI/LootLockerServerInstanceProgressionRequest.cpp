// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerInstanceProgressionRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerInstanceProgressionRequest::ULootLockerServerInstanceProgressionRequest()
{
}

void ULootLockerServerInstanceProgressionRequest::GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerInstanceProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllInstanceProgressions, { PlayerId, AssetInstanceId }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerInstanceProgressionRequest::GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0)
    {
        QueryParams.Add("count", FString::FromInt(Count));
    }
    if (!After.IsEmpty())
    {
        QueryParams.Add("after", After);
    }
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerInstanceProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllInstanceProgressions, { PlayerId, AssetInstanceId }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerInstanceProgressionRequest::GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleInstanceProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetSingleInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerInstanceProgressionRequest::AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::AddPointsToInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerInstanceProgressionRequest::SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::SubtractPointsFromInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerInstanceProgressionRequest::ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionWithRewardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ResetInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerInstanceProgressionRequest::DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseBP& OnCompletedRequestBP, const FLootLockerServerDeleteInstanceProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

