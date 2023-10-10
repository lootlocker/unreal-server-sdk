// Copyright (c) 2021 LootLocker

#include "LootLockerServerCurrencyRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerCurrencyRequest::ULootLockerServerCurrencyRequest()
{
}

void ULootLockerServerCurrencyRequest::ListCurrencies(const FLootLockerServerListCurrenciesResponseBP& OnResponseCompletedBP, const FLootLockerServerListCurrenciesResponseDelegate& OnResponseCompleted)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerListCurrenciesResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListCurrencies, {}, {}, OnResponseCompletedBP, OnResponseCompleted);
}
