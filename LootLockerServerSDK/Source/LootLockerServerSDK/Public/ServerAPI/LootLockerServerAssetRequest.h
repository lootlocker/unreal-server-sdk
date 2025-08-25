// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "../LootLockerServerResponse.h"
#include "LootLockerServerMetadataRequest.h"

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
	FString Key = "";
	/*
	 The Value of this set, this is the data
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Value = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerAssetInstanceStorageKeyValueSet
{
	GENERATED_BODY()
	/*
	 The id of this key value pair
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Id = 0;
	/*
	 The key for this set, used to access the value
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key = "";
	/*
	 The Value of this set, this is the data
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Value = "";
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
    int Id = 0;
    /*
     The name of this rental option
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
    /*
     Optional: Total duration (in seconds) that this rental item is rented for
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Duration = "";
    /*
     The price of this rental option
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Price = 0;
    /*
     Optional: A sales price of this rental option. If it is not null, then there is a sale for this item and this price should be used instead of Price
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Sales_price = "";
    /*
     Collection of links related to this rental option
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TMap<FString, FString> Links;
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
    FString Name = "";
    /*
     The short the rarity this Asset is classed as
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Short_name = "";
    /*
     The color for this rarity class
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Color = "";
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
    FString Url = "";
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
    int Created_by_player_id = 0;
    /*
     The UID of the player who created this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_by_player_uid = "";
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
    FString Material_path = "";
    /*
     Path on disk (developer configured) to this asset's binding
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Binding_path = "";
    /*
     Id of the bone this property applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Bone_id = 0;
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
    bool Can_equip = false;
    /*
     The id of the hero that this exception applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Hero_id = 0;
    /*
     The name of the hero that this exception applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Hero_name = "";
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
    int Id = 0;
    /*
     The name of this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
    /*
     The primary color of this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Primary_color = "";
    /*
     The secondary color of this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Secondary_color = "";
    /*
     List of properties configured for this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetVariationProperty> Properties;
    /*
     Collection of links related to this asset variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TMap<FString, FString> Links;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetWithoutPackageContent
{
    GENERATED_BODY()
    /*
     The id of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Id = 0;
    /*
     The uuid of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Uuid = "";
    /*
     The ulid of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Ulid = "";
    /*
     The name of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
    /*
     Whether this assset is active
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Active = false;
    /*
     The price of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Price = 0;
    /*
     Optional: A sales price of this asset. If it is not null, then there is a sale for this item and this price should be used instead of Price
    
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Sales_price = "";
    /*
     A string representation of how to display the price in the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Display_price = "";
    /*
     Path of the thumbnail to use in the shop for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Shop_thumbnail = "";
    /*
     The name of the context this asset lives within
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Context = "";
    /*
     The id of the context this asset lives within
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Context_id = 0;
    /*
     List of the character classes that this asset applies to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<int> Character_classes;
    /*
     Whether this asset is detachable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Detachable = false;
    /*
     Whether this asset is purchasable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Purchasable = false;
    /*
     Whether this asset is initially purchaseble
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Initially_purchasable = false;
    /*
     Timestamp of when this asset was last updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated = "";
    /*
     Optional: Timestamp of when this asset was marked new
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Marked_new = "";
    /*
     The default variation id to use for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Default_variation_id = 0;
    /*
     List of variations applicable to this variation
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetVariation> Variations;
    /*
     Description for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Description = "";
    /*
     Whether this asset is featured
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Featured = false;
    /*
     Whether this asset is context locked
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Context_locked = false;
    /*
     Optional: Whether this asset unlocks the context it refers to
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it has a valid value and then you can (in code) use .ToBool() or (in blueprint) use a case insensitive string comparison for "true"
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Unlocks_context = "";
    /*
     The rarity of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetRarity Rarity;
    /*
     Whether this asset is considered popular
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Popular = false;
    /*
     The popularity score of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Popularity_score = 0;
    /*
     Whether this asset is a unique instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Unique_instance = false;
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
    FString Drop_table_max_picks = "";
    /*
     Links related to this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TMap<FString, FString> Links;
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

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPackageContentItem
{
    GENERATED_BODY()
    /*
     Optional: What variation of this asset's variation
     
     This variable is optional meaning it may or may not exist, which is why it's a string. To get the value from it you should first check if it is valid (for example using .IsNumeric() and then get the value from it (for example using FCString::Atoi)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Variation_id = "";
    /*
     The quantity of this package content
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Quantity = 0;
    /*
     List of assets in this package content
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetWithoutPackageContent Asset;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAsset : public FLootLockerServerAssetWithoutPackageContent
{
    GENERATED_BODY()
    /*
     Optional: If this is a drop table asset, this contains a list of assets referred to by it
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPackageContentItem> Package_contents;
};

/** Fields to include in the simple asset response */
USTRUCT(BlueprintType)
struct FLootLockerServerSimpleAssetIncludes
{
    GENERATED_BODY()
    // If set to true, response will include storage key-value pairs.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    bool storage = false;
    // If set to true, response will include files.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    bool files = false;
    // If set to true, response will include asset data entities.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    bool data_entities = false;
    // If set to true, response will include asset metadata.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    bool metadata = false;
};

