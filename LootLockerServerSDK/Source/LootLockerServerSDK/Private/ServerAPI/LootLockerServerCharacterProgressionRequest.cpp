// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCharacterProgressionRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerCharacterProgressionRequest::ULootLockerServerCharacterProgressionRequest()
{
}

void ULootLockerServerCharacterProgressionRequest::GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerCharacterProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForCharacter, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerCharacterProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForCharacter, { PlayerID, CharacterID }, QueryParams, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsByKeyForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::AddPointsToProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::SubtractPointsFromProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ResetProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterProgressionRequest::DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

