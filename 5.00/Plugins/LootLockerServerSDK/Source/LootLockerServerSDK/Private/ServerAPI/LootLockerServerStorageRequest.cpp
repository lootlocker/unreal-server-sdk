// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerStorageRequest.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerGameEndpoints.h"

ULootLockerServerHttpClient* ULootLockerServerStorageRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerStorageRequest::ULootLockerServerStorageRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerStorageRequest::GetPersistentStorage(TArray<int> PlayerIds,
	const FGetPersistentStorageResponseBP& OnCompletedRequestBP,
	const FGetPersistentStorageResponse& OnCompletedRequest)
{
	FString data;
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetPersistentStorageResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerGetPersistentStorageResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("Getting players failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetPersistentStorageEndpoint;
	TArray<FString> PlayerStringIds;
	for (int Id : PlayerIds)
	{
		PlayerStringIds.Add(FString::FromInt(Id));
	}
	
	FString endpoint = FString::Format(*(Endpoint.endpoint), { FString::Join(PlayerStringIds, TEXT(",")) });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerServerStorageRequest::UpdatePersistentStorage(FLootLockerServerPersistentStorageRequestData requestData,
	const FUpdatePersistentStorageResponseBP& OnCompletedRequestBP,
	const FUpdatePersistentStorageResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerUpdatePersistentStorageResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerUpdatePersistentStorageResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("Failed to update persisten storage"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
	FJsonObjectConverter::UStructToJsonObject(FLootLockerServerPersistentStorageRequestData::StaticStruct(), &requestData, ItemJson, 0, 0);
	FString ContentString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
	FJsonSerializer::Serialize(ItemJson, Writer);
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::UpdatePersistentStorageEndpoint;
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}
