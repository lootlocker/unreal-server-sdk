// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerCatalogRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Possible entity kinds that catalog entries can have
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerCatalogEntryEntityKind : uint8
{
    Asset = 0,
    Currency = 1,
    Progression_Points = 2,
    Progression_Reset = 3,
    Group = 4,
};

/**
 * Represents a catalog with its name, unique key, identifier, and creation timestamp.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalog
{
    GENERATED_BODY()
    /**
     * The time when this catalog was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    /**
     * The name of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     * The unique identifying key of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    /**
     * The id of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The time when this catalog was deleted, should normally be empty
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Deleted_at;
};

/**
 * Represents a price for a catalog entry in a specific currency, including the numeric amount,
 * display-friendly string, and unique price identifier.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogEntryPrice
{
    GENERATED_BODY()
    /**
     * The amount (cost) set for this price
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Amount = 0;
    /**
     * A prettified version of the amount to use for display
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Display_amount;
    /**
     * The short code for the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Currency_code;
    /**
     * The name of the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Currency_name;
    /**
     * The unique id of this price
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Price_id;
    /**
     * The unique id of the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Currency_id;
};

/**
 * Holds the Apple App Store product identifier for a catalog entry.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogAppleAppStoreListing
{
    GENERATED_BODY()
    /**
     * The id of the product in Apple App Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Product_id;
};

/**
 * Holds the Google Play Store product identifier for a catalog entry.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogGooglePlayStoreListing
{
    GENERATED_BODY()
    /**
     * The id of the product in Google Play Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Product_id;
};

/**
 * Represents a single price point for a Steam Store listing.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogSteamStoreListingPrice
{
    GENERATED_BODY()
    /**
     * Currency code of the currency to be used for purchasing this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Currency;
    /**
     * Amount of the base value of the specified currency that this listing costs to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Amount = 0;
};

/**
 * Holds the Steam Store listing for a catalog entry.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogSteamStoreListing
{
    GENERATED_BODY()
    /**
     * Description of this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Description;
    /**
     * List of prices for this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogSteamStoreListingPrice> Prices;
};

/**
 * Holds the Stripe payment details for a catalog entry.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogStripeStoreListing
{
    GENERATED_BODY()
    /**
     * The currency to use for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Currency;
    /**
     * The amount to charge in the smallest unit of the currency (e.g. cents for USD)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Amount = 0;
};

/**
 * Holds the Epic Games Store audience item identifier associated with a catalog entry listing.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogEpicGamesStoreListing
{
    GENERATED_BODY()
    /**
     * The Epic Games audience item id associated with this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Audience_item_id;
};

/**
 * Holds the PlayStation Store entitlement label associated with a catalog entry listing.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogPlaystationStoreListing
{
    GENERATED_BODY()
    /**
     * The Playstation entitlement label associated with this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Entitlement_label;
};

/**
 * Aggregates the platform-specific store listing information configured for a catalog entry.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogEntryListings
{
    GENERATED_BODY()
    /**
     * The listing information (if configured) for Apple App Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogAppleAppStoreListing Apple_app_store;
    /**
     * The listing information (if configured) for Google Play Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogGooglePlayStoreListing Google_play_store;
    /**
     * The listing information (if configured) for Steam Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogSteamStoreListing Steam_store;
    /**
     * The listing information (if configured) for Stripe
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogStripeStoreListing Stripe_store;
    /**
     * The listing information (if configured) for Epic Games Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogEpicGamesStoreListing Epic_games_store;
    /**
     * The listing information (if configured) for PlayStation Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogPlaystationStoreListing Playstation_store;
};

/**
 * Represents a single item in a catalog, including its entity type, prices, store listings,
 * purchasability flag, non-refundable flag, and unique catalog listing identifier.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogEntry
{
    GENERATED_BODY()
    /**
     * The time when this catalog entry was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    /**
     * The kind of entity that this entry is. This signifies in which lookup structure to find
     * the details of this entry by using the Catalog_listing_id.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerCatalogEntryEntityKind Entity_kind = ELootLockerServerCatalogEntryEntityKind::Asset;
    /**
     * All the listings configured for this catalog entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogEntryListings Listings;
    /**
     * The name of this entity
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Entity_name;
    /**
     * A list of prices for this catalog entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogEntryPrice> Prices;
    /**
     * The unique id of the entity that this entry refers to.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Entity_id;
    /**
     * A unique listing id for this entry in this catalog, grouping the entity and the prices.
     * This is the key you use to look up details about the entity in the structure signified by Entity_kind.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Catalog_listing_id;
    /**
     * Whether this entry is currently purchasable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Purchasable = false;
    /**
     * Whether this entry is refundable. If false, purchases of this entry cannot be refunded.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Non_refundable = false;
};

/**
 * Holds detail information about an asset catalog entity, including its name, ULID, legacy
 * numeric id, thumbnail, and optional variation or rental option identifiers.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogAssetDetails
{
    GENERATED_BODY()
    /**
     * The name of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     * The id of the specific variation of this asset that this refers to.
     * Asset Variations is a deprecated feature, this is added for backward compatibility only.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Variation_id;
    /**
     * The id of the specific rental option of this asset that this refers to.
     * Asset Rental Options is a deprecated feature, this is added for backward compatibility only.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Rental_option_id;
    /**
     * The legacy numeric id of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Legacy_id = 0;
    /**
     * The unique identifying ulid of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The thumbnail for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Thumbnail;
    /**
     * The catalog listing id for this asset detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Catalog_listing_id;
};

/**
 * Holds details about a progression-points catalog entity.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogProgressionPointDetails
{
    GENERATED_BODY()
    /**
     * The unique key of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    /**
     * The name of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     * The amount of points to be added to the progression in question
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Amount = 0;
    /**
     * The unique id of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The catalog listing id for this progression point detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Catalog_listing_id;
};

/**
 * Holds details about a progression-reset catalog entity.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogProgressionResetDetails
{
    GENERATED_BODY()
    /**
     * The unique key of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    /**
     * The name of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     * The unique id of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The catalog listing id for this progression reset detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Catalog_listing_id;
};

/**
 * Holds details about a currency catalog entity.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogCurrencyDetails
{
    GENERATED_BODY()
    /**
     * The name of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     * The unique short code of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Code;
    /**
     * The amount of this currency to be awarded
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Amount;
    /**
     * The unique id of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The catalog listing id for this currency detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Catalog_listing_id;
};

/**
 * Holds details about a catalog group entity.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogGroupDetails
{
    GENERATED_BODY()
    /**
     * The name of the Group
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     * The description of the Group
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Description;
    /**
     * The unique id of the Group
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     * The catalog listing id for this group detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Catalog_listing_id;
};

/**
 * Cursor-based pagination information for a catalog listing response.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerCatalogPagination
{
    GENERATED_BODY()
    /**
     * The total number of items in the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int64 Total = 0;
    /**
     * The cursor to use to get the next page of results. Empty string means there are no more pages.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Next_cursor;
};

//==================================================
// Request Definitions
//==================================================

// N/A

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing catalog entries with entity-typed detail arrays and cursor-based pagination.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerListCatalogPricesResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * Information about the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalog Catalog;
    /**
     * The catalog entries (items with prices)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogEntry> Entries;
    /**
     * Details for catalog entries with entity_kind == Asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogAssetDetails> Assets_details;
    /**
     * Details for catalog entries with entity_kind == Progression_Points
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogProgressionPointDetails> Progression_points_details;
    /**
     * Details for catalog entries with entity_kind == Progression_Reset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogProgressionResetDetails> Progression_resets_details;
    /**
     * Details for catalog entries with entity_kind == Currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogCurrencyDetails> Currency_details;
    /**
     * Details for catalog entries with entity_kind == Group
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerCatalogGroupDetails> Group_details;
    /**
     * Pagination information — use Next_cursor to fetch subsequent pages
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCatalogPagination Pagination;
};

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for listing catalog prices
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListCatalogPricesResponseDelegate, FLootLockerServerListCatalogPricesResponse);

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerCatalogRequest : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerCatalogRequest();

    /**
     * List catalog items (entries with prices) for the catalog identified by the given key.
     *
     * Use Count and After for cursor-based pagination. Pass After = "" and Count = 0 to get the
     * first page with the default page size.
     *
     * @param CatalogKey The unique key of the catalog to list items for
     * @param Count Optional: number of items to return per page (0 = server default)
     * @param After Optional: cursor from a previous response's Pagination.Next_cursor to get the next page
     * @param OnResponseCompleted Delegate for handling the response
     */
    static FString ListCatalogItemsByKey(const FString& CatalogKey, int Count, const FString& After, const FLootLockerServerListCatalogPricesResponseDelegate& OnResponseCompleted);
};
