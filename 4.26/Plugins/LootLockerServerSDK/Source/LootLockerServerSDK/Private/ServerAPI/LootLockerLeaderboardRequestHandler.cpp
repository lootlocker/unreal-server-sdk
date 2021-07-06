// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerLeaderboardRequestHandler.h"
#include "LootLockerServerSDK/Private/Utils/LootLockerServerUtilities.h"
#include "LootLockerServerGameEndpoints.h"


ULootLockerServerHttpClient* ULootLockerLeaderboardRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerLeaderboardRequestHandler::ULootLockerLeaderboardRequestHandler()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}


void ULootLockerLeaderboardRequestHandler::CreateLeaderboard(const FLootLockerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerCreateLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerCreateLeaderboardResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerCreateLeaderboardRequest::StaticStruct(), &CreateLeaderboardRequest, ContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerCreateLeaderboardResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCreateLeaderboardResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
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

void ULootLockerLeaderboardRequestHandler::UpdateLeaderboard(const FLootLockerUpdateLeaderboardRequest& UpdateLeaderboardRequests, int LeaderboardId, const FLootLockerUpdateLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerUpdateLeaderboardResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerUpdateLeaderboardRequest::StaticStruct(), &UpdateLeaderboardRequests, ContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerUpdateLeaderboardResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerUpdateLeaderboardResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
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

void ULootLockerLeaderboardRequestHandler::DeleteLeaderboard(int LeaderboardId, const FLootLockerDeleteLeaderboardResponseBP& OnCompletedRequestBP, const FLootLockerDeleteLeaderboardResponseDelegate& OnCompletedRequest)
{
	FString ContentString;

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerDeleteLeaderboardResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerDeleteLeaderboardResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
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

void ULootLockerLeaderboardRequestHandler::SubmitScore(const FLootLockerSubmitScoreRequest& SubmitScoreRequests, int LeaderboardId, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerSubmitScoreRequest::StaticStruct(), &SubmitScoreRequests, ContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerSubmitScoreResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerSubmitScoreResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
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
