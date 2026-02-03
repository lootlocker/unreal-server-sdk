// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerDropTableRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerDropTableRequest::ULootLockerServerDropTableRequest()
{
}

FString ULootLockerServerDropTableRequest::ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, {}, OnCompletedRequest);
}

FString ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(!Tag.IsEmpty())
    {
        QueryParams.Add("tag", Tag);
    }
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerDropTableRequest::ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("asset_details", "true");
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("asset_details", "true");
    if(!Tag.IsEmpty())
    {
        QueryParams.Add("tag", Tag);
    }
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerDropTableRequest::PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPickFromDropTableResponse>(FLootLockerServerPickDropsFromDropTableRequest{ DropTableItemIDsToPick }, ULootLockerServerEndpoints::PickDropsFromDropTable, { PlayerID, DropTableID }, {}, OnCompletedRequest);
}
