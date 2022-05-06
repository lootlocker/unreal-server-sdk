// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerCharacterRequest.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerGameEndpoints.h"

ULootLockerServerHttpClient* ULootLockerServerCharacterRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerCharacterRequest::ULootLockerServerCharacterRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerCharacterRequest::GetPlayerCharacters(int PlayerId,
	const FCharactersResponseBP& OnCompletedRequestBP, const FCharactersResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetPlayerCharactersResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerGetPlayerCharactersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetPlayerCharactersEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	UE_LOG(LogTemp, Log, TEXT("data=%s"), *ContentString);
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerCharacterRequest::GetInventoryToCharacter(int PlayerId, int CharacterId,
	const FCharacterInventoryResponseBP& OnCompletedRequestBP, const FServerCharacterInventoryResponse& OnCompletedRequest)
{
	FString data;
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerCharacterInventoryResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerCharacterInventoryResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetInventorytoCharacterEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, CharacterId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerServerCharacterRequest::GetCharacterLoadout(int PlayerId, int CharacterId,
	const FCharacterLoadoutResponseBP& OnCompletedRequestBP, const FServerCharacterLoadoutResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetCharacterLoadoutResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerGetCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetCharacterLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, CharacterId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerCharacterRequest::EquipAssetForCharacterLoadout(int PlayerId, int CharacterId, int InstanceId,
	const FEquipResponseBP& OnCompletedRequestBP, const FEquipResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerEquipCharacterResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerEquipCharacterResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                ResponseStruct.success = false;
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
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::EquipAssetforCharacterLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, CharacterId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerCharacterRequest::UnequipAssetForCharacterLoadout(int PlayerId, int CharacterId, int InstanceId,
	const FUnequipResponseBP& OnCompletedRequestBP, const FUnequipResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerUnequipCharacterResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerUnequipCharacterResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::UnequipAssetforCharacterLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, CharacterId, InstanceId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
