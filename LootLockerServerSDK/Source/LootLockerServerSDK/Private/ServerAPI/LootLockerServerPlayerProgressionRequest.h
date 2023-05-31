// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"
#include "LootLockerServerSDK/Private/ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerPlayerProgressionRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerProgression
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_key = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_name = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Points = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Previous_threshold = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Next_threshold = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Last_level_up = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerProgressionPointsReward
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_id = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_key = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_name = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Amount = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerServerProgressionResetReward
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_id = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_key = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerAssetReward
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Asset_id = 0;
    /*
     Optional: TODO: Document
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Asset_variation_id = "";
    /*
     Optional: TODO: Document
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Asset_rental_option_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerRewards
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerServerProgressionPointsReward> Progression_points_rewards;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerServerProgressionResetReward> Progression_reset_rewards;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerServerAssetReward> Asset_rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAwardedTier
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Points_threshold = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerServerRewards Rewards;
};

//==================================================
// Request Definitions
//==================================================
USTRUCT(BlueprintType)
struct FLootLockerServerModifyScoreRequest
{
    GENERATED_BODY()
    UPROPERTY()
    int32 Amount = 0;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerSinglePlayerProgressionResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
	/*
	 TODO: Document :: COPY!!!!
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_key = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_name = "";
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Points = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Previous_threshold = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Next_threshold = 0;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Last_level_up = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerSinglePlayerProgressionWithRewardsResponse : public FLootLockerServerSinglePlayerProgressionResponse
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerServerAwardedTier> Awarded_tiers;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerProgressionListResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerServerKeyBasedPagination Pagination;
	/*
	 TODO: Document
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerServerPlayerProgression> Items;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================
/*
 Blueprint response delegate for TODO: Document
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerSingleProgressionResponseBP, FLootLockerServerSinglePlayerProgressionResponse, Response);
/*
 Blueprint response delegate for TODO: Document
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerProgressionListResponseBP, FLootLockerServerPlayerProgressionListResponse, Response);
/*
 Blueprint response delegate for TODO: Document
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP, FLootLockerServerSinglePlayerProgressionWithRewardsResponse, Response);
/*
 Blueprint response delegate for TODO: Document
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeletePlayerProgressionResponseBP, FLootLockerServerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for TODO: Document
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionResponseDelegate, FLootLockerServerSinglePlayerProgressionResponse);
/*
 C++ response delegate for TODO: Document
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerProgressionListResponseDelegate, FLootLockerServerPlayerProgressionListResponse);
/*
 C++ response delegate for TODO: Document
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate, FLootLockerServerSinglePlayerProgressionWithRewardsResponse);
/*
 C++ response delegate for TODO: Document
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDeletePlayerProgressionResponseDelegate, FLootLockerServerResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPlayerProgressionRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerPlayerProgressionRequest();	

    static void GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerPlayerProgressionListResponseBP(), const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerPlayerProgressionListResponseDelegate());
    static void GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerPlayerProgressionListResponseBP(), const FLootLockerServerPlayerProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerPlayerProgressionListResponseDelegate());
    static void GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerPlayerSingleProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerPlayerSingleProgressionResponseBP(), const FLootLockerServerSinglePlayerProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionResponseDelegate());
    static void AddPointsProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate());
    static void ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate());
    static void DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerDeletePlayerProgressionResponseBP(), const FLootLockerServerDeletePlayerProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerDeletePlayerProgressionResponseDelegate());
};
