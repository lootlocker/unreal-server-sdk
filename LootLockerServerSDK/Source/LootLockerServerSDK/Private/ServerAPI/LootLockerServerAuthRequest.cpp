// Copyright (c) 2021 LootLocker


#include "ServerAPI/LootLockerServerAuthRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"

ULootLockerServerAuthRequest::ULootLockerServerAuthRequest()
{
}

FString ULootLockerServerAuthRequest::StartSession(const FLootLockerServerAuthResponseDelegate& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	const FLootLockerServerAuthenticationRequest authRequest{ Config->GameVersion };
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAuthenticationResponse>(
		authRequest,
		ULootLockerServerEndpoints::StartSession,
		{},
		{},
		OnCompletedRequest,
		ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerAuthenticationResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([](const FLootLockerServerAuthenticationResponse& Response)
		{
			ULootLockerServerStateData::SetServerToken(Response.Token);
		}),
		{ {"x-server-key", Config->LootLockerServerKey} }
	);
}

FString ULootLockerServerAuthRequest::MaintainSession(const FLootLockerServerMaintainSessionResponseDelegate& OnCompletedRequest)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerMaintainSessionResponse>(
		FLootLockerServerEmptyRequest(),
		ULootLockerServerEndpoints::MaintainingSession,
		{},
		{},
		OnCompletedRequest
	);
}
