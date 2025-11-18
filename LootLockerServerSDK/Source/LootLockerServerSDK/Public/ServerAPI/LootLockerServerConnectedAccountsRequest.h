// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerConnectedAccountsRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Details about a particular connected account
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerConnectedAccount
{
    GENERATED_BODY()
    /**
     * The platform of the connected account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Platform = "";
    /**
     * The platform identifier for the account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Platform_id = "";
    /**
     * The creation date of the connected account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at = "";
    /**
     * The last update date of the connected account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at = "";
};

//==================================================
// Request Definitions
//==================================================

// N/A

//==================================================
// Response Definitions
//==================================================

/**
 * Response for listing connected accounts
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerListConnectedAccountsResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * List of connected accounts for the specified player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerConnectedAccount> Accounts;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/**
 * Blueprint response delegate for listing connected accounts
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListConnectedAccountsResponseBP, FLootLockerServerListConnectedAccountsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for listing connected accounts
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListConnectedAccountsResponseDelegate, FLootLockerServerListConnectedAccountsResponse);

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerConnectedAccountsRequest : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerConnectedAccountsRequest();

    static void ListConnectedAccounts(const FString& PlayerULID, const FLootLockerServerListConnectedAccountsResponseBP& OnResponseCompletedBP = FLootLockerServerListConnectedAccountsResponseBP(), const FLootLockerServerListConnectedAccountsResponseDelegate& OnResponseCompleted = FLootLockerServerListConnectedAccountsResponseDelegate());
};
