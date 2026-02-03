// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCharacterProgressionRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerCharacterProgressionRequest::ULootLockerServerCharacterProgressionRequest()
{
}

FString ULootLockerServerCharacterProgressionRequest::GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerCharacterProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForCharacter, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterProgressionRequest::GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest)
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerCharacterProgressionListResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsForCharacter, { PlayerID, CharacterID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerCharacterProgressionRequest::GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetProgressionsByKeyForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterProgressionRequest::AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::AddPointsToProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterProgressionRequest::SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerModifyScoreRequest{ Amount }, ULootLockerServerEndpoints::SubtractPointsFromProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterProgressionRequest::ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleCharacterProgressionWithRewardsResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ResetProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterProgressionRequest::DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeleteProgressionForCharacter, { PlayerID, CharacterID, ProgressionKey }, {}, OnCompletedRequest);
}

