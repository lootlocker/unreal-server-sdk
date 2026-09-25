// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "ServerAPI/LootLockerServerMetadataRequest.h"

#include "LootLockerServerItemRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 The template an item instance (player inventory item) is based on
 */
USTRUCT(BlueprintType)
struct FLootLockerItemTemplate
{
    GENERATED_BODY()
    /**
     The unique identifier (ULID) of this item template
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     The name of this item template
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     The id of the game this item template belongs to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Game_id = 0;
    /**
     The limited quantity of this item template (if any)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Limited = 0;
    /**
     The type of this item template (instanced or stackable)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Item_type;
    /**
     Whether this item template is consumable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Consumable = false;
    /**
     Whether this item template is deletable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Deletable = false;
    /**
     The time this item template was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    /**
     The time this item template was last updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at;
};

/**
 A single item instance in a player's inventory (Assets 2.0)

 Note: The backend list endpoint returns the raw inventory rows, which currently
 marshal in PascalCase (the backend Inventory struct is missing JSON tags),
 whereas the get-item endpoint returns snake_case. The DTO below mirrors the
 snake_case shape used by get-item, and ListPlayerItems normalizes the
 PascalCase keys so both endpoints deserialize correctly. Once the backend adds
 JSON tags the normalization becomes a no-op.
 */
USTRUCT(BlueprintType)
struct FLootLockerServerItem
{
    GENERATED_BODY()
    /**
     The unique identifier (ULID) of this inventory item instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     The id of the player that owns this inventory item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Player_id = 0;
    /**
     The unique identifier (ULID) of the item template this item is based on
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Item_template_id;
    /**
     The type of this item (instanced or stackable)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Item_type;
    /**
     Whether this item is consumable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Consumable = false;
    /**
     The count of this item in the stack
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Count = 0;
    /**
     The source that granted this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Source;
    /**
     The time this item instance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    /**
     The time this item instance was last updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at;
    /**
     Free-form metadata attached to this item instance.

     Note: The get-item endpoint returns metadata as an array of entries matching
     FLootLockerServerMetadataEntry. The list endpoint returns raw inventory rows
     (see note on FLootLockerServerItem).
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerMetadataEntry> Metadata;
};

//==================================================
// Response Type Definitions
//==================================================

/**
 Response for listing a player's items (Assets 2.0)
 */
USTRUCT(BlueprintType)
struct FLootLockerServerListPlayerItemsResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     The items in the player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerItem> Items;
    /**
     Pagination information for this listing (extended offset pagination)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerExtendedIndexBasedPagination Pagination;
};

/**
 Response for getting a single player item (Assets 2.0)
 Note: The backend returns the item fields at the top level of the response
 object (not wrapped in an "item" key).
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerItemResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     The unique identifier (ULID) of this inventory item instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     The id of the player that owns this inventory item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Player_id = 0;
    /**
     The unique identifier (ULID) of the item template this item is based on
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Item_template_id;
    /**
     The type of this item (instanced or stackable)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Item_type;
    /**
     Whether this item is consumable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Consumable = false;
    /**
     The count of this item in the stack
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Count = 0;
    /**
     The source that granted this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Source;
    /**
     The time this item instance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    /**
     The time this item instance was last updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at;
    /**
     Free-form metadata attached to this item instance.
     Note: The server returns this as an array of metadata entries, matching the
     existing SDK convention (FLootLockerServerMetadataEntry).
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerMetadataEntry> Metadata;
    /**
     The full item template this item is based on
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerItemTemplate Template;
};

/**
 Response for deleting a player item (Assets 2.0)
 */
USTRUCT(BlueprintType)
struct FLootLockerServerDeletePlayerItemResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
};

/**
 A single result produced by a grant behaviour (e.g. "also grant this currency").
 Matches the backend GrantResult shape.
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGrantedItem
{
    GENERATED_BODY()
    /**
     The source id of the granted result (ULID)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Source_id;
    /**
     The number of this result granted
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Count = 0;
    /**
     The type of the granted result ("item_template", "currency", or "publisher_currency")
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Type;
    /**
     The name of the granted result (when provided)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /**
     The code of the granted result (when provided)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Code;
};

/**
 Response for granting an item to a player (Assets 2.0)
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGrantItemResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     The unique identifier (ULID) of the newly granted inventory item instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /**
     Results produced by any behaviours that fired as part of the grant (optional)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerGrantedItem> Behaviour_results;
};

/**
 Response for splitting a player item stack (Assets 2.0)
 */
USTRUCT(BlueprintType)
struct FLootLockerServerSplitPlayerItemStackResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     The unique identifier (ULID) of the newly split inventory item instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
};

