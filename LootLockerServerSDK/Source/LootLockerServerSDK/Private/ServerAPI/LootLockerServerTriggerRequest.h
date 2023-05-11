// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"

#include "LootLockerServerTriggerRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerTriggeredLevel
{
	GENERATED_BODY()
	/*
	 The level rewarded by the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Level;
	/*
	 Whether the level is a prestige level.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool Is_prestige;
	/*
	 The XP threshold for the level.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int XP_threshold;
	
};

USTRUCT(BlueprintType)
struct FLootLockerServerTriggeredXP
{
	GENERATED_BODY()

	/*
	 The XP before trigger was invoked
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Previous;
	/*
	 The XP after trigger was invoked
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Current;
};

USTRUCT(BlueprintType)
struct FLootLockerServerTriggeredAsset
{
	GENERATED_BODY()

	/*
	 The ID of the asset granted by the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int ID;
	/*
	 The UUID of the asset granted by the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString UUID;
	/*
	 The Name of the asset granted by the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name;
	/*
	 Whether the asset granted by the trigger is active.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool Active;
};

//==================================================
// Request Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerInvokeTriggerForPlayerRequest
{
	GENERATED_BODY()
	/*
	 The name of the trigger to invoke.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name;
	/*
	The player id of the player for whom to invoke the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Player_id;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerInvokeTriggerResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 Information on the XP rewarded by the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FLootLockerServerTriggeredXP XP;
	/*
	 Information on of the levels rewarded by the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerTriggeredLevel> Levels;
	/*
	 Information on of the assets rewarded by the trigger.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerTriggeredAsset> Granted_assets; //TODO: Asset Support not yet fully implemented
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for invoking a trigger
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerInvokeTriggerResponseBP, FLootLockerServerInvokeTriggerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for invoking a trigger
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerInvokeTriggerResponseDelegate, FLootLockerServerInvokeTriggerResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerTriggerRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerTriggerRequest();	

	static void InvokeTriggerForPlayer(FString TriggerName, int PlayerId, const FLootLockerServerInvokeTriggerResponseBP& OnCompletedRequestBP = FLootLockerServerInvokeTriggerResponseBP(), const FLootLockerServerInvokeTriggerResponseDelegate& OnCompletedRequest = FLootLockerServerInvokeTriggerResponseDelegate());
};
