// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "LootLockerServerEndpoints.h"
#include "LootLockerServerStateData.h"
#include "Utils/LootLockerServerUtilities.h"


ULootLockerServerHttpClient* ULootLockerServerAuthRequest::HttpClient = nullptr;

ULootLockerServerAuthRequest::ULootLockerServerAuthRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerAuthRequest::StartSession(const FServerAuthResponseBP& OnCompletedRequestBP, const FServerAuthResponse& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	const FLootLockerServerAuthenticationRequest authRequest{ Config->GameVersion };
	LootLockerServerAPIUtilities<FLootLockerServerAuthenticationResponse>::CallAPI(HttpClient, authRequest, ULootLockerServerEndpoints::StartSessionEndpoint, {}, {}, OnCompletedRequestBP, OnCompletedRequest, LootLockerServerAPIUtilities<FLootLockerServerAuthenticationResponse>::FServerResponseInspectorCallback(), {{"x-server-key", Config->LootLockerServerKey}});
}

void ULootLockerServerAuthRequest::MaintainSession(const FServerAuthResponseBP& OnCompletedRequestBP, const FServerAuthResponse& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	const FLootLockerServerAuthenticationRequest authRequest{ Config->GameVersion };

	LootLockerServerAPIUtilities<FLootLockerServerAuthenticationResponse>::CallAPI(HttpClient, authRequest, ULootLockerServerEndpoints::StartSessionEndpoint, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}