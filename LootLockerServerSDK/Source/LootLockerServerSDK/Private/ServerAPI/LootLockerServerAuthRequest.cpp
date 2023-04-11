// Fill out your copyright notice in the Description page of Project Settings.


#include "LootLockerServerAuthRequest.h"
#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"

ULootLockerServerAuthRequest::ULootLockerServerAuthRequest()
{
}

void ULootLockerServerAuthRequest::StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequestBP, const FLootLockerServerAuthResponseDelegate& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	const FLootLockerServerAuthenticationRequest authRequest{ Config->GameVersion };
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerAuthenticationResponse>(
		authRequest, 
		ULootLockerServerEndpoints::StartSession,
		{},
		{}, 
		OnCompletedRequestBP, 
		OnCompletedRequest, 
		ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerAuthenticationResponse>::FLootLockerServerResponseInspectorCallback(), 
		{ {"x-server-key", Config->LootLockerServerKey} }
	);
}

void ULootLockerServerAuthRequest::MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequestBP, const FLootLockerServerMaintainSessionResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerMaintainSessionResponse>(
		FLootLockerServerEmptyRequest(),
		ULootLockerServerEndpoints::MaintainingSession,
		{},
		{},
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}