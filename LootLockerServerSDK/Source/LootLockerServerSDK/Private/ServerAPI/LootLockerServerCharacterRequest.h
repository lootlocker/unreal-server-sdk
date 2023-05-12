// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"

#include "LootLockerServerCharacterRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerCharacter
{
	GENERATED_BODY()
	/*
	 The ID of the character
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Id;
    /*
     Whether this is the players default character
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Default;
    /*
     The name of the character
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerCharacterItemRentalData
{
    GENERATED_BODY()
    /*
     Whether this item is a rental item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Is_rental;
    /*
     Optional: How much time (in seconds) that is left before this rental item expires
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Time_left;
    /*
     Optional: Total duration (in seconds) that this rental item is rented for
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Duration;
    /*
     Optional: Whether this rental item is currently active
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it has a valid value and then you can (in code) use .ToBool() or (in blueprint) use a case insensitive string comparison for "true"
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Is_active;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerCharacterInventoryItem
{
    GENERATED_BODY()
    /*
     The instance id of this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id;
    /*
     Optional: This item's variation id
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Variation_id;
    /*
     Optional: This item's rental option id
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Rental_option_id;
    /*
     The acquisition source for this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Acquisition_source;
    /*
     The asset this item refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset; //TODO: Assets not implemented
    /*
     Information about this items rental state
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerPlayerCharacterItemRentalData Rental;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerCharacterLoadoutItem
{
    GENERATED_BODY()
    /*
     Optional: This item's variation id
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Variation_id;
    /*
     The instance id of this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id;
    /*
     The time that this item was mounted
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Mounted_at;
    /*
     The asset this item refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset; //TODO: Assets not implemented
    /*
     Information about this items rental state
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerPlayerCharacterItemRentalData Rental;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToCharacterLoadoutRequest
{
    GENERATED_BODY()
    /*
     The id of the asset instance to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Instance_id;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToCharacterLoadoutByAssetIdAndVariationIdRequest
{
    GENERATED_BODY()
    /*
     The id of the asset to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_id;
    /*
     The asset variation id of the asset variation to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_variation_id;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToCharacterLoadoutByAssetIdAndRentalOptionIdRequest
{
    GENERATED_BODY()
    /*
     The id of the asset to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_id;
    /*
     The rental option id of the rental option to equip
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Rental_option_id;
};

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerCharactersResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    
    /*
     List of player characters
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerCharacter> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetCharacterInventoryResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    
    /*
     The total number of items in this player characters inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Total;
    /*
     List of items in this player characters inventory according to the requested pagination
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerCharacterInventoryItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerFullCharacterLoadoutResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()

    /*
     List of the requested player character's loadout
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerCharacterLoadoutItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetCharacterLoadoutResponse : public FLootLockerServerFullCharacterLoadoutResponse
{
    GENERATED_BODY()
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToCharacterLoadoutResponse : public FLootLockerServerFullCharacterLoadoutResponse
{
    GENERATED_BODY()
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerUnequipAssetFromCharacterLoadoutResponse : public FLootLockerServerFullCharacterLoadoutResponse
{
    GENERATED_BODY()
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for getting a player's characters
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerCharacterResponseBP, FLootLockerServerGetPlayerCharactersResponse, Response);
/*
 Blueprint response delegate for getting a player characters inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetCharacterInventoryResponseBP, FLootLockerServerGetCharacterInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player characters loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetCharacterLoadoutResponseBP, FLootLockerServerGetCharacterLoadoutResponse, Response);
/*
 Blueprint response delegate for equipping an asset to a player characters loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerEquipAssetToCharacterLoadoutResponseBP, FLootLockerServerEquipAssetToCharacterLoadoutResponse, Response);
/*
 Blueprint response delegate for unequipping an asset from a player characters loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP, FLootLockerServerUnequipAssetFromCharacterLoadoutResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for getting a player's characters
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPlayerCharacterResponseDelegate, FLootLockerServerGetPlayerCharactersResponse);
/*
 C++ response delegate for getting a player characters inventory
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetCharacterInventoryResponseDelegate, FLootLockerServerGetCharacterInventoryResponse);
/*
 C++ response delegate for getting a player characters loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetCharacterLoadoutResponseDelegate, FLootLockerServerGetCharacterLoadoutResponse);
/*
 C++ response delegate for equipping an asset to a player characters loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate, FLootLockerServerEquipAssetToCharacterLoadoutResponse);
/*
 C++ response delegate for unequipping an asset from a player characters loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate, FLootLockerServerUnequipAssetFromCharacterLoadoutResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerCharacterRequest : public UObject
{
	GENERATED_BODY()
	public:	
    ULootLockerServerCharacterRequest();

    static void GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseBP& OnCompletedRequestBP = FLootLockerServerGetPlayerCharacterResponseBP(), const FLootLockerServerGetPlayerCharacterResponseDelegate& OnCompletedRequest = FLootLockerServerGetPlayerCharacterResponseDelegate());
    static void GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerGetCharacterInventoryResponseBP(), const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerGetCharacterInventoryResponseDelegate());
    static void GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerGetCharacterInventoryResponseBP(), const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerGetCharacterInventoryResponseDelegate());
    static void GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerGetCharacterLoadoutResponseBP(), const FLootLockerServerGetCharacterLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerGetCharacterLoadoutResponseDelegate());
    static void EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToCharacterLoadoutResponseBP(), const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate());
    static void EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToCharacterLoadoutResponseBP(), const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate());
    static void EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToCharacterLoadoutResponseBP(), const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate());
	static void UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP(), const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate());
};
