// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerItemRequestHandler.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerItemRequestHandler::ULootLockerServerItemRequestHandler()
{
}

FString ULootLockerServerItemRequestHandler::ListPlayerItems(int PlayerID, int Page, int PerPage, const FLootLockerServerListPlayerItemsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0)
    {
        QueryParams.Add("page", FString::FromInt(Page));
    }
    if (PerPage > 0)
    {
        QueryParams.Add("per_page", FString::FromInt(PerPage));
    }
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListPlayerItemsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerItems, { PlayerID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::GetPlayerItem(int PlayerID, const FString& InventoryId, const FLootLockerServerGetPlayerItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerItem, { PlayerID, InventoryId }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::DeletePlayerItem(int PlayerID, const FString& InventoryId, const FLootLockerServerDeletePlayerItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerDeletePlayerItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeletePlayerItem, { PlayerID, InventoryId }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::GrantItemToPlayer(int PlayerID, const FLootLockerServerGrantItemRequest& Request, const FLootLockerServerGrantItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGrantItemResponse>(Request, ULootLockerServerEndpoints::GrantItemToPlayer, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::SplitPlayerItemStack(int PlayerID, const FString& InventoryId, const FLootLockerServerSplitItemRequest& Request, const FLootLockerServerSplitPlayerItemStackResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSplitPlayerItemStackResponse>(Request, ULootLockerServerEndpoints::SplitPlayerItemStack, { PlayerID, InventoryId }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::MergePlayerItemStacks(int PlayerID, const FLootLockerServerMergeItemsRequest& Request, const FLootLockerServerMergePlayerItemStacksResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerMergePlayerItemStacksResponse>(Request, ULootLockerServerEndpoints::MergePlayerItemStacks, { PlayerID }, {}, OnCompletedRequest);
}