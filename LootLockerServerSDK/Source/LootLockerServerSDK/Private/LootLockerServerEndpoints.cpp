// Copyright (c) 2021 LootLocker

#include "LootLockerServerEndpoints.h"

#include "LootLockerServerConfig.h"

FString ULootLockerServerEndpoints::GameBaseUrl = "https://{domainKey}api.lootlocker.io/server/";

//Auth
FLootLockerServerEndPoint ULootLockerServerEndpoints::StartSession = InitEndpoint("session", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::MaintainingSession = InitEndpoint("ping", ELootLockerServerHTTPMethod::GET);

//Leaderboards
FLootLockerServerEndPoint ULootLockerServerEndpoints::CreateLeaderboard = InitEndpoint("leaderboards", ELootLockerServerHTTPMethod::POST);
FLootLockerServerEndPoint ULootLockerServerEndpoints::UpdateLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::PUT);
FLootLockerServerEndPoint ULootLockerServerEndpoints::DeleteLeaderboard = InitEndpoint("leaderboards/{0}", ELootLockerServerHTTPMethod::DELETE);
FLootLockerServerEndPoint ULootLockerServerEndpoints::SubmitScore = InitEndpoint("leaderboards/{0}/submit", ELootLockerServerHTTPMethod::POST);

FLootLockerServerEndPoint ULootLockerServerEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method)
{
	FLootLockerServerEndPoint Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
