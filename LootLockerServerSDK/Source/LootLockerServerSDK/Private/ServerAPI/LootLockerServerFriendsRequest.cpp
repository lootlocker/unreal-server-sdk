#include "ServerAPI/LootLockerServerFriendsRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerFriendsRequest::ULootLockerServerFriendsRequest()
{
}

void ULootLockerServerFriendsRequest::ListFriends(const FString& PlayerULID, const FLootLockerServerListFriendsResponseBP& OnResponseCompletedBP, const FLootLockerServerListFriendsResponseDelegate& OnResponseCompleted)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerListFriendsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListFriends, { PlayerULID }, {}, OnResponseCompletedBP, OnResponseCompleted);
}
