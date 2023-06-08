// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerGameProgressionRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerGameProgressionRequest::ULootLockerServerGameProgressionRequest()
{
}

void ULootLockerServerGameProgressionRequest::GetProgressions(const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGameProgressionListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAllProgressions, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerGameProgressionRequest::GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequestBP, const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest) 
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGameProgressionListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetAllProgressions, {}, { QueryParams }, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerGameProgressionRequest::GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseBP& OnCompletedRequestBP, const FLootLockerServerSingleGameProgressionResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSingleGameProgressionResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetProgression, { ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerGameProgressionRequest::GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequestBP, const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerProgressionTiersResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetProgressionTiers, { ProgressionKey }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerGameProgressionRequest::GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequestBP, const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest) 
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerProgressionTiersResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetProgressionTiers, { ProgressionKey }, { QueryParams }, OnCompletedRequestBP, OnCompletedRequest);
}

