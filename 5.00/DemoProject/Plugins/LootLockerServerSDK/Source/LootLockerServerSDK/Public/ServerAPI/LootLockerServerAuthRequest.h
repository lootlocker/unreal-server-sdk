// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerServerAuthRequest.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool is_development;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPingResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 pong;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FServerPingResponseBP, FLootLockerServerPingResponse, Var);
DECLARE_DELEGATE_OneParam(FServerPingResponse, FLootLockerServerPingResponse);

USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString token;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString error;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FServerAuthResponseBP, FLootLockerServerAuthenticationResponse, Var);
DECLARE_DELEGATE_OneParam(FServerAuthResponse, FLootLockerServerAuthenticationResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSERVERSDK_API ULootLockerServerAuthRequest : public UObject
{
public:
	GENERATED_BODY()
public:
	ULootLockerServerAuthRequest();

public:
	static void StartSession(const FServerAuthResponseBP& OnCompletedRequestBP = FServerAuthResponseBP(), const FServerAuthResponse& OnCompletedRequest = FServerAuthResponse());
	static void MaintainSession(const FServerPingResponseBP& OnCompletedRequestBP = FServerPingResponseBP(), const FServerPingResponse& OnCompletedRequest = FServerPingResponse());
	static ULootLockerServerHttpClient* HttpClient;
};
