// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "LootLockerServerAssetRequest.h"
#include "LootLockerServerConfig.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerTriggerRequest.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerLevel
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int level = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_prestige = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int xp_threshold = 0;
	
};

USTRUCT(BlueprintType)
struct FLootLockerServerXP
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int previous = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int current = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerServerInvokeTriggerResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerXP xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerLevel> levels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerAsset> granted_assets;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FInvokeTriggerResponseBP, FLootLockerServerInvokeTriggerResponse, InvokeTriggerResponse);
DECLARE_DELEGATE_OneParam(FInvokeTriggerResponse, FLootLockerServerInvokeTriggerResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerTriggerRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerTriggerRequest();	

	static void InvokeTriggerOnBehalfOfPlayer(FString name, int PlayerId, const FInvokeTriggerResponseBP& OnCompletedRequestBP = FInvokeTriggerResponseBP(), const FInvokeTriggerResponse& OnCompletedRequest = FInvokeTriggerResponse());

	static ULootLockerServerHttpClient* HttpClient;
};
