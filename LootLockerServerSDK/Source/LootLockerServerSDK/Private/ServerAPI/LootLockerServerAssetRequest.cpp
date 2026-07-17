// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerAssetRequest::ULootLockerServerAssetRequest()
{
}

FString ULootLockerServerAssetRequest::GetAssets(int Count, int After, int Context, bool IncludeUGC, const FLootLockerServerGetAssetsResponseDelegate& OnCompletedRequest)
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetAssetsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssets, {}, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairs, { PlayerID, AssetInstanceID }, {}, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAssetInstanceKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerCreateAssetInstanceKeyValuePairRequest { Key, Value }, ULootLockerServerEndpoints::AddKeyValuePairToAssetInstance, { PlayerID, AssetInstanceID }, {}, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerUpdateOneOrMoreKeyValuePairsOnAssetInstanceRequest{KeyValuePairs}, ULootLockerServerEndpoints::UpdateKeyValuePairs, { PlayerID, AssetInstanceID }, {}, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairItemResponse>(FLootLockerServerCreateAssetInstanceKeyValuePairRequest { Key, Value }, ULootLockerServerEndpoints::UpdateKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssetInstanceKeyValuePairsListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeleteKeyValuePairById, { PlayerID, AssetInstanceID, KeyValuePairID }, {}, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::ListAssets(const FLootLockerServerListAssetsRequest& Request, int PerPage, int Page, ELootLockerServerOrderAssetListBy OrderBy, ELootLockerServerOrderAssetListDirection OrderDirection, const FLootLockerServerListAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if(PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if(OrderBy != ELootLockerServerOrderAssetListBy::None)
    {
        QueryParams.Add("order_by", ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerOrderAssetListBy"), static_cast<int32>(OrderBy)).ToLower());
    }
    if(OrderDirection != ELootLockerServerOrderAssetListDirection::None)
    {
        QueryParams.Add("order_direction", ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerOrderAssetListDirection"), static_cast<int32>(OrderDirection)).ToLower());
    }
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListAssetsResponse>(Request, ULootLockerServerEndpoints::ListAssets, {}, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerAssetRequest::ListContexts(int PerPage, int Page, const FLootLockerServerListContextsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if(PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListContextsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListContexts, {}, QueryParams, OnCompletedRequest);
}

