// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerLeaderboardArchiveRequestHandler.h"
#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"

// Sets default values for this component's properties
ULootLockerServerLeaderboardArchiveRequestHandler::ULootLockerServerLeaderboardArchiveRequestHandler()
{
}

void ULootLockerServerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseBP& OnCompletedRequestBP, const FLootLockerServerLeaderboardArchiveResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerLeaderboardArchiveResponse>(FLootLockerServerLeaderboardArchiveResponse{}, ULootLockerServerEndpoints::ListLeaderboardArchive, { LeaderboardKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP, const FLootLockerServerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest)
{

    TMultiMap<FString,FString> QueryParams;

	if (!Key.IsEmpty()) {
		QueryParams.Add("key", Key);
	}
	if(Count > 0){
    	QueryParams.Add("count", FString::FromInt(Count));
	}
	if (!After.IsEmpty())
	{
		QueryParams.Add("after", After);
	}
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerLeaderboardArchiveDetailsResponse>(FLootLockerServerLeaderboardArchiveResponse{}, ULootLockerServerEndpoints::GetLeaderboardArchive, { }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}