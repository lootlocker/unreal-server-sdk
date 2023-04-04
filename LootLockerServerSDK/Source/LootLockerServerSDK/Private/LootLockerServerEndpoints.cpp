// Copyright (c) 2021 LootLocker

#include "LootLockerServerEndpoints.h"

#include "LootLockerServerConfig.h"

FString ULootLockerServerEndpoints::GameBaseUrl = "https://{domainKey}api.lootlocker.io/server/";

//Auth
FLootLockerServerEndPoint ULootLockerServerEndpoints::StartSessionEndpoint = InitEndpoint("session", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MaintainingSessionEndpoint = InitEndpoint("ping", ELootLockerServerHTTPMethod::GET);

FLootLockerServerEndPoint ULootLockerServerEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method)
{
	FLootLockerServerEndPoint Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
