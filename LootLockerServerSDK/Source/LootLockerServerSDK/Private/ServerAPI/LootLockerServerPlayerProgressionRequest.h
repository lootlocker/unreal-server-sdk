// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/ServerAPI/LootLockerServerProgressionGenericTypes.h"
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
	 Which step (steps are configured in the console) of the progression the player is on
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Step = 0;
	/*
	 How many points this player has in this progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Points = 0;
	/*
	 The number of points needed to enter the current step of the progression (already cleared by the player)
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
struct FLootLockerServerSinglePlayerProgressionResponse : public FLootLockerServerResponse
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
	 Which step (steps are configured in the console) of the progression the player is on
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Step = 0;
	/*
	 How many points this player has in this progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Points = 0;
	/*
	 The number of points needed to enter the current step of the progression (already cleared by the player)
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
struct FLootLockerServerSinglePlayerProgressionWithRewardsResponse : public FLootLockerServerSinglePlayerProgressionResponse
{
    GENERATED_BODY()
	/*
	 A list of the tiers that were awarded as an effect of the progression state change
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAwardedTier> Awarded_tiers;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerProgressionListResponse : public FLootLockerServerResponse
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
    TArray<FLootLockerServerPlayerProgression> Items;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================
/*
 Blueprint response delegate for receiving a single player progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionResponseBP, FLootLockerServerSinglePlayerProgressionResponse, Response);
/*
 Blueprint response delegate for receiving a list of player progressions
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerProgressionListResponseBP, FLootLockerServerPlayerProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single player progression with rewards
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP, FLootLockerServerSinglePlayerProgressionWithRewardsResponse, Response);
/*
 Blueprint response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeletePlayerProgressionResponseBP, FLootLockerServerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for receiving a single player progression
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionResponseDelegate, FLootLockerServerSinglePlayerProgressionResponse);
/*
 C++ response delegate for receiving a list of player progressions
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerProgressionListResponseDelegate, FLootLockerServerPlayerProgressionListResponse);
/*
 C++ response delegate for receiving a single player progression with rewards
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate, FLootLockerServerSinglePlayerProgressionWithRewardsResponse);
/*
 C++ response delegate for deleting a progression. Will be empty if no error occured.
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
    static void GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerSinglePlayerProgressionResponseBP(), const FLootLockerServerSinglePlayerProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionResponseDelegate());
    static void AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate());
    static void ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP(), const FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSinglePlayerProgressionWithRewardsResponseDelegate());
    static void DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerDeletePlayerProgressionResponseBP(), const FLootLockerServerDeletePlayerProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerDeletePlayerProgressionResponseDelegate());
};
