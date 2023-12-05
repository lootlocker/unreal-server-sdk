// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerPurchaseRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerPurchaseStatus : uint8
{
		Open = 0			UMETA(DisplayName = "Open"),
		Succeeded = 1		UMETA(DisplayName = "Succeeded"),
		Refunded = 2		UMETA(DisplayName = "Refunded"),
		Canceled = 3		UMETA(DisplayName = "Canceled"),
		Failed = 4			UMETA(DisplayName = "Failed")
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPurchaseProduct
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
     The acquisition source for this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Acquisition_source = "";
    /*
     The full asset description
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FLootLockerServerAsset Asset;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerPurchaseStatusResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 The current status of the order
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	ELootLockerServerPurchaseStatus Order_status = ELootLockerServerPurchaseStatus::Open;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPurchaseStatusWithProductsResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 The current status of the order
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	ELootLockerServerPurchaseStatus Order_status = ELootLockerServerPurchaseStatus::Open;
	/*
	 A list of the products in the purchase
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPurchaseProduct> Products;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for checking a purchase's status
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPurchaseStatusResponseBP, FLootLockerServerPurchaseStatusResponse, Response);
/*
 Blueprint response delegate for checking a purchase's status including the products related to the purchase
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPurchaseStatusWithProductsResponseBP, FLootLockerServerPurchaseStatusWithProductsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for checking a purchase's status
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPurchaseStatusResponseDelegate, FLootLockerServerPurchaseStatusResponse);
/*
 C++ response delegate for checking a purchase's status including the products related to the purchase
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPurchaseStatusWithProductsResponseDelegate, FLootLockerServerPurchaseStatusWithProductsResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPurchaseRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerPurchaseRequest();	

	static void CheckPurchaseStatusForPlayerByID(int PlayerID, int PurchaseID, const FLootLockerServerPurchaseStatusResponseBP& OnCompletedRequestBP = FLootLockerServerPurchaseStatusResponseBP(), const FLootLockerServerPurchaseStatusResponseDelegate& OnCompletedRequest = FLootLockerServerPurchaseStatusResponseDelegate());
	static void CheckPurchaseStatusForPlayerByPlatformTransactionID(int PlayerID, int PlatformTransactionID, const FLootLockerServerPurchaseStatusResponseBP& OnCompletedRequestBP = FLootLockerServerPurchaseStatusResponseBP(), const FLootLockerServerPurchaseStatusResponseDelegate& OnCompletedRequest = FLootLockerServerPurchaseStatusResponseDelegate());
	static void CheckPurchaseStatusForPlayerByIDWith_IncludeProducts(int PlayerID, int PurchaseID, const FLootLockerServerPurchaseStatusWithProductsResponseBP& OnCompletedRequestBP = FLootLockerServerPurchaseStatusWithProductsResponseBP(), const FLootLockerServerPurchaseStatusWithProductsResponseDelegate& OnCompletedRequest = FLootLockerServerPurchaseStatusWithProductsResponseDelegate());
	static void CheckPurchaseStatusForPlayerByPlatformTransactionID_IncludeProducts(int PlayerID, int PlatformTransactionID, const FLootLockerServerPurchaseStatusWithProductsResponseBP& OnCompletedRequestBP = FLootLockerServerPurchaseStatusWithProductsResponseBP(), const FLootLockerServerPurchaseStatusWithProductsResponseDelegate& OnCompletedRequest = FLootLockerServerPurchaseStatusWithProductsResponseDelegate());

	private:
	static const TMultiMap<FString, FString> IncludeProductsQueryParams;
};
