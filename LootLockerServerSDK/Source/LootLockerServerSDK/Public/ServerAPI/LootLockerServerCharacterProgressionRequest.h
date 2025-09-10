// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "ServerAPI/LootLockerServerProgressionGenericTypes.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerCharacterProgressionRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerCharacterProgression
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
	 The ULID of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_id = "";
	/*
	 Which step (steps are configured in the console) of the progression the character is on
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Step = 0;
	/*
	 How many points this character has in this progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Points = 0;
	/*
	 The number of points needed to enter the current step of the progression (already cleared by the character)
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
struct FLootLockerServerSingleCharacterProgressionResponse : public FLootLockerServerResponse
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
	 The ULID of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_id = "";
	/*
	 Which step (steps are configured in the console) of the progression the character is on
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Step = 0;
	/*
	 How many points this character has in this progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Points = 0;
	/*
	 The number of points needed to enter the current step of the progression (already cleared by the character)
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
struct FLootLockerServerSingleCharacterProgressionWithRewardsResponse : public FLootLockerServerSingleCharacterProgressionResponse
{
    GENERATED_BODY()
	/*
	 A list of the tiers that were awarded as an effect of the progression state change
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerProgressionTier> Awarded_tiers;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCharacterProgressionListResponse : public FLootLockerServerResponse
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
    TArray<FLootLockerServerCharacterProgression> Items;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================
/*
 Blueprint response delegate for receiving a single character progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleCharacterProgressionResponseBP, FLootLockerServerSingleCharacterProgressionResponse, Response);
/*
 Blueprint response delegate for receiving a list of character progressions
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCharacterProgressionListResponseBP, FLootLockerServerCharacterProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single character progression with rewards
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP, FLootLockerServerSingleCharacterProgressionWithRewardsResponse, Response);
/*
 Blueprint response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteCharacterProgressionResponseBP, FLootLockerServerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for receiving a single character progression
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSingleCharacterProgressionResponseDelegate, FLootLockerServerSingleCharacterProgressionResponse);
/*
 C++ response delegate for receiving a list of character progressions
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerCharacterProgressionListResponseDelegate, FLootLockerServerCharacterProgressionListResponse);
/*
 C++ response delegate for receiving a single character progression with rewards
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate, FLootLockerServerSingleCharacterProgressionWithRewardsResponse);
/*
 C++ response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDeleteCharacterProgressionResponseDelegate, FLootLockerServerResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerCharacterProgressionRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerCharacterProgressionRequest();	

    static void GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerCharacterProgressionListResponseBP(), const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerCharacterProgressionListResponseDelegate());
    static void GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerCharacterProgressionListResponseBP(), const FLootLockerServerCharacterProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerCharacterProgressionListResponseDelegate());
    static void GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerSingleCharacterProgressionResponseBP(), const FLootLockerServerSingleCharacterProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerSingleCharacterProgressionResponseDelegate());
    static void AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP(), const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP(), const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate());
    static void ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP(), const FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate& OnCompletedRequest = FLootLockerServerSingleCharacterProgressionWithRewardsResponseDelegate());
    static void DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerDeleteCharacterProgressionResponseBP(), const FLootLockerServerDeleteCharacterProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerDeleteCharacterProgressionResponseDelegate());
};
