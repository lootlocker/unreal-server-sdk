// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerConfig.h"

ULootLockerServerPlayerRequest::ULootLockerServerPlayerRequest()
{
}

void ULootLockerServerPlayerRequest::LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequestBP, const FLootLockerServerPlayerNameLookupResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
    for (int i = 0; i < IdsToLookUp.Num(); ++i) {
		QueryParams.Add(GetDefault<ULootLockerServerConfig>()->GetEnum(TEXT("ELootLockerServerPlayerNameLookupIdType"), static_cast<int32_t>(IdsToLookUp[i].IdType)), IdsToLookUp[i].Id);
	}
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerNameLookupResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::LookupMultiplePlayerNamesUsingIDs, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
