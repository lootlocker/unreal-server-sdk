// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerProgressionGenericTypes.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerProgressionPointsReward
{
    GENERATED_BODY()
	/*
	 The id of the progression this reward is for
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_id = "";
	/*
	 The key of the progression this reward is for
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_key = "";
	/*
	 The name of the progression this reward is for
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_name = "";
	/*
	 The number of points awarded with this reward on the specified progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Amount = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerServerProgressionResetReward
{
    GENERATED_BODY()
	/*
	 The id of the progression this reward is for
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_id = "";
	/*
	 The key of the progression this reward is for
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_key = "";
	/*
	 The name of the progression this reward is for
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Progression_name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerAssetReward
{
    GENERATED_BODY()
	/*
	 The id of the asset this reward is for
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_id = 0;
    /*
     Optional: The id of the specific asset variation that this reward is for
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Asset_variation_id = "";
    /*
     Optional: The id of the specific rental option that this reward is for
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Asset_rental_option_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerRewards
{
    GENERATED_BODY()
	/*
	 A list of progression point rewards that were rewarded
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerProgressionPointsReward> Progression_points_rewards;
	/*
	 A list of progression reset rewards that were rewarded
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerProgressionResetReward> Progression_reset_rewards;
	/*
	 A list of asset rewards that were rewarded
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetReward> Asset_rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAwardedTier
{
    GENERATED_BODY()
	/*
	 Which step was rewarded with the current awarded tier
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Step = 0;
	/*
	 The number of points required for this tier
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Points_threshold = 0;
	/*
	 The rewards awarded with this tier
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerRewards Rewards;
};

//==================================================
// Request Definitions
//==================================================
USTRUCT(BlueprintType)
struct FLootLockerServerModifyScoreRequest
{
    GENERATED_BODY()
	/*
	 The number of points to add or subtract (do not use negative integers)
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Amount = 0;
};
