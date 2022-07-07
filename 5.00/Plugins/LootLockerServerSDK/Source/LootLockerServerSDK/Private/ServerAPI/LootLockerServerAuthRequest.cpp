// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "LootLockerServerGameEndpoints.h"
#include "LootLockerSrvPersitentDataHolder.h"


ULootLockerServerHttpClient* ULootLockerServerAuthRequest::HttpClient = nullptr;

ULootLockerServerAuthRequest::ULootLockerServerAuthRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}
//
void ULootLockerServerAuthRequest::StartSession(const FServerAuthResponseBP& OnCompletedRequestBP, const FServerAuthResponse& OnCompletedRequest)
{
	FLootLockerServerAuthenticationRequest authRequest;
	const ULootLockerServerConfig* config = GetDefault<ULootLockerServerConfig>();
	authRequest.development_mode = config->OnDevelopmentMode;
	authRequest.game_version = config->GameVersion;
	FString AuthContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerServerAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);
	UE_LOG(LogLootLockerServer, Error, TEXT("Content %s"), *AuthContentString);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, config](FLootLockerServerResponse response)
		{
			FLootLockerServerAuthenticationResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerAuthenticationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ULootLockerSrvPersitentDataHolder::ServerToken = ResponseStruct.token;
				ResponseStruct.success = true;
			}
			else
			{
				ResponseStruct.success = false;
				UE_LOG(LogLootLockerServer, Error, TEXT("Starting of Session failed"));
			}

			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerServerEndPoints endpoint = ULootLockerServerGameEndpoints::StartSessionEndpoint;
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, AuthContentString, sessionResponse);
}

void ULootLockerServerAuthRequest::MaintainSession(const FServerAuthResponseBP& OnCompletedRequestBP, const FServerAuthResponse& OnCompletedRequest)
{
	FLootLockerServerAuthenticationRequest authRequest;
	const ULootLockerServerConfig* config = GetDefault<ULootLockerServerConfig>();
	authRequest.development_mode = config->OnDevelopmentMode;
	authRequest.game_version = config->GameVersion;
	FString AuthContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerServerAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, config](FLootLockerServerResponse response)
		{
			FLootLockerServerAuthenticationResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerAuthenticationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else
			{
				ResponseStruct.success = false;
				UE_LOG(LogLootLockerServer, Error, TEXT("Starting of Session failed"));
			}

			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerServerEndPoints endpoint = ULootLockerServerGameEndpoints::StartSessionEndpoint;
	FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, AuthContentString, sessionResponse,true);
}