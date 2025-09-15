#include "ServerAPI/LootLockerServerFriendsRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerFriendsRequest::ULootLockerServerFriendsRequest()
{
}

void ULootLockerServerFriendsRequest::ListFriends(const FString& PlayerULID, int Page, int PerPage, const FLootLockerServerListFriendsResponseBP& OnResponseCompletedBP, const FLootLockerServerListFriendsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("page", FString::FromInt(Page));
    QueryParams.Add("per_page", FString::FromInt(PerPage));
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerListFriendsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListFriends, { PlayerULID }, QueryParams, OnResponseCompletedBP, OnResponseCompleted);
}
