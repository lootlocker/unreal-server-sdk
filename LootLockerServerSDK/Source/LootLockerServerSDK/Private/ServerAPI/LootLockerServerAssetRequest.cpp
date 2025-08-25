// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerAssetRequest::ULootLockerServerAssetRequest()
{
}

void ULootLockerServerAssetRequest::GetAssets(int Count, int After, int Context, bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequestBP, const FLootLockerServerGetAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("include_ugc", IncludeUGC ? "true" : "false");
    if (Count > 0)
    {
        QueryParams.Add("count", FString::FromInt(Count));
    }
    if (After > 0)
    {
        QueryParams.Add("after", FString::FromInt(After));
    }
    if (Context > -1)
    {
        QueryParams.Add("context_id", FString::FromInt(Context));
    }
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAssetsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssets, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairs, { PlayerID, AssetInstanceID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerCreateAssetInstanceKeyValuePairRequest { Key, Value }, ULootLockerServerEndpoints::AddKeyValuePairToAssetInstance, { PlayerID, AssetInstanceID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerUpdateOneOrMoreKeyValuePairsOnAssetInstanceRequest{KeyValuePairs}, ULootLockerServerEndpoints::UpdateKeyValuePairs, { PlayerID, AssetInstanceID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairItemResponse>(FLootLockerServerCreateAssetInstanceKeyValuePairRequest { Key, Value }, ULootLockerServerEndpoints::UpdateKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeleteKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::ListAssets(const FLootLockerServerListAssetsRequest& Request, int PerPage, int Page, const FLootLockerServerListAssetsResponseBP& OnCompletedRequestBP, const FLootLockerServerListAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if(PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerListAssetsResponse>(Request, ULootLockerServerEndpoints::ListAssets, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

