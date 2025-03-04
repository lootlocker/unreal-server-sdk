// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerOAuthRequest.generated.h"

//==================================================
// Response Definitions
//==================================================
USTRUCT(BlueprintType)
struct FLootLockerServerTokenExchangeResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 The type of token contained in the response
	 */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Token_type = "";
	/*
	 The new access token to use in subsequent requests
	 */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Access_token = "";
	/*
	 The refresh token to use for refreshing the access token upon expiry
	 */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Refresh_token = "";
	/*
	 The ulid of the subject that this token is for
	 */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Subject_ulid = "";
	/*
	 For how many seconds the Access Token is valid
	 */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	int Expires_in = 0;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for handling token exchange responses
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerTokenExchangeResponseBP, FLootLockerServerTokenExchangeResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/*
 C++ response delegate for handling token exchange responses
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerTokenExchangeResponseDelegate, FLootLockerServerTokenExchangeResponse);

//==================================================
// Interface Definition
//==================================================
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerOAuthRequest : public UObject
{
public:
	GENERATED_BODY()
public:
	ULootLockerServerOAuthRequest();

	static void GameApiTokenExchange(const FString& GameApiSessionToken, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequestBP = FLootLockerServerTokenExchangeResponseBP(), const FLootLockerServerTokenExchangeResponseDelegate& OnCompletedRequest = FLootLockerServerTokenExchangeResponseDelegate());
	static void GameApiUserImpersonation(const FString& PlayerUlid, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequestBP = FLootLockerServerTokenExchangeResponseBP(), const FLootLockerServerTokenExchangeResponseDelegate& OnCompletedRequest = FLootLockerServerTokenExchangeResponseDelegate());

private:
	static FString TokenExchangeWWWFormFormatString;
	static FString TokenExchangeGrantType;
	static FString TokenExchangeActorTokenType;
	static FString TokenExchangeAccessTokenSubjectTokenType;
	static FString TokenExchangePlayerImpersonationSubjectTokenType;
};
