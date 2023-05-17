// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerDropTableRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerDropTableRequest::ULootLockerServerDropTableRequest()
{
}

void ULootLockerServerDropTableRequest::ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(!Tag.IsEmpty())
    {
        QueryParams.Add("tag", Tag);
    }
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerDropTableRequest::ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("asset_details", "true");
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerDropTableRequest::ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("asset_details", "true");
    if(!Tag.IsEmpty())
    {
        QueryParams.Add("tag", Tag);
    }
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerComputeAndLockDropTableResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ComputeAndLockDropTable, { PlayerID, DropTableID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerDropTableRequest::PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseBP& OnCompletedRequestBP, const FLootLockerServerPickFromDropTableResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPickFromDropTableResponse>(FLootLockerServerPickDropsFromDropTableRequest{ DropTableItemIDsToPick }, ULootLockerServerEndpoints::PickDropsFromDropTable, { PlayerID, DropTableID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}
