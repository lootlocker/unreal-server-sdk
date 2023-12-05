// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "ServerAPI/LootLockerServerProgressionGenericTypes.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerInstanceProgressionRequest.generated.h"


//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerInstanceProgression
{
	GENERATED_BODY()
		/*
		 The ID of the progression
		*/
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Id = "";
	/*
	 The key of the progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Progression_key = "";
	/*
	 The name of the progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Progression_name = "";
	/*
	 Which step (steps are configured in the console) of the progression the instance is on
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Step = 0;
	/*
	 How many points this instance has in this progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Points = 0;
	/*
	 The number of points needed to enter the current step of the progression (already cleared by the instance)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Previous_threshold = 0;
	/*
	 The number of points needed to enter the next step of the progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Next_threshold = 0;
	/*
	 The time of the last level up
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Last_level_up = "";
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerSingleInstanceProgressionResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
		/*
		 The ID of the progression
		*/
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Id = "";
	/*
	 The key of the progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Progression_key = "";
	/*
	 The name of the progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Progression_name = "";
	/*
	 Which step (steps are configured in the console) of the progression the instance is on
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Step = 0;
	/*
	 How many points this instance has in this progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Points = 0;
	/*
	 The number of points needed to enter the current step of the progression (already cleared by the instance)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Previous_threshold = 0;
	/*
	 The number of points needed to enter the next step of the progression
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		int32 Next_threshold = 0;
	/*
	 The time of the last level up
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FString Last_level_up = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerSingleInstanceProgressionWithRewardsResponse : public FLootLockerServerSingleInstanceProgressionResponse
{
	GENERATED_BODY()
		/*
		 A list of the tiers that were awarded as an effect of the progression state change
		*/
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		TArray<FLootLockerServerProgressionTier> Awarded_tiers;
};

USTRUCT(BlueprintType)
struct FLootLockerServerInstanceProgressionListResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
		/*
		 The current pagination data of the requested data
		*/
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		FLootLockerServerKeyBasedPagination Pagination;
	/*
	 List of progression items according to the current pagination settings
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
		TArray<FLootLockerServerInstanceProgression> Items;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================
/*
 Blueprint response delegate for receiving a single instance progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleInstanceProgressionResponseBP, FLootLockerServerSingleInstanceProgressionResponse, Response);
/*
 Blueprint response delegate for receiving a list of instance progressions
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerInstanceProgressionListResponseBP, FLootLockerServerInstanceProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single instance progression with rewards
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP, FLootLockerServerSingleInstanceProgressionWithRewardsResponse, Response);
/*
 Blueprint response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteInstanceProgressionResponseBP, FLootLockerServerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for receiving a single Instance progression
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSingleInstanceProgressionResponseDelegate, FLootLockerServerSingleInstanceProgressionResponse);
/*
 C++ response delegate for receiving a list of Instance progressions
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerInstanceProgressionListResponseDelegate, FLootLockerServerInstanceProgressionListResponse);
/*
 C++ response delegate for receiving a single Instance progression with rewards
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate, FLootLockerServerSingleInstanceProgressionWithRewardsResponse);
/*
 C++ response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDeleteInstanceProgressionResponseDelegate, FLootLockerServerResponse);

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerInstanceProgressionRequest : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerServerInstanceProgressionRequest();

	static void GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerInstanceProgressionListResponseBP(), const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerInstanceProgressionListResponseDelegate());
	static void GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerInstanceProgressionListResponseBP(), const FLootLockerServerInstanceProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerInstanceProgressionListResponseDelegate());
	static void GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerSingleInstanceProgressionResponseBP(), const FLootLockerServerSingleInstanceProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerSingleInstanceProgressionResponseDelegate());
	static void AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP(), const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate());
	static void SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP(), const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate());
	static void ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP(), const FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSingleInstanceProgressionWithRewardsResponseDelegate());
	static void DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerDeleteInstanceProgressionResponseBP(), const FLootLockerServerDeleteInstanceProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerDeleteInstanceProgressionResponseDelegate());
};