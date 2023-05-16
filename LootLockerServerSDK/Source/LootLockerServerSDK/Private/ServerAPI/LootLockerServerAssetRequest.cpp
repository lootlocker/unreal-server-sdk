// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerAssetRequest::ULootLockerServerAssetRequest()
{
}

void ULootLockerServerAssetRequest::GetAssets(const FLootLockerServerGetAssetsResponseBP& OnCompletedRequestBP, const FLootLockerServerGetAssetsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAssetsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssets, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::GetPaginatedAssets(int Count, int After, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequestBP, const FLootLockerServerGetAssetsResponseDelegate& OnCompletedRequest)
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAssetsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssets, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
