// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "LootLockerServerAssetRequest.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerPlayerRequest.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_rental = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString time_left;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString is_active;
};

USTRUCT(BlueprintType)
struct FLootLockerServerInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerRental rental;
};

USTRUCT(BlueprintType)
struct FLootLockerServerInventoryResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAddAssetData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_id = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_variation_id = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_rental_option_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAddAssetResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetForPlayerLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUnequipAssetForPlayerLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FInventoryResponseBP, FLootLockerServerInventoryResponse, InventoryResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAddAssetResponseBP, FLootLockerServerAddAssetResponse, AddAssetResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetPlayerLoadoutResponseBP, FLootLockerServerGetPlayerLoadoutResponse, GetPlayerLoadoutResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEquipAssetResponseBP, FLootLockerServerEquipAssetForPlayerLoadoutResponse, EquipAssetResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FUnequipAssetResponseBP, FLootLockerServerUnequipAssetForPlayerLoadoutResponse, UnequipAssetResponse);
DECLARE_DELEGATE_OneParam(FInventoryResponse, FLootLockerServerInventoryResponse);
DECLARE_DELEGATE_OneParam(FAddAssetResponse, FLootLockerServerAddAssetResponse);
DECLARE_DELEGATE_OneParam(FGetPlayerLoadoutResponse, FLootLockerServerGetPlayerLoadoutResponse);
DECLARE_DELEGATE_OneParam(FEquipAssetResponse, FLootLockerServerEquipAssetForPlayerLoadoutResponse);
DECLARE_DELEGATE_OneParam(FUnequipAssetResponse, FLootLockerServerUnequipAssetForPlayerLoadoutResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPlayerRequest : public UObject
{
	GENERATED_BODY()

public:	
	ULootLockerServerPlayerRequest();

	static void GetInventory(int PlayerId, int StartFromIndex, int ItemsCount, const FInventoryResponseBP& OnCompletedRequestBP = FInventoryResponseBP(), const FInventoryResponse& OnCompletedRequest = FInventoryResponse());

	static void AddAssetToPlayerInventory(int PlayerId, FLootLockerServerAddAssetData AddAssetData, const FAddAssetResponseBP& OnCompletedRequestBP = FAddAssetResponseBP(), const FAddAssetResponse& OnCompletedRequest = FAddAssetResponse());

	static void GetPlayerLoadout(int PlayerId, const FGetPlayerLoadoutResponseBP& OnCompletedRequestBP = FGetPlayerLoadoutResponseBP(), const FGetPlayerLoadoutResponse& OnCompletedRequest = FGetPlayerLoadoutResponse());

	static void EquipAssetForPlayerLoadout(int PlayerId, int InstanceId, const FEquipAssetResponseBP& OnCompletedRequestBP = FEquipAssetResponseBP(), const FEquipAssetResponse& OnCompletedRequest = FEquipAssetResponse());

	static void UnequipAssetForPlayerLoadout(int PlayerId, int LoadoutId, const FUnequipAssetResponseBP& OnCompletedRequestBP = FUnequipAssetResponseBP(), const FUnequipAssetResponse& OnCompletedRequest = FUnequipAssetResponse());

	static ULootLockerServerHttpClient* HttpClient;
};
