// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerInstanceProgressionRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerInstanceProgressionRequest::ULootLockerServerInstanceProgressionRequest()
{
}

FString ULootLockerServerInstanceProgressionRequest::GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerInstanceProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllInstanceProgressions, { PlayerId, AssetInstanceId }, {}, OnCompletedRequest);
}

FString ULootLockerServerInstanceProgressionRequest::GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest)
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerInstanceProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetAllInstanceProgressions, { PlayerId, AssetInstanceId }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerInstanceProgressionRequest::GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetSingleInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerInstanceProgressionRequest::AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::AddPointsToInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerInstanceProgressionRequest::SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::SubtractPointsFromInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerInstanceProgressionRequest::ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleInstanceProgressionWithRewardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ResetInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerInstanceProgressionRequest::DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteInstanceProgression, { PlayerId, AssetInstanceId, ProgressionKey }, {}, OnCompletedRequest);
}

