// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"
#include "LootLockerServerSDK/Private/ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerHeroRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerHero
{
    GENERATED_BODY()
    /*
     The ID of this player hero
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Id = 0;
    /*
     The ID of the hero itself
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Hero_id = 0;
    /*
     The asset instance id of the hero
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id = 0;
    /*
     The name of the hero
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Hero_name = "";
    /*
     The name of the character
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Character_name = "";
    /*
     The name of the class that this hero belongs to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Class_name = "";
    /*
     Whether this is the players default hero
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Is_default = false;
    /*
     The asset variation id of the hero
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_variation_id = 0;
    /*
     The asset this hero refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAsset Asset;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerHeroItemRentalData
{
    GENERATED_BODY()
    /*
     Whether this item is a rental item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Is_rental = false;
    /*
     Optional: How much time (in seconds) that is left before this rental item expires
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Time_left = "";
    /*
     Optional: Total duration (in seconds) that this rental item is rented for
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Duration = "";
    /*
     Optional: Whether this rental item is currently active
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it has a valid value and then you can (in code) use .ToBool() or (in blueprint) use a case insensitive string comparison for "true"
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Is_active = "";
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerHeroInventoryItem
{
    GENERATED_BODY()
    /*
     The instance id of this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id = 0;
    /*
     Optional: This item's variation id
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Variation_id = "";
    /*
     Optional: This item's rental option id
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Rental_option_id = "";
    /*
     The acquisition source for this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Acquisition_source = "";
    /*
     The asset this item refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAsset Asset;
    /*
     Information about this items rental state
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerPlayerHeroItemRentalData Rental;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerHeroLoadoutItem
{
    GENERATED_BODY()
    /*
     Optional: This item's variation id
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Variation_id = "";
    /*
     The instance id of this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id = 0;
    /*
     The time that this item was mounted
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Mounted_at = "";
    /*
     The asset this item refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAsset Asset;
    /*
     Information about this items rental state
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerPlayerHeroItemRentalData Rental;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToHeroLoadoutRequest
{
    GENERATED_BODY()
    /*
     The id of the asset instance to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id = 0;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndVariationIdRequest
{
    GENERATED_BODY()
    /*
     The id of the asset to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_id = 0;
    /*
     The asset variation id of the asset variation to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_variation_id = 0;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndRentalOptionIdRequest
{
    GENERATED_BODY()
    /*
     The id of the asset to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_id = 0;
    /*
     The rental option id of the rental option to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Rental_option_id = 0;
};

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerHeroesResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    
    /*
     List of player heroes
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerHero> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetHeroInventoryResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    
    /*
     The total number of items in this player heroes inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Total = 0;
    /*
     List of items in this player heroes inventory according to the requested pagination
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerHeroInventoryItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerFullHeroLoadoutResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()

    /*
     List of the requested player heroes's loadout
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerHeroLoadoutItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetHeroLoadoutResponse : public FLootLockerServerFullHeroLoadoutResponse
{
    GENERATED_BODY()
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToHeroLoadoutResponse : public FLootLockerServerFullHeroLoadoutResponse
{
    GENERATED_BODY()
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerUnequipAssetFromHeroLoadoutResponse : public FLootLockerServerFullHeroLoadoutResponse
{
    GENERATED_BODY()
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for getting a player's heroes
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerHeroResponseBP, FLootLockerServerGetPlayerHeroesResponse, Response);
/*
 Blueprint response delegate for getting a player heroes inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetHeroInventoryResponseBP, FLootLockerServerGetHeroInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player heroes loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetHeroLoadoutResponseBP, FLootLockerServerGetHeroLoadoutResponse, Response);
/*
 Blueprint response delegate for equipping an asset to a player heroes loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerEquipAssetToHeroLoadoutResponseBP, FLootLockerServerEquipAssetToHeroLoadoutResponse, Response);
/*
 Blueprint response delegate for unequipping an asset from a player heroes loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP, FLootLockerServerUnequipAssetFromHeroLoadoutResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for getting a player's heroes
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPlayerHeroResponseDelegate, FLootLockerServerGetPlayerHeroesResponse);
/*
 C++ response delegate for getting a player heroes inventory
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetHeroInventoryResponseDelegate, FLootLockerServerGetHeroInventoryResponse);
/*
 C++ response delegate for getting a player heroes loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetHeroLoadoutResponseDelegate, FLootLockerServerGetHeroLoadoutResponse);
/*
 C++ response delegate for equipping an asset to a player heroes loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate, FLootLockerServerEquipAssetToHeroLoadoutResponse);
/*
 C++ response delegate for unequipping an asset from a player heroes loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate, FLootLockerServerUnequipAssetFromHeroLoadoutResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerHeroRequest : public UObject
{
    GENERATED_BODY()
    public:
    ULootLockerServerHeroRequest();

    static void GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseBP& OnCompletedRequestBP = FLootLockerServerGetPlayerHeroResponseBP(), const FLootLockerServerGetPlayerHeroResponseDelegate& OnCompletedRequest = FLootLockerServerGetPlayerHeroResponseDelegate());
    static void GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerGetHeroInventoryResponseBP(), const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerGetHeroInventoryResponseDelegate());
    static void GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerGetHeroInventoryResponseBP(), const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerGetHeroInventoryResponseDelegate());
    static void GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerGetHeroLoadoutResponseBP(), const FLootLockerServerGetHeroLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerGetHeroLoadoutResponseDelegate());
    static void EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToHeroLoadoutResponseBP(), const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate());
    static void EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToHeroLoadoutResponseBP(), const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate());
    static void EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToHeroLoadoutResponseBP(), const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate());
    static void UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP(), const FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate());
};
