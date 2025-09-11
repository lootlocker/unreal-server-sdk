// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerPlayerRequest::ULootLockerServerPlayerRequest()
{
}

void ULootLockerServerPlayerRequest::LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequestBP, const FLootLockerServerPlayerNameLookupResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
    for (int i = 0; i < IdsToLookUp.Num(); ++i) {
		FString Key = ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerPlayerNameLookupIdType"), static_cast<int32_t>(IdsToLookUp[i].IdType)).ToLower();
		Key.ReplaceCharInline(TEXT(' '), TEXT('_'));
		QueryParams.Add(Key, IdsToLookUp[i].Id);
	}
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerNameLookupResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::LookupMultiplePlayerNamesUsingIDs, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerRequest::GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequestBP, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate& OnCompletedRequest)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse>(FLootLockerServerGetPlayerInfoFromGameSessionTokenRequest{ GameSessionTokensToLookUp }, ULootLockerServerEndpoints::GetPlayerInfoFromGameSessionToken, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerRequest::CreatePlayer(ELootLockerServerCreatePlayerPlatforms Platform, const FString& PlayerIdentifier, const FLootLockerServerCreatePlayerResponseBP& OnCompletedRequestBP, const FLootLockerServerCreatePlayerResponseDelegate& OnCompletedRequest)
{
	FLootLockerServerCreatePlayerRequest Request;
	Request.Player_identifier = PlayerIdentifier;
	switch (Platform)
	{
		case ELootLockerServerCreatePlayerPlatforms::Steam: Request.Platform = "steam"; break;
		case ELootLockerServerCreatePlayerPlatforms::PlayStation: Request.Platform = "psn"; break;
		case ELootLockerServerCreatePlayerPlatforms::Apple: Request.Platform = "apple_sign_in"; break;
		case ELootLockerServerCreatePlayerPlatforms::AppleGameCenter: Request.Platform = "apple_game_center"; break;
		case ELootLockerServerCreatePlayerPlatforms::AppleAppStore: Request.Platform = "apple_app_store"; break;
		case ELootLockerServerCreatePlayerPlatforms::Google: Request.Platform = "google_sign_in"; break;
		case ELootLockerServerCreatePlayerPlatforms::GooglePlay: Request.Platform = "google_play_store"; break;
		case ELootLockerServerCreatePlayerPlatforms::Xbox: Request.Platform = "xbox_one"; break;
		case ELootLockerServerCreatePlayerPlatforms::NintendoSwitch: Request.Platform = "nintendo_switch"; break;
		case ELootLockerServerCreatePlayerPlatforms::AmazonLuna: Request.Platform = "amazon_luna"; break;
		case ELootLockerServerCreatePlayerPlatforms::WhiteLabelLogin:  Request.Platform = "white_label_login"; break;
		case ELootLockerServerCreatePlayerPlatforms::Guest:  Request.Platform = "guest"; break;
		case ELootLockerServerCreatePlayerPlatforms::EpicGames:  Request.Platform = "epic_games"; break;
		case ELootLockerServerCreatePlayerPlatforms::Meta:  Request.Platform = "meta"; break;
		default: Request.Platform = "N/A"; break;
	}
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreatePlayerResponse>(Request, ULootLockerServerEndpoints::CreatePlayer, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}
