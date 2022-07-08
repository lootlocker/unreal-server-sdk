// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"
#include "LLServerDropTablesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerComputeAndLockItem
{
    GENERATED_BODY()
    int asset_id;
    int asset_variation_id;
    int asset_rental_option_id;
    int id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerComputeAndLockDropTableResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerServerComputeAndLockItem> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPickDropsFromDropTableResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    bool success;
public:
    TArray <FLootLockerServerPickDropsFromDropTableItem> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPickDropsFromDropTableItem
{
    GENERATED_BODY()
    int instance_id;
    int variation_id;
    int rental_option_id;
    int quantity;
    FLootLockerServerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPickDropsFromDropTableRequest
{
    GENERATED_BODY()
    TArray<int> picks;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerComputeAndLockDropTableResponseBP, FLootLockerServerComputeAndLockDropTableResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerServerComputeAndLockDropTableResponseDelegate, FLootLockerServerComputeAndLockDropTableResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPickDropsFromDropTableResponseBP, FLootLockerServerPickDropsFromDropTableResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerServerPickDropsFromDropTableResponseDelegate, FLootLockerServerPickDropsFromDropTableResponse);
/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULLServerDropTablesRequestHandler : public UObject
{
	GENERATED_BODY()
public:
    ULLServerDropTablesRequestHandler();
    static ULootLockerServerHttpClient* HttpClient;
    static void ComputeAndLockDropTable(int TableId,const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP = FLootLockerServerComputeAndLockDropTableResponseBP(), const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest = FLootLockerServerComputeAndLockDropTableResponseDelegate());
    static void PickDropsFromDropTable(const FLootLockerServerPickDropsFromDropTableRequest& request, int TableId,const FLootLockerServerPickDropsFromDropTableResponseBP& OnCompletedRequestBP = FLootLockerServerPickDropsFromDropTableResponseBP(), const FLootLockerServerPickDropsFromDropTableResponseDelegate& OnCompletedRequest = FLootLockerServerPickDropsFromDropTableResponseDelegate());
	
};
