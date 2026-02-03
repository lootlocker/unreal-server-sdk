// Copyright (c) 2021 LootLocker


#include "ServerAPI/LootLockerServerAuthRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"

ULootLockerServerAuthRequest::ULootLockerServerAuthRequest()
{
}

void ULootLockerServerAuthRequest::StartSession(const FLootLockerServerAuthResponseDelegate& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	const FLootLockerServerAuthenticationRequest authRequest{ Config->GameVersion };
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerAuthenticationResponse>(
		authRequest,
		ULootLockerServerEndpoints::StartSession,
		{},
		{},
		FLootLockerServerAuthResponseBP(),
		OnCompletedRequest,
		ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerAuthenticationResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([](const FLootLockerServerAuthenticationResponse& Response)
		{
			ULootLockerServerStateData::SetServerToken(Response.Token);
		}),
		{ {"x-server-key", Config->LootLockerServerKey} }
	);
}

void ULootLockerServerAuthRequest::MaintainSession(const FLootLockerServerMaintainSessionResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerMaintainSessionResponse>(
		FLootLockerServerEmptyRequest(),
		ULootLockerServerEndpoints::MaintainingSession,
		{},
		{},
		FLootLockerServerMaintainSessionResponseBP(),
		OnCompletedRequest
	);
}
