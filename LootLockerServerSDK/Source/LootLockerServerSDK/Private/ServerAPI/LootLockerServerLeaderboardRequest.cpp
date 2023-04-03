// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerLeaderboardRequest.h"
#include "LootLockerServerSDK/Private/Utils/LootLockerServerUtilities.h"
#include "LootLockerServerGameEndpoints.h"


ULootLockerServerHttpClient* ULootLockerServerLeaderboardRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerLeaderboardRequest::ULootLockerServerLeaderboardRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}


void ULootLockerServerLeaderboardRequest::CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerServerCreateLeaderboardRequest::StaticStruct(), &CreateLeaderboardRequest, ContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerServerCreateLeaderboardResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerCreateLeaderboardResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("CreateLeaderboard failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::CreateLeaderboardEndpoint;
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerLeaderboardRequest::UpdateLeaderboard(const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequests, int LeaderboardId, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerServerUpdateLeaderboardRequest::StaticStruct(), &UpdateLeaderboardRequests, ContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerServerUpdateLeaderboardResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerUpdateLeaderboardResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("UpdateLeaderboard failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::UpdateLeaderboardEndpoint;
	FString newEndpoint = FString::Format(*Endpoint.endpoint, { LeaderboardId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerLeaderboardRequest::DeleteLeaderboard(int LeaderboardId, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	FString ContentString;

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerServerDeleteLeaderboardResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerDeleteLeaderboardResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("DeleteLeaderboard failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::DeleteLeaderboardEndpoint;
	FString TempEndpoint = Endpoint.endpoint;
	FString newEndpoint = FString::Format(*TempEndpoint, { LeaderboardId });

	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerLeaderboardRequest::SubmitScore(const FLootLockerServerSubmitScoreRequest& SubmitScoreRequests, int LeaderboardId, const FLootLockerServerSubmitScoreResponseBP& OnCompletedRequestBP, const FLootLockerServerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerServerSubmitScoreRequest::StaticStruct(), &SubmitScoreRequests, ContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerServerSubmitScoreResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerSubmitScoreResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("SubmitScore failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::SubmitScoreEndpoint;
	FString newEndpoint = FString::Format(*Endpoint.endpoint, { LeaderboardId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
