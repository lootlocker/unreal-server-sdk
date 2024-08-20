// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerLogger.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerConfig.h"

ULootLockerServerPlayerRequest::ULootLockerServerPlayerRequest()
{
}

void ULootLockerServerPlayerRequest::LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequestBP, const FLootLockerServerPlayerNameLookupResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
    for (int i = 0; i < IdsToLookUp.Num(); ++i) {
		FString Key = GetDefault<ULootLockerServerConfig>()->GetEnum(TEXT("ELootLockerServerPlayerNameLookupIdType"), static_cast<int32_t>(IdsToLookUp[i].IdType)).ToLower();
		Key.ReplaceCharInline(TEXT(' '), TEXT('_'));
		QueryParams.Add(Key, IdsToLookUp[i].Id);
	}
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerNameLookupResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::LookupMultiplePlayerNamesUsingIDs, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerRequest::GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequestBP, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse>(FLootLockerServerGetPlayerInfoFromGameSessionTokenRequest{ GameSessionTokensToLookUp }, ULootLockerServerEndpoints::GetPlayerInfoFromGameSessionToken, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}
