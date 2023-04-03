// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerPlayerRequest.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerGameEndpoints.h"

ULootLockerServerHttpClient* ULootLockerServerPlayerRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerPlayerRequest::ULootLockerServerPlayerRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerPlayerRequest::GetInventory(int PlayerId, int StartFromIndex, int ItemsCount,
                                                  const FInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest)
{
	FString data;
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerInventoryResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerInventoryResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetPlayerInventoryEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerServerPlayerRequest::AddAssetToPlayerInventory(int PlayerId, FLootLockerServerAddAssetData AddAssetData,
	const FAddAssetResponseBP& OnCompletedRequestBP, const FAddAssetResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerAddAssetResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerAddAssetResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
	FJsonObjectConverter::UStructToJsonObject(FLootLockerServerAddAssetData::StaticStruct(), &AddAssetData, ItemJson, 0, 0);
	FString ContentString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
	FJsonSerializer::Serialize(ItemJson, Writer);
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::AddAssetsToPlayerInventoryEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	UE_LOG(LogTemp, Log, TEXT("data=%s"), *ContentString);
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerPlayerRequest::GetPlayerLoadout(int PlayerId,
	const FGetPlayerLoadoutResponseBP& OnCompletedRequestBP, const FGetPlayerLoadoutResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetPlayerLoadoutResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerGetPlayerLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetPlayerLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	UE_LOG(LogTemp, Log, TEXT("data=%s"), *ContentString);
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerPlayerRequest::EquipAssetForPlayerLoadout(int PlayerId, int InstanceId,
	const FEquipAssetResponseBP& OnCompletedRequestBP, const FEquipAssetResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerEquipAssetForPlayerLoadoutResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerEquipAssetForPlayerLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
	ItemJson->SetStringField(FString(TEXT("instance_id")), FString::FromInt(InstanceId));
	FString ContentString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
	FJsonSerializer::Serialize(ItemJson, Writer);
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::EquipAssetToPlayerLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	UE_LOG(LogTemp, Log, TEXT("data=%s"), *ContentString);
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerPlayerRequest::UnequipAssetForPlayerLoadout(int PlayerId, int LoadoutId,
	const FUnequipAssetResponseBP& OnCompletedRequestBP, const FUnequipAssetResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerUnequipAssetForPlayerLoadoutResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerUnequipAssetForPlayerLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::UnEquipAssetToPlayerLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, LoadoutId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
