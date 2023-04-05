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

void ULootLockerServerAuthRequest::StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequestBP, const FLootLockerServerAuthResponseDelegate& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	const FLootLockerServerAuthenticationRequest authRequest{ Config->GameVersion };
	LootLockerServerAPIUtilities<FLootLockerServerAuthenticationResponse>::CallAPI(HttpClient, authRequest, ULootLockerServerEndpoints::StartSession, {}, {}, OnCompletedRequestBP, OnCompletedRequest, LootLockerServerAPIUtilities<FLootLockerServerAuthenticationResponse>::FServerResponseInspectorCallback(), {{"x-server-key", Config->LootLockerServerKey}});
}

void ULootLockerServerAuthRequest::MaintainSession(const FLootLockerServerAuthResponseBP& OnCompletedRequestBP, const FLootLockerServerAuthResponseDelegate& OnCompletedRequest)
{
	LootLockerServerAPIUtilities<FLootLockerServerAuthenticationResponse>::CallAPI(HttpClient, FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::MaintainingSession, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}