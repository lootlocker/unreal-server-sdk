// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCurrencyRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerCurrencyRequest::ULootLockerServerCurrencyRequest()
{
}

FString ULootLockerServerCurrencyRequest::ListCurrencies(const FLootLockerServerListCurrenciesResponseDelegate& OnResponseCompleted)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListCurrenciesResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListCurrencies, {}, {}, OnResponseCompleted);
}
