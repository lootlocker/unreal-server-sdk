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

void ULootLockerServerAssetRequest::GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairs, { PlayerID, AssetInstanceID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerCreateAssetInstanceKeyValuePairRequest { Key, Value }, ULootLockerServerEndpoints::AddKeyValuePairToAssetInstance, { PlayerID, AssetInstanceID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerUpdateOneOrMoreKeyValuePairsOnAssetInstanceRequest{KeyValuePairs}, ULootLockerServerEndpoints::UpdateKeyValuePairs, { PlayerID, AssetInstanceID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerCreateAssetInstanceKeyValuePairRequest { Key, Value }, ULootLockerServerEndpoints::UpdateKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerAssetRequest::DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeleteKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

