// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerHeroesRequest.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerGameEndpoints.h"

ULootLockerServerHttpClient* ULootLockerServerHeroesRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerHeroesRequest::ULootLockerServerHeroesRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerHeroesRequest::GetPlayerHeroes(int PlayerId,
	const FHeroesResponseBP& OnCompletedRequestBP, const FHeroesResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetPlayerHeroesResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerGetPlayerHeroesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetPlayerHeroesEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerHeroesRequest::GetInventoryToHero(int PlayerId, int HeroId,
	const FHeroInventoryResponseBP& OnCompletedRequestBP, const FHeroInventoryResponse& OnCompletedRequest)
{
	FString data;
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerHeroInventoryResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerHeroInventoryResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetInventorytoHeroEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, HeroId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerServerHeroesRequest::GetHeroLoadout(int PlayerId, int HeroId,
	const FHeroLoadoutResponseBP& OnCompletedRequestBP, const FHeroLoadoutResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetHeroLoadoutResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerGetHeroLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetHeroLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, HeroId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerHeroesRequest::EquipAssetForHeroLoadout(int PlayerId, int HeroId, int InstanceId,
	const FEquipHeroResponseBP& OnCompletedRequestBP, const FEquipHeroResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerEquipHeroResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerEquipHeroResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("Getting player failed from lootlocker"));
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
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::EquipAssetforHeroLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, HeroId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerHeroesRequest::UnequipAssetForHeroLoadout(int PlayerId, int HeroId, int InstanceId,
	const FUnequipHeroResponseBP& OnCompletedRequestBP, const FUnequipHeroResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerUnequipHeroResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerUnequipHeroResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("Getting player failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	FString ContentString;
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::UnequipAssetforHeroLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, HeroId, InstanceId });
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}