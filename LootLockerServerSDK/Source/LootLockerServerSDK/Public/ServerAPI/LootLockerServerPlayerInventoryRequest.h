// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "LootLockerServerPlayerInventoryRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerItemRentalData
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
struct FLootLockerServerUniversalInventoryItem
{
    GENERATED_BODY()
    /*
     The universal id of this item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Universal_id = 0;
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
    FLootLockerServerPlayerItemRentalData Rental;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerInventoryItem
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
    FLootLockerServerPlayerItemRentalData Rental;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerLoadoutItem
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
    FLootLockerServerPlayerItemRentalData Rental;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetByInstanceIDRequest
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
struct FLootLockerServerAssetByAssetIdRequest
{
    GENERATED_BODY()
    /*
     The id of the asset to equip, the default variation if any will be used
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Asset_id = 0;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAssetByAssetInstanceIdRequest
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
struct FLootLockerServerAssetByAssetIdAndVariationIdRequest
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
struct FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest
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

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAlterPlayerInventoryRequestBase
{
    GENERATED_BODY()
        FLootLockerServerAlterPlayerInventoryRequestBase(const TArray<int>& InRemove)
        : Remove(InRemove)
    {
    }
    FLootLockerServerAlterPlayerInventoryRequestBase()
    {
	}
    /*
     The ids of assets to remove from the specified player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<int> Remove;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAlterPlayerInventoryByAssetIdRequest : public FLootLockerServerAlterPlayerInventoryRequestBase
{
    GENERATED_BODY()
        FLootLockerServerAlterPlayerInventoryByAssetIdRequest(const TArray<int>& InRemove, const TArray<FLootLockerServerAssetByAssetIdRequest>& InAdd)
        : FLootLockerServerAlterPlayerInventoryRequestBase(InRemove)
        , Add(InAdd)
    {
    }

    FLootLockerServerAlterPlayerInventoryByAssetIdRequest()
	{}
    /*
     List of the assets to add to the specified player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetByAssetIdRequest> Add;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAlterPlayerInventoryByAssetIdAndAssetVariationIdRequest : public FLootLockerServerAlterPlayerInventoryRequestBase
{
    GENERATED_BODY()
        FLootLockerServerAlterPlayerInventoryByAssetIdAndAssetVariationIdRequest(const TArray<int>& InRemove, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& InAdd)
        : FLootLockerServerAlterPlayerInventoryRequestBase(InRemove)
        , Add(InAdd)
    {
    }

    FLootLockerServerAlterPlayerInventoryByAssetIdAndAssetVariationIdRequest()
    {
    }

    /*
     List of the assets to add to the specified player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest> Add;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAlterPlayerInventoryByAssetIdAndRentalOptionIdRequest : public FLootLockerServerAlterPlayerInventoryRequestBase
{
    GENERATED_BODY()
        FLootLockerServerAlterPlayerInventoryByAssetIdAndRentalOptionIdRequest(const TArray<int>& InRemove, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& InAdd)
        : FLootLockerServerAlterPlayerInventoryRequestBase(InRemove)
        , Add(InAdd)
    {
    }

    FLootLockerServerAlterPlayerInventoryByAssetIdAndRentalOptionIdRequest()
    {
	}
    /*
     List of the assets to add to the specified player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest> Add;
};

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetUniversalInventoryResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     List of items in this game's universal inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerUniversalInventoryItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerInventoryResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    
    /*
     The total number of items in this player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Total = 0;
    /*
     List of items in this player's inventory according to the requested pagination
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerInventoryItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAddAssetToPlayerInventoryResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     List of the assets granted to the specified player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerLoadoutItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerFullPlayerLoadoutResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()

    /*
     List of the specified player's loadout
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerPlayerLoadoutItem> Items;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerLoadoutResponse : public FLootLockerServerFullPlayerLoadoutResponse
{
    GENERATED_BODY()
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetToPlayerLoadoutResponse : public FLootLockerServerFullPlayerLoadoutResponse
{
    GENERATED_BODY()
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerUnequipAssetFromPlayerLoadoutResponse : public FLootLockerServerFullPlayerLoadoutResponse
{
    GENERATED_BODY()
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerAlterPlayerInventoryResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()

    /*
     List of asset instances added to the specified player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerAsset> Added;
    /*
     List of asset instance ids removed from the specified player's inventory
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<int> Removed;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for getting a game's universal inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetUniversalInventoryResponseBP, FLootLockerServerGetUniversalInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player's inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerInventoryResponseBP, FLootLockerServerGetPlayerInventoryResponse, Response);
/*
 Blueprint response delegate for adding an asset to a player's inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAddAssetToPlayerInventoryResponseBP, FLootLockerServerAddAssetToPlayerInventoryResponse, Response);
/*
 Blueprint response delegate for altering a player's inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAlterPlayerInventoryResponseBP, FLootLockerServerAlterPlayerInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player's loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerLoadoutResponseBP, FLootLockerServerGetPlayerLoadoutResponse, Response);
/*
 Blueprint response delegate for equipping an asset to a player's loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerEquipAssetToPlayerLoadoutResponseBP, FLootLockerServerEquipAssetToPlayerLoadoutResponse, Response);
/*
 Blueprint response delegate for unequipping an asset from a player's loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP, FLootLockerServerUnequipAssetFromPlayerLoadoutResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for getting a game's universal inventory
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetUniversalInventoryResponseDelegate, FLootLockerServerGetUniversalInventoryResponse);
/*
 C++ response delegate for getting a player's inventory
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPlayerInventoryResponseDelegate, FLootLockerServerGetPlayerInventoryResponse);
/*
 C++ response delegate for adding an asset to a player's inventory
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerAddAssetToPlayerInventoryResponseDelegate, FLootLockerServerAddAssetToPlayerInventoryResponse);
/*
 C++ response delegate for altering a player's inventory
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerAlterPlayerInventoryResponseDelegate, FLootLockerServerAlterPlayerInventoryResponse);
/*
 C++ response delegate for getting a player's loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPlayerLoadoutResponseDelegate, FLootLockerServerGetPlayerLoadoutResponse);
/*
 C++ response delegate for equipping an asset to a player's loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate, FLootLockerServerEquipAssetToPlayerLoadoutResponse);
/*
 C++ response delegate for unequipping an asset from a player's loadout
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate, FLootLockerServerUnequipAssetFromPlayerLoadoutResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPlayerInventoryRequest : public UObject
{
    GENERATED_BODY()
    public:
    ULootLockerServerPlayerInventoryRequest();

    static void GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerGetUniversalInventoryResponseBP(), const FLootLockerServerGetUniversalInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerGetUniversalInventoryResponseDelegate());
    static void GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerGetPlayerInventoryResponseBP(), const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerGetPlayerInventoryResponseDelegate());
    static void GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerGetPlayerInventoryResponseBP(), const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerGetPlayerInventoryResponseDelegate());
    static void GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerGetPlayerLoadoutResponseBP(), const FLootLockerServerGetPlayerLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerGetPlayerLoadoutResponseDelegate());
    static void EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate());
    static void EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate());
    static void EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate());
    static void EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate());
    static void UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP& OnCompletedRequestBP = FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP(), const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate& OnCompletedRequest = FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate());
    static void AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerAddAssetToPlayerInventoryResponseBP(), const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerAddAssetToPlayerInventoryResponseDelegate());
    static void AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerAddAssetToPlayerInventoryResponseBP(), const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerAddAssetToPlayerInventoryResponseDelegate());
    static void AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerAddAssetToPlayerInventoryResponseBP(), const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerAddAssetToPlayerInventoryResponseDelegate());
    static void AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerAlterPlayerInventoryResponseBP(), const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerAlterPlayerInventoryResponseDelegate());
    static void AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerAlterPlayerInventoryResponseBP(), const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerAlterPlayerInventoryResponseDelegate());
    static void AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequestBP = FLootLockerServerAlterPlayerInventoryResponseBP(), const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest = FLootLockerServerAlterPlayerInventoryResponseDelegate());
};
