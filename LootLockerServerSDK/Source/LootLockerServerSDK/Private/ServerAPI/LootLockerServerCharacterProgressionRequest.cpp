// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCharacterProgressionRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerCharacterProgressionRequest::ULootLockerServerCharacterProgressionRequest()
{
}

void ULootLockerServerCharacterProgressionRequest::GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerCharacterProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForCharacter, { PlayerID, CharacterID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(Count > 0)
    {
        QueryParams.Add("count", FString::FromInt(Count));
    }
    if(!After.IsEmpty())
    {
        QueryParams.Add("after", After);
    }
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerCharacterProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForCharacter, { PlayerID, CharacterID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsByKeyForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::AddPointsToProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::SubtractPointsFromProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ResetProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseBP& OnCompletedRequestBP, const FLootLockerServerDeleteCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

