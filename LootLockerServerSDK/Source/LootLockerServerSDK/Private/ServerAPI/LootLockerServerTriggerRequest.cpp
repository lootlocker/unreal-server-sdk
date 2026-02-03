// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerTriggerRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerTriggerRequest::ULootLockerServerTriggerRequest()
{
}

FString ULootLockerServerTriggerRequest::InvokeTriggerForPlayer(FString TriggerName, int PlayerId, const FLootLockerServerInvokeTriggerResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerInvokeTriggerResponse>(FLootLockerServerInvokeTriggerForPlayerRequest{TriggerName, PlayerId}, ULootLockerServerEndpoints::InvokeTriggerForPlayer, {}, {}, OnCompletedRequest);
}
