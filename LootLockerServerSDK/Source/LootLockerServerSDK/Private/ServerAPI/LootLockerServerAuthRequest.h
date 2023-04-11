// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerConfig.h"
#include "JsonObjectConverter.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"
#include "LootLockerServerAuthRequest.generated.h"

//==================================================
// Request Definitions
//==================================================
USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString Game_Version;
};

//==================================================
// Response Definitions
//==================================================
USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerServerMaintainSessionResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 Current time on the LootLocker Backend
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString Pong;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for start session responses
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAuthResponseBP, FLootLockerServerAuthenticationResponse, Var);
/*
 Blueprint response delegate for maintain session responses
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerMaintainSessionResponseBP, FLootLockerServerMaintainSessionResponse, Var);

//==================================================
// C++ Delegate Definitions
//==================================================
/*
 C++ response delegate for start session responses
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerAuthResponseDelegate, FLootLockerServerAuthenticationResponse);
/*
 C++ response delegate for maintain session responses
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerMaintainSessionResponseDelegate, FLootLockerServerMaintainSessionResponse);

//==================================================
// Interface Definition
//==================================================
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerAuthRequest : public UObject
{
public:
	GENERATED_BODY()
public:
	ULootLockerServerAuthRequest();

public:
	static void StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequestBP = FLootLockerServerAuthResponseBP(), const FLootLockerServerAuthResponseDelegate& OnCompletedRequest = FLootLockerServerAuthResponseDelegate());
	static void MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequestBP = FLootLockerServerMaintainSessionResponseBP(), const FLootLockerServerMaintainSessionResponseDelegate& OnCompletedRequest = FLootLockerServerMaintainSessionResponseDelegate());
};
