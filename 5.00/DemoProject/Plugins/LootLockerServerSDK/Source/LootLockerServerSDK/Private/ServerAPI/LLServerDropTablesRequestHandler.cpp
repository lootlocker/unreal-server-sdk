// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LLServerDropTablesRequestHandler.h"
#include "LootLockerServerGameEndpoints.h"
ULootLockerServerHttpClient* ULLServerDropTablesRequestHandler::HttpClient = nullptr;

ULLServerDropTablesRequestHandler::ULLServerDropTablesRequestHandler()
{
    HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULLServerDropTablesRequestHandler::ComputeAndLockDropTable(int TableId, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP, const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerServerComputeAndLockDropTableResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerComputeAndLockDropTableResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLockerServer, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerServerEndPoints endpoint = ULootLockerServerGameEndpoints::ComputeAndLockDropTableEndpoint;

	FString newEndpoint = FString::Format(*endpoint.endpoint, { TableId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULLServerDropTablesRequestHandler::PickDropsFromDropTable(const FLootLockerServerPickDropsFromDropTableRequest& request, int TableId, const FLootLockerServerPickDropsFromDropTableResponseBP& OnCompletedRequestBP, const FLootLockerServerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerServerPickDropsFromDropTableItem::StaticStruct(), &request, ContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
		{
			FLootLockerServerPickDropsFromDropTableResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerPickDropsFromDropTableResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLockerServer, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerServerEndPoints endpoint = ULootLockerServerGameEndpoints::PickDropsFromDropTableEndpoint;

	FString newEndpoint = FString::Format(*endpoint.endpoint, { TableId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
