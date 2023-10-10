// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerCurrencyRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Details about a particular currency
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCurrency
{
    GENERATED_BODY()
    /**
     * The unique id of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The name of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     * The unique short code of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Code;
    /**
     * True if this currency can be awarded to the player from the game api
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Game_api_writes_enabled = false;
    /**
     * The time that this currency was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    /**
     * The time that this currency was published
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Published_at;
};

//==================================================
// Request Definitions
//==================================================

// N/A

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerListCurrenciesResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * List of available currencies
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCurrency> Currencies;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================

/**
 * Blueprint response delegate for listing currencies
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListCurrenciesResponseBP, FLootLockerServerListCurrenciesResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for listing currencies
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListCurrenciesResponseDelegate, FLootLockerServerListCurrenciesResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerCurrencyRequest : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerCurrencyRequest();

    static void ListCurrencies(const FLootLockerServerListCurrenciesResponseBP& OnResponseCompletedBP = FLootLockerServerListCurrenciesResponseBP(), const FLootLockerServerListCurrenciesResponseDelegate& OnResponseCompleted = FLootLockerServerListCurrenciesResponseDelegate());
};
