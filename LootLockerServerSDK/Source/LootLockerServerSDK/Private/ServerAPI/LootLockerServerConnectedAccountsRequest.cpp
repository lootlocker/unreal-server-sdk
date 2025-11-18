// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerConnectedAccountsRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerConnectedAccountsRequest::ULootLockerServerConnectedAccountsRequest()
{
}

void ULootLockerServerConnectedAccountsRequest::ListConnectedAccounts(const FString& PlayerULID, const FLootLockerServerListConnectedAccountsResponseBP& OnResponseCompletedBP, const FLootLockerServerListConnectedAccountsResponseDelegate& OnResponseCompleted)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerListConnectedAccountsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListConnectedAccounts, { PlayerULID }, {}, OnResponseCompletedBP, OnResponseCompleted);
}
