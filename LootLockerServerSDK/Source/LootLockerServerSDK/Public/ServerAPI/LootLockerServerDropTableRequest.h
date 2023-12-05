// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerDropTableRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerDropTableItem
{
    GENERATED_BODY()
    /*
     The id of this drop table item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Id = 0;
    /*
     The id of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_id = 0;
    /*
     Optional: The id of the particular asset variation of the asset that is in the drop table
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Asset_variation_id = "";
    /*
     Optional: The id of the particular rental option of the asset that is in the drop table
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Asset_rental_option_id = "";
    /*
     Optional: The full asset description
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FLootLockerServerAsset Asset;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPickedDropTableItem
{
    GENERATED_BODY()
    /*
     The id of this asset instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id = 0;
    /*
     Optional: The id of the particular asset variation of this asset instance
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Variation_id = "";
    /*
     Optional: The id of the particular rental option of this asset instance
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Rental_option_id = "";
    /*
     The quantity of this item that was picked
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Quantity = 0;
    /*
     The full asset description
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FLootLockerServerAsset Asset;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPickDropsFromDropTableRequest
{
    GENERATED_BODY()
    /*
     List of ids of the drop table items to pick for the specified player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<int> Picks;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerComputeAndLockDropTableResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 List of drop table items in this drop table
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerDropTableItem> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPickFromDropTableResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 List of drop table items that were picked
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPickedDropTableItem> Items;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for computing and locking a drop table
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerComputeAndLockDropTableResponseBP, FLootLockerServerComputeAndLockDropTableResponse, Response);
/*
 Blueprint response delegate for picking from a drop table
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPickFromDropTableResponseBP, FLootLockerServerPickFromDropTableResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for computing and locking a drop table
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerComputeAndLockDropTableResponseDelegate, FLootLockerServerComputeAndLockDropTableResponse);
/*
 C++ response delegate for picking from a drop table
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPickFromDropTableResponseDelegate, FLootLockerServerPickFromDropTableResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerDropTableRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerDropTableRequest();	

	static void ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP = FLootLockerServerComputeAndLockDropTableResponseBP(), const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest = FLootLockerServerComputeAndLockDropTableResponseDelegate());
	static void ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP = FLootLockerServerComputeAndLockDropTableResponseBP(), const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest = FLootLockerServerComputeAndLockDropTableResponseDelegate());
	static void ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP = FLootLockerServerComputeAndLockDropTableResponseBP(), const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest = FLootLockerServerComputeAndLockDropTableResponseDelegate());
	static void ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequestBP = FLootLockerServerComputeAndLockDropTableResponseBP(), const FLootLockerServerComputeAndLockDropTableResponseDelegate& OnCompletedRequest = FLootLockerServerComputeAndLockDropTableResponseDelegate());

	static void PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseBP& OnCompletedRequestBP = FLootLockerServerPickFromDropTableResponseBP(), const FLootLockerServerPickFromDropTableResponseDelegate& OnCompletedRequest = FLootLockerServerPickFromDropTableResponseDelegate());
};
