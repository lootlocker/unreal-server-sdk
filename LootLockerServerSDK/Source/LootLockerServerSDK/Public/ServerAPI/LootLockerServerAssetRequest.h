// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LootLockerServerHttpClient.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerAssetRequest.generated.h"

UENUM(BlueprintType)
enum class ELootLockerServerAssetFilter : uint8
{
	None = 0,
    Purchasable = 1,
    NonPurchasable = 2,
    Rentable = 3,
    NonRentable = 4,
    Popular = 5,
    UnPopular = 6
};

//TODO: implement default loadouts
// USTRUCT(BlueprintType)
// struct FLootLockerServerDefaultLoadouts {
// 	GENERATED_BODY()
// 	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
// 	bool Light_Vehicle;
// 	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
// 	bool Heavy_Vehicle;
// };

USTRUCT(BlueprintType)
struct FLootLockerServerLinks {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString thumbnail;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPersistentStorageItem {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString value;
};

USTRUCT(BlueprintType)
struct FLootLockerServerRarity {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString short_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString color;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPsn {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString entitlement_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 service_label;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAppStore
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString product_id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGooglePay
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString product_id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerExternalIdentifiers {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerPsn psn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerAppStore apple_app_store;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerAppStore google_play;
};

USTRUCT(BlueprintType)
struct FLootLockerServerRentalOption {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString sales_price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerLinks links;
};

USTRUCT(BlueprintType)
struct FLootLockerServerFile {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FString> tags;
};

USTRUCT(BlueprintType)
struct FLootLockerServerFilter {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString value;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAssetCandidate
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int created_by_player_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_by_player_uid;
};

USTRUCT(BlueprintType)
struct FLootLockerServerVariation
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString primary_color;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString secondary_color;
	//TODO: implement properties
	//  TArray<FProperty> properties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerLinks links;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAsset
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool active;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool purchasable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString sales_price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString display_price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString context;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString unlocks_context;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool detachable;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString updated;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString marked_new;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 default_variation_id;
	//TODO: implement default loadouts
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	// FLootLockerServerDefaultLoadouts default_loadouts;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerLinks links;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPersistentStorageItem> storage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerRarity rarity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool popular;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 popularity_score;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool unique_instance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerExternalIdentifiers external_identifiers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerRentalOption> rental_options;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerFilter> filters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerFile> files;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FString> data_entities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerAssetCandidate asset_candidate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerVariation> variations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool featured;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool context_locked;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool initially_purchasable;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetAssetsToGameResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerAsset> items;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 total;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FServerAssetsResponseDelegateBP, FLootLockerServerGetAssetsToGameResponse, AssetsResponse);

DECLARE_DELEGATE_OneParam(FServerAssetsResponseDelegate, FLootLockerServerGetAssetsToGameResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerAssetRequest : public UObject
{
	GENERATED_BODY()

	public:

	ULootLockerServerAssetRequest();

	static void GetAssetsToGame(int StartFromIndex, int ItemsCount, ELootLockerServerAssetFilter AssetFilter, bool IncludeUGC, const FServerAssetsResponseDelegateBP& OnCompletedRequestBP = FServerAssetsResponseDelegateBP(), const FServerAssetsResponseDelegate& OnCompletedRequest = FServerAssetsResponseDelegate());

	static ULootLockerServerHttpClient* HttpClient;
};
