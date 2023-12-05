// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerCurrencyRequest.h"
#include "LootLockerServerBalanceRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================


/**
 * Possible wallet holder types
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerWalletHolderTypes : uint8
{
    character = 0,
    player = 1,
};

/**
 * 
 */
USTRUCT(BlueprintType, Category="LootLockerServer")
struct FLootLockerServerBalance
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Amount;
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Wallet_id;
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLockerServer")
struct FLootLockerServerCreateWalletRequest
{
    GENERATED_BODY()
    /**
     * ULID of the holder you want to create a wallet for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Holder_id;
    /**
     * The type of holder that this holder id refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Holder_type;
    /**
     * The id of the created wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLockerServer")
struct FLootLockerServerCreditRequest
{
    GENERATED_BODY()
    /**
     * Amount of the given currency to debit/credit to/from the given wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Amount;
    /**
     * The id of the currency that the amount is given in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Currency_id;
    /** The id of the wallet to credit/debit to/from
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Wallet_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLockerServer")
struct FLootLockerServerDebitRequest
{
    GENERATED_BODY()
    /**
     * Amount of the given currency to debit/credit to/from the given wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Amount;
    /**
     * The id of the currency that the amount is given in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Currency_id;
    /** The id of the wallet to credit/debit to/from
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Wallet_id;
};


//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLockerServer")
struct FLootLockerServerListBalancesForWalletResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * List of balances in different currencies in the requested wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerBalance> Balances;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLockerServer")
struct FLootLockerServerGetWalletResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * The unique id of the holder of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Holder_id;
    /**
     * The unique id of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The type of entity that holds this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerWalletHolderTypes type = ELootLockerServerWalletHolderTypes::player;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCreditWalletResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Amount;
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Wallet_id;
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerDebitWalletResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Amount;
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Wallet_id;
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLockerServer")
struct FLootLockerServerCreateWalletResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * The unique id of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Wallet_id;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================
/**
 * Blueprint response delegate for listing balances in a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListBalancesForWalletResponseBP, FLootLockerServerListBalancesForWalletResponse, Response);
/**
 * Blueprint response delegate for getting a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetWalletResponseBP, FLootLockerServerGetWalletResponse, Response);
/**
 * Blueprint response delegate for crediting currency to a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreditWalletResponseBP, FLootLockerServerCreditWalletResponse, Response);
/**
 * Blueprint response delegate for debiting currency from a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDebitWalletResponseBP, FLootLockerServerDebitWalletResponse, Response);
/**
 * Blueprint response delegate for creating a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreateWalletResponseBP, FLootLockerServerCreateWalletResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/**
 * C++ response delegate for listing balances in a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListBalancesForWalletResponseDelegate, FLootLockerServerListBalancesForWalletResponse);
/**
 * C++ response delegate for getting a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetWalletResponseDelegate, FLootLockerServerGetWalletResponse);
/**
 * C++ response delegate for crediting currency to a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerCreditWalletResponseDelegate, FLootLockerServerCreditWalletResponse);
/**
 * C++ response delegate for debiting currency from a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDebitWalletResponseDelegate, FLootLockerServerDebitWalletResponse);
/**
 * C++ response delegate for creating a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerCreateWalletResponseDelegate, FLootLockerServerCreateWalletResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerBalanceRequest : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerBalanceRequest();
    static void ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseBP& OnCompleteBP = FLootLockerServerListBalancesForWalletResponseBP(), const FLootLockerServerListBalancesForWalletResponseDelegate& OnComplete = FLootLockerServerListBalancesForWalletResponseDelegate());
    static void GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseBP& OnCompleteBP = FLootLockerServerGetWalletResponseBP(), const FLootLockerServerGetWalletResponseDelegate& OnComplete = FLootLockerServerGetWalletResponseDelegate());
    static void GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseBP& OnCompleteBP = FLootLockerServerGetWalletResponseBP(), const FLootLockerServerGetWalletResponseDelegate& OnComplete = FLootLockerServerGetWalletResponseDelegate());
    static void CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseBP& OnCompleteBP = FLootLockerServerCreditWalletResponseBP(), const FLootLockerServerCreditWalletResponseDelegate& OnComplete = FLootLockerServerCreditWalletResponseDelegate());
    static void DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseBP& OnCompleteBP = FLootLockerServerDebitWalletResponseBP(), const FLootLockerServerDebitWalletResponseDelegate& OnComplete = FLootLockerServerDebitWalletResponseDelegate());
private:
	static void CreateWallet(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerCreateWalletResponseBP& OnCompleteBP = FLootLockerServerCreateWalletResponseBP(), const FLootLockerServerCreateWalletResponseDelegate& OnComplete = FLootLockerServerCreateWalletResponseDelegate());
};
