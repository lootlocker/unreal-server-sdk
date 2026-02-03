// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerConnectedAccountsRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerConnectedAccountsRequest::ULootLockerServerConnectedAccountsRequest()
{
}

FString ULootLockerServerConnectedAccountsRequest::ListConnectedAccounts(const TArray<FString>& PlayerULIDs, const TArray<int>& LegacyPlayerIDs, const FLootLockerServerListConnectedAccountsResponseDelegate& OnResponseCompleted)
{
    FLootLockerServerListConnectedAccountsRequest Request;
    Request.Player_ids = PlayerULIDs;
    Request.Legacy_player_ids = LegacyPlayerIDs;
    
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListConnectedAccountsResponse>(Request, ULootLockerServerEndpoints::ListConnectedAccounts, {}, {}, OnResponseCompleted);
}
