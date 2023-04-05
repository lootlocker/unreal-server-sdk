// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerServerAuthRequest.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString Game_Version;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAuthResponseBP, FLootLockerServerAuthenticationResponse, Var);
DECLARE_DELEGATE_OneParam(FLootLockerServerAuthResponseDelegate, FLootLockerServerAuthenticationResponse);

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerAuthRequest : public UObject
{
public:
	GENERATED_BODY()
public:
	ULootLockerServerAuthRequest();

public:
	static void StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequestBP = FLootLockerServerAuthResponseBP(), const FLootLockerServerAuthResponseDelegate& OnCompletedRequest = FLootLockerServerAuthResponseDelegate());
	static void MaintainSession(const FLootLockerServerAuthResponseBP& OnCompletedRequestBP = FLootLockerServerAuthResponseBP(), const FLootLockerServerAuthResponseDelegate& OnCompletedRequest = FLootLockerServerAuthResponseDelegate());
	static ULootLockerServerHttpClient* HttpClient;
};
