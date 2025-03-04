// Copyright (c) 2021 LootLocker


#include "ServerAPI/LootLockerServerOAuthRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "GenericPlatform/GenericPlatformHttp.h"

FString ULootLockerServerOAuthRequest::TokenExchangeWWWFormFormatString = "grant_type={0}&actor_token_type={1}&subject_token_type={2}&subject_token={3}&actor_token={4}";
FString ULootLockerServerOAuthRequest::TokenExchangeGrantType = "urn:ietf:params:oauth:grant-type:token-exchange";
FString ULootLockerServerOAuthRequest::TokenExchangeActorTokenType = "urn:ietf:params:oauth:token-type:access_token";
FString ULootLockerServerOAuthRequest::TokenExchangeAccessTokenSubjectTokenType = "urn:ietf:params:oauth:token-type:access_token";
FString ULootLockerServerOAuthRequest::TokenExchangePlayerImpersonationSubjectTokenType = "lootlocker.v1.player";

ULootLockerServerOAuthRequest::ULootLockerServerOAuthRequest()
{
}

void ULootLockerServerOAuthRequest::GameApiTokenExchange(const FString& GameApiSessionToken, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequestBP, const FLootLockerServerTokenExchangeResponseDelegate& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	FString WWWFormData = FString::Format(*TokenExchangeWWWFormFormatString, { FGenericPlatformHttp::UrlEncode(TokenExchangeGrantType), FGenericPlatformHttp::UrlEncode(TokenExchangeActorTokenType), FGenericPlatformHttp::UrlEncode(TokenExchangeAccessTokenSubjectTokenType), FGenericPlatformHttp::UrlEncode(GameApiSessionToken), FGenericPlatformHttp::UrlEncode(Config->LootLockerServerKey) });
	ULootLockerServerHttpClient::SendRawWWWFormUrlEncodedRequest<FLootLockerServerTokenExchangeResponse>(
		WWWFormData,
		ULootLockerServerEndpoints::TokenExchange,
		{},
		{ { "game_version", Config->GameVersion }},
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerOAuthRequest::GameApiUserImpersonation(const FString& PlayerUlid, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequestBP, const FLootLockerServerTokenExchangeResponseDelegate& OnCompletedRequest)
{
	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
	FString WWWFormData = FString::Format(*TokenExchangeWWWFormFormatString, { FGenericPlatformHttp::UrlEncode(TokenExchangeGrantType), FGenericPlatformHttp::UrlEncode(TokenExchangeActorTokenType), FGenericPlatformHttp::UrlEncode(TokenExchangePlayerImpersonationSubjectTokenType), FGenericPlatformHttp::UrlEncode(PlayerUlid), FGenericPlatformHttp::UrlEncode(Config->LootLockerServerKey) });
	ULootLockerServerHttpClient::SendRawWWWFormUrlEncodedRequest<FLootLockerServerTokenExchangeResponse>(
		WWWFormData,
		ULootLockerServerEndpoints::TokenExchange,
		{},
		{ { "game_version", Config->GameVersion } },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}