/** Fields to exclude from the simple asset response */
USTRUCT(BlueprintType)
struct FLootLockerServerSimpleAssetExcludes
{
    GENERATED_BODY()
    // If set to true, UGC assets authors will not be returned.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    bool authors = false;
};

/** Filters to apply to simple asset listing */
USTRUCT(BlueprintType)
struct FLootLockerServerSimpleAssetFilters
{
    GENERATED_BODY()
    // If true only UGC assets are returned
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    bool ugc_only = false;
    // If provided only the requested ids will be returned (max 100, server enforced). Pagination ignored.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    TArray<int> asset_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerServerSimpleAssetAuthor
{
    GENERATED_BODY()
    // The ID of the player who created the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    int player_id = 0;
    // The ULID of the player who created the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString player_ulid;
    // The public UID of the player who created the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString public_uid;
    // The active name of the player who created the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString active_name;
};

USTRUCT(BlueprintType)
struct FLootLockerServerSimpleAssetFile
{
    GENERATED_BODY()
    // The size of the file in bytes
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    int size = 0;
    // The name of the file
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString name;
    // The URL of the file
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString url;
    // The tags associated with the file
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    TArray<FString> tags;
};

USTRUCT(BlueprintType)
struct FLootLockerServerSimpleAssetDataEntity
{
    GENERATED_BODY()
    // The name of the data entity
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString name;
    // The data of the data entity
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer") 
    FString data;
};

/** Simplified asset object */
USTRUCT(BlueprintType)
struct FLootLockerServerSimpleAsset
{
    GENERATED_BODY()
    // The ID of the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    int asset_id = 0;
    // The UUID of the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString asset_uuid;
    // The ULID of the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString asset_ulid;
    // The name of the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString asset_name;
    // The context ID of the asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    int context_id = 0;
    // The name of the context the asset belongs to
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FString context_name;
    // The author of the asset if the asset is a UGC asset
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer") 
    FLootLockerServerSimpleAssetAuthor author;
    // The storage key-value pairs associated with the asset, empty if not requested
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer") 
    TArray<FLootLockerServerAssetStorageKeyValueSet> storage;
    // The files associated with the asset, empty if not requested
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer") 
    TArray<FLootLockerServerSimpleAssetFile> files;
    // The data entities associated with the asset, empty if not requested
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer") 
    TArray<FLootLockerServerSimpleAssetDataEntity> data_entities;
    // The metadata associated with the asset, empty if not requested
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer") 
    TArray<FLootLockerServerMetadataEntry> metadata;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerCreateAssetInstanceKeyValuePairRequest
{
    GENERATED_BODY()
	/*
	 The key for this set, used to access the value
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key = "";
	/*
	 The Value of this set, this is the data
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Value = "";
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerUpdateOneOrMoreKeyValuePairsOnAssetInstanceRequest
{
    GENERATED_BODY()
    /*
     List of key values to update
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetStorageKeyValueSet> Storage;
};

/** Request payload for simple asset listing */
USTRUCT(BlueprintType)
struct FLootLockerServerListAssetsRequest
{
    GENERATED_BODY()
    /*
     Configuration for what data to include in the returned assets
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FLootLockerServerSimpleAssetIncludes includes;
    /*
    Configuration for what data to exclude in the returned assets
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FLootLockerServerSimpleAssetExcludes excludes;
    /*
     Filter options for what assets to return
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FLootLockerServerSimpleAssetFilters filters;
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
    int Total = 0;
    /*
     List of assets returned for this specific request, in accordance with the supplied pagination options
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAsset> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetInstanceKeyValuePairsListResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()

    /*
     List of currently stored key value pairs for this asset instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetInstanceStorageKeyValueSet> Storage;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetInstanceKeyValuePairItemResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()

    /*
     The key value pair for this asset instance as derived from context
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetInstanceStorageKeyValueSet Storage;
};

/** Response payload for simple asset listing */
USTRUCT(BlueprintType)
struct FLootLockerServerListAssetsResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     List of assets returned for this specific request, in accordance with the supplied pagination and filtering option options
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    TArray<FLootLockerServerSimpleAsset> assets;
    /*
     Pagination information for the returned asset list
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLockerServer")
    FLootLockerServerExtendedIndexBasedPagination pagination;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for getting assets
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetAssetsResponseBP, FLootLockerServerGetAssetsResponse, Response);
/*
 Blueprint response delegate for receiving a list of asset instance key value pairs
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAssetInstanceKeyValuePairsListResponseBP, FLootLockerServerAssetInstanceKeyValuePairsListResponse, Response);
/*
 Blueprint response delegate for receiving a single asset instance key value pair
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAssetInstanceKeyValuePairItemResponseBP, FLootLockerServerAssetInstanceKeyValuePairItemResponse, Response);
/*
 Blueprint response delegate for listing simple assets
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListAssetsResponseBP, FLootLockerServerListAssetsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for getting assets
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetAssetsResponseDelegate, FLootLockerServerGetAssetsResponse);
/*
 C++ response delegate for receiving a list of asset instance key value pairs
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate, FLootLockerServerAssetInstanceKeyValuePairsListResponse);
/*
 Blueprint response delegate for receiving a single asset instance key value pair
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate, FLootLockerServerAssetInstanceKeyValuePairItemResponse);
/*
 Blueprint response delegate for listing simple assets
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListAssetsResponseDelegate, FLootLockerServerListAssetsResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerAssetRequest : public UObject
{
    GENERATED_BODY()
    public:
    ULootLockerServerAssetRequest();

    static void GetAssets(int Count, int After, int Context, bool IncludeUGC = false, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequestBP = FLootLockerServerGetAssetsResponseBP(), const FLootLockerServerGetAssetsResponseDelegate& OnCompletedRequest = FLootLockerServerGetAssetsResponseDelegate());

    static void GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP = FLootLockerServerAssetInstanceKeyValuePairsListResponseBP(), const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest = FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate());
    static void GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequestBP = FLootLockerServerAssetInstanceKeyValuePairItemResponseBP(), const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest = FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate());
    static void AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP = FLootLockerServerAssetInstanceKeyValuePairsListResponseBP(), const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest = FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate());
    static void UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP = FLootLockerServerAssetInstanceKeyValuePairsListResponseBP(), const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest = FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate());
    static void UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequestBP = FLootLockerServerAssetInstanceKeyValuePairItemResponseBP(), const FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate& OnCompletedRequest = FLootLockerServerAssetInstanceKeyValuePairItemResponseDelegate());
    static void DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequestBP = FLootLockerServerAssetInstanceKeyValuePairsListResponseBP(), const FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate& OnCompletedRequest = FLootLockerServerAssetInstanceKeyValuePairsListResponseDelegate());
    static void ListAssets(const FLootLockerServerListAssetsRequest& Request, int PerPage = 0, int Page = 0, const FLootLockerServerListAssetsResponseBP& OnCompletedRequestBP = FLootLockerServerListAssetsResponseBP(), const FLootLockerServerListAssetsResponseDelegate& OnCompletedRequest = FLootLockerServerListAssetsResponseDelegate());
};
