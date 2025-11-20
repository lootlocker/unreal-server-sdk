// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerConnectedAccountsRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerConnectedAccountsRequest::ULootLockerServerConnectedAccountsRequest()
{
}

void ULootLockerServerConnectedAccountsRequest::ListConnectedAccounts(const TArray<FString>& PlayerULIDs, const TArray<int>& LegacyPlayerIDs, const FLootLockerServerListConnectedAccountsResponseBP& OnResponseCompletedBP, const FLootLockerServerListConnectedAccountsResponseDelegate& OnResponseCompleted)
{
    FLootLockerServerListConnectedAccountsRequest Request;
    Request.Player_ids = PlayerULIDs;
    Request.Legacy_player_ids = LegacyPlayerIDs;
    
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerListConnectedAccountsResponse>(Request, ULootLockerServerEndpoints::ListConnectedAccounts, {}, {}, OnResponseCompletedBP, OnResponseCompleted);
}
