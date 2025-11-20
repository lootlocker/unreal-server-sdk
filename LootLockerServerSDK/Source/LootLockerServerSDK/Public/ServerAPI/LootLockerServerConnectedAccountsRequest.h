// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerConnectedAccountsRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Details about a connected authentication provider for a player
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerConnectedAccount
{
    GENERATED_BODY()
    /**
     * Simple provider name (e.g., "steam", "xbox", "psn")
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Provider = "";
    /**
     * Human readable provider name
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Provider_name = "";
    /**
     * The identifier of the player on said provider
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Player_identifier = "";
};

/**
 * Platform information for a single player including their connected accounts
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerPlayerPlatform
{
    GENERATED_BODY()
    /**
     * Integer based Player ID
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Legacy_player_id = 0;
    /**
     * ULID for the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Player_id = "";
    /**
     * List of connected authentication providers
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerConnectedAccount> Connected_accounts;
};

//==================================================
// Request Definitions
//==================================================

/**
 * Request to list connected accounts for multiple players
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerListConnectedAccountsRequest
{
    GENERATED_BODY()
    /**
     * List of Player ULIDs (up to 25 players)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> Player_ids;
    /**
     * List of legacy integer Player IDs (up to 25 players)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<int> Legacy_player_ids;
};

//==================================================
// Response Definitions
//==================================================

/**
 * Response for listing connected accounts for multiple players
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerListConnectedAccountsResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * List of player platform information including connected accounts
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerPlatform> Player_platforms;
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

    /**
     * List connected accounts for multiple players (up to 25)
     * You can provide player ULIDs, legacy player IDs, or both
     * 
     * @param PlayerULIDs List of Player ULIDs
     * @param LegacyPlayerIDs List of legacy integer Player IDs
     * @param OnResponseCompletedBP Blueprint delegate for handling the response
     * @param OnResponseCompleted C++ delegate for handling the response
     */
    static void ListConnectedAccounts(const TArray<FString>& PlayerULIDs, const TArray<int>& LegacyPlayerIDs, const FLootLockerServerListConnectedAccountsResponseBP& OnResponseCompletedBP = FLootLockerServerListConnectedAccountsResponseBP(), const FLootLockerServerListConnectedAccountsResponseDelegate& OnResponseCompleted = FLootLockerServerListConnectedAccountsResponseDelegate());
};
