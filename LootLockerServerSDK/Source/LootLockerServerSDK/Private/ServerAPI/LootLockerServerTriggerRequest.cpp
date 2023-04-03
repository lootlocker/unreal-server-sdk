// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerTriggerRequest.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerGameEndpoints.h"

ULootLockerServerHttpClient* ULootLockerServerTriggerRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerTriggerRequest::ULootLockerServerTriggerRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerTriggerRequest::InvokeTriggerOnBehalfOfPlayer(FString name, int PlayerId,
	const FInvokeTriggerResponseBP& OnCompletedRequestBP, const FInvokeTriggerResponse& OnCompletedRequest)
{
	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerInvokeTriggerResponse ResponseStruct;
            if (response.success)
            {
                response.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerInvokeTriggerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                response.success = false;
                UE_LOG(LogTemp, Error, TEXT("Invoking trigger failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

	TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
	ItemJson->SetStringField(FString(TEXT("name")), name);
	ItemJson->SetStringField(FString(TEXT("player_id")), FString::FromInt(PlayerId));
	FString ContentString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
	FJsonSerializer::Serialize(ItemJson, Writer);
	FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::InvokeTriggeronBehalfofPlayerEndpoint;
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}