/**
 Response for merging player item stacks (Assets 2.0)
 Note: This endpoint returns 204 No Content.
 */
USTRUCT(BlueprintType)
struct FLootLockerServerMergePlayerItemStacksResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
};

//==================================================
// Request Type Definitions
//==================================================

/**
 Request body for granting an item to a player (Assets 2.0)
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGrantItemRequest
{
    GENERATED_BODY()
    /**
     The unique identifier (ULID) of the item template to grant (required)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Item_template_id;
    /**
     The number of items to grant (defaults to 1)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Count = 1;
    /**
     The source of this grant (optional)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Source;
};

/**
 Request body for splitting a player item stack (Assets 2.0)
 */
USTRUCT(BlueprintType)
struct FLootLockerServerSplitItemRequest
{
    GENERATED_BODY()
    /**
     The number of items to move into the new stack
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Count = 0;
};

/**
 Request body for merging player item stacks (Assets 2.0)
 */
USTRUCT(BlueprintType)
struct FLootLockerServerMergeItemsRequest
{
    GENERATED_BODY()
    /**
     The unique identifier (ULID) of the source inventory item instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Source_inventory_id;
    /**
     The unique identifier (ULID) of the target inventory item instance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Target_inventory_id;
};

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for listing a player's items
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListPlayerItemsResponseDelegate, FLootLockerServerListPlayerItemsResponse);
/*
 C++ response delegate for getting a player item
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPlayerItemResponseDelegate, FLootLockerServerGetPlayerItemResponse);
/*
 C++ response delegate for deleting a player item
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDeletePlayerItemResponseDelegate, FLootLockerServerDeletePlayerItemResponse);
/*
 C++ response delegate for granting an item to a player
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGrantItemResponseDelegate, FLootLockerServerGrantItemResponse);
/*
 C++ response delegate for splitting a player item stack
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSplitPlayerItemStackResponseDelegate, FLootLockerServerSplitPlayerItemStackResponse);
/*
 C++ response delegate for merging player item stacks
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerMergePlayerItemStacksResponseDelegate, FLootLockerServerMergePlayerItemStacksResponse);

/**
 Handler for the Items & Item Templates (Assets 2.0) server endpoints
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerItemRequestHandler : public UObject
{
    GENERATED_BODY()
    public:
    ULootLockerServerItemRequestHandler();

    static FString ListPlayerItems(int PlayerID, int Page, int PerPage, const FLootLockerServerListPlayerItemsResponseDelegate& OnCompletedRequest);
    static FString GetPlayerItem(int PlayerID, const FString& InventoryId, const FLootLockerServerGetPlayerItemResponseDelegate& OnCompletedRequest);
    static FString DeletePlayerItem(int PlayerID, const FString& InventoryId, const FLootLockerServerDeletePlayerItemResponseDelegate& OnCompletedRequest);
    static FString GrantItemToPlayer(int PlayerID, const FLootLockerServerGrantItemRequest& Request, const FLootLockerServerGrantItemResponseDelegate& OnCompletedRequest);
    static FString SplitPlayerItemStack(int PlayerID, const FString& InventoryId, const FLootLockerServerSplitItemRequest& Request, const FLootLockerServerSplitPlayerItemStackResponseDelegate& OnCompletedRequest);
    static FString MergePlayerItemStacks(int PlayerID, const FLootLockerServerMergeItemsRequest& Request, const FLootLockerServerMergePlayerItemStacksResponseDelegate& OnCompletedRequest);
};