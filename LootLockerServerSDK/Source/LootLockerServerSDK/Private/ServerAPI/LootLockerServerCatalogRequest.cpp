// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCatalogRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerCatalogRequest::ULootLockerServerCatalogRequest()
{
}

FString ULootLockerServerCatalogRequest::ListCatalogItemsByKey(const FString& CatalogKey, int Count, const FString& After, const FLootLockerServerListCatalogPricesResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0)
    {
        QueryParams.Add("per_page", FString::FromInt(Count));
    }
    if (!After.IsEmpty())
    {
        QueryParams.Add("cursor", After);
    }

    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListCatalogPricesResponse>(
        FLootLockerServerEmptyRequest{},
        ULootLockerServerEndpoints::ListCatalogItemsByKey,
        { CatalogKey },
        QueryParams,
        OnResponseCompleted);
}
