// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerGameProgressionRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerGameProgressionRequest::ULootLockerServerGameProgressionRequest()
{
}

FString ULootLockerServerGameProgressionRequest::GetProgressions(const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGameProgressionListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAllProgressions, {}, {}, OnCompletedRequest);
}

FString ULootLockerServerGameProgressionRequest::GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest) 
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGameProgressionListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAllProgressions, {}, { QueryParams }, OnCompletedRequest);
}

FString ULootLockerServerGameProgressionRequest::GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleGameProgressionResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetProgression, { ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerGameProgressionRequest::GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerProgressionTiersResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetProgressionTiers, { ProgressionKey }, {}, OnCompletedRequest);
}

FString ULootLockerServerGameProgressionRequest::GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest) 
{
    TMultiMap<FString, FString> QueryParams;
    if(Count > 0)
    {
        QueryParams.Add("count", FString::FromInt(Count));
    }
    if(After > 0)
    {
        QueryParams.Add("after", FString::FromInt(After));
    }
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerProgressionTiersResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetProgressionTiers, { ProgressionKey }, { QueryParams }, OnCompletedRequest);
}

