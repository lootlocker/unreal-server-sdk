// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"

#include "LootLockerServerAssetRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerAssetStorageKeyValueSet
{
	GENERATED_BODY()
	/*
	 The key for this set, used to access the value
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key;
	/*
	 The Value of this set, this is the data
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Value;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetRentalOptionLinks
{
    GENERATED_BODY()
    /*
     URL to storage from where you can download this rental option's thumbnail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Thumbnail;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetRentalOption
{
    GENERATED_BODY()
    /*
     The id of this rental option
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Id;
    /*
     The name of this rental option
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /*
     Optional: Total duration (in seconds) that this rental item is rented for
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Duration;
    /*
     The price of this rental option
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Price;
    /*
     Optional: A sales price of this rental option. If it is not null, then there is a sale for this item and this price should be used instead of Price
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Sales_price;
    /*
     Collection of links related to this rental option
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetRentalOptionLinks Links;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetRarity
{
    GENERATED_BODY()
    /*
     The name of the rarity this Asset is classed as
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /*
     The short the rarity this Asset is classed as
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Short_name;
    /*
     The color for this rarity class
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Color;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetFile
{
    GENERATED_BODY()
    /*
     The url where this file can be downloaded from
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Url;
    /*
     A list of tags applied to this file
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> Tags;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetCandidateInformation
{
    GENERATED_BODY()
    /*
     The id of the player who created this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Created_by_player_id;
    /*
     The UID of the player who created this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_by_player_uid;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetVariationLinks
{
    GENERATED_BODY()
    /*
     URL to storage from where you can download this asset variation's thumbnail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Thumbnail;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetVariationProperty
{
    GENERATED_BODY()
    /*
     Path on disk (developer configured) to this asset's material
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Material_path;
    /*
     Path on disk (developer configured) to this asset's binding
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Binding_path;
    /*
     Id of the bone this property applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Bone_id;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetHeroEquipException
{
    GENERATED_BODY()
    /*
     Whether this hero can equip this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Can_equip;
    /*
     The id of the hero that this exception applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Hero_id;
    /*
     The name of the hero that this exception applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Hero_name;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetVariation
{
    GENERATED_BODY()
    /*
     The id of this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Id;
    /*
     The name of this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /*
     The primary color of this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Primary_color;
    /*
     The secondary color of this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Secondary_color;
    /*
     List of properties configured for this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetVariationProperty> Properties;
    /*
     Collection of links related to this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetVariationLinks Links;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetLinks
{
    GENERATED_BODY()
    /*
     URL to storage from where you can download this rental option's thumbnail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Thumbnail;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAsset
{
    GENERATED_BODY()
    /*
     The id of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Id;
    /*
     The uuid of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Uuid;
    /*
     The name of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /*
     Whether this assset is active
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Active;
    /*
     The price of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Price;
    /*
     Optional: A sales price of this asset. If it is not null, then there is a sale for this item and this price should be used instead of Price
    
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Sales_price;
    /*
     A string representation of how to display the price in the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Display_price;
    /*
     Path of the thumbnail to use in the shop for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Shop_thumbnail;
    /*
     The name of the context this asset lives within
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Context;
    /*
     The id of the context this asset lives within
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Context_id;
    /*
     List of the character classes that this asset applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<int> Character_classes;
    /*
     Whether this asset is detachable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Detachable;
    /*
     Whether this asset is purchasable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Purchasable;
    /*
     Whether this asset is initially purchaseble
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Initially_purchasable;
    /*
     Timestamp of when this asset was last updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated;
    /*
     Optional: Timestamp of when this asset was marked new
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Marked_new;
    /*
     The default variation id to use for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Default_variation_id;
    /*
     List of variations applicable to this variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetVariation> Variations;
    /*
     Description for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Description;
    /*
     Whether this asset is featured
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Featured;
    /*
     Whether this asset is context locked
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Context_locked;
    /*
     Optional: Whether this asset unlocks the context it refers to
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it has a valid value and then you can (in code) use .ToBool() or (in blueprint) use a case insensitive string comparison for "true"
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Unlocks_context;
    /*
     The rarity of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetRarity Rarity;
    /*
     Whether this asset is considered popular
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Popular;
    /*
     The popularity score of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Popularity_score;
    /*
     Whether this asset is a unique instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Unique_instance;
    /*
     List of rental options configured for this asset 
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetRentalOption> Rental_options;
    /*
     List of files related to this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetFile> Files;
    /*
     Data entities configured for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> Data_entities;
    /*
     Author data of this asset
     
     If this game uses user generated content, and this asset is user generated then this property contains data on the author of this asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetCandidateInformation Asset_candidate;
    /*
     Optional: If configured for this asset, then this shows the max picks of this asset from drop tables
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Drop_table_max_picks;
    /*
     Links related to this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetLinks Links;
    /*
     List of key values configured for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetStorageKeyValueSet> Storage;
    /*
     List of equip exceptions configured for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetHeroEquipException> Hero_equip_exceptions;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetTemplateRequest
{
    GENERATED_BODY()
    /*
     TODO: Document
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Templated;
};

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetAssetsResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    
    /*
     The total number of assets present for this game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Total;
    /*
     List of assets returned for this specific request, in accordance with the supplied pagination options
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAsset> Items;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for getting assets
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetAssetsResponseBP, FLootLockerServerGetAssetsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for getting assets
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetAssetsResponseDelegate, FLootLockerServerGetAssetsResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerAssetRequest : public UObject
{
    GENERATED_BODY()
    public:
    ULootLockerServerAssetRequest();

    static void GetAssets(const FLootLockerServerGetAssetsResponseBP& OnCompletedRequestBP = FLootLockerServerGetAssetsResponseBP(), const FLootLockerServerGetAssetsResponseDelegate& OnCompletedRequest = FLootLockerServerGetAssetsResponseDelegate());
    static void GetPaginatedAssets(int Count, int After, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequestBP = FLootLockerServerGetAssetsResponseBP(), const FLootLockerServerGetAssetsResponseDelegate& OnCompletedRequest = FLootLockerServerGetAssetsResponseDelegate());
};
