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
	bool is_rental;
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
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id;
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
	int32 total;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAddAssetData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_variation_id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_rental_option_id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAddAssetResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFile {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 size;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString expires_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at;
};

USTRUCT(BlueprintType)
struct FLootLockerServerListFilesForPlayerResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPlayerFile> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetFileByIdForPlayerResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerPlayerFile item;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAlterInventoryRequestData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerAddAssetData> add;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<int> remove;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAlterInventoryResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> added;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<int> removed;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerEquipAssetForPlayerLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUnequipAssetForPlayerLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerInventory> items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FInventoryResponseBP, FLootLockerServerInventoryResponse, InventoryResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAddAssetResponseBP, FLootLockerServerAddAssetResponse, AddAssetResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAlterInventoryResponseBP, FLootLockerServerAlterInventoryResponse, AlterInventoryResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetPlayerLoadoutResponseBP, FLootLockerServerGetPlayerLoadoutResponse, GetPlayerLoadoutResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FListFilesForPlayerResponseBP, FLootLockerServerListFilesForPlayerResponse, ListFilesForPlayerResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetFileByIdForPlayerResponseBP, FLootLockerServerGetFileByIdForPlayerResponse, GetFileByIdForPlayerResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEquipAssetResponseBP, FLootLockerServerEquipAssetForPlayerLoadoutResponse, EquipAssetResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FUnequipAssetResponseBP, FLootLockerServerUnequipAssetForPlayerLoadoutResponse, UnequipAssetResponse);
DECLARE_DELEGATE_OneParam(FServerInventoryResponse, FLootLockerServerInventoryResponse);
DECLARE_DELEGATE_OneParam(FAddAssetResponse, FLootLockerServerAddAssetResponse);
DECLARE_DELEGATE_OneParam(FListFilesForPlayerResponse, FLootLockerServerListFilesForPlayerResponse);
DECLARE_DELEGATE_OneParam(FGetFileByIdForPlayerResponse, FLootLockerServerGetFileByIdForPlayerResponse);
DECLARE_DELEGATE_OneParam(FAlterInventoryResponse, FLootLockerServerAlterInventoryResponse);
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

	static void GetInventory(int PlayerId, int StartFromIndex, int ItemsCount, const FInventoryResponseBP& OnCompletedRequestBP = FInventoryResponseBP(), const FServerInventoryResponse& OnCompletedRequest = FServerInventoryResponse());

	static void AddAssetToPlayerInventory(int PlayerId, FLootLockerServerAddAssetData AddAssetData, const FAddAssetResponseBP& OnCompletedRequestBP = FAddAssetResponseBP(), const FAddAssetResponse& OnCompletedRequest = FAddAssetResponse());

	static void ListFilesForPlayer(int PlayerId, const FListFilesForPlayerResponseBP& OnCompletedRequestBP = FListFilesForPlayerResponseBP(), const FListFilesForPlayerResponse& OnCompletedRequest = FListFilesForPlayerResponse());

	static void GetFileByIdForPlayer(int PlayerId, int FileId, const FGetFileByIdForPlayerResponseBP& OnCompletedRequestBP = FGetFileByIdForPlayerResponseBP(), const FGetFileByIdForPlayerResponse& OnCompletedRequest = FGetFileByIdForPlayerResponse());

	static void AlterPlayerInventory(int PlayerId, const FLootLockerServerAlterInventoryRequestData& RequestData, const FAlterInventoryResponseBP& OnCompletedRequestBP = FAlterInventoryResponseBP(), const FAlterInventoryResponse& OnCompletedRequest = FAlterInventoryResponse());
	
	static void GetPlayerLoadout(int PlayerId, const FGetPlayerLoadoutResponseBP& OnCompletedRequestBP = FGetPlayerLoadoutResponseBP(), const FGetPlayerLoadoutResponse& OnCompletedRequest = FGetPlayerLoadoutResponse());

	static void EquipAssetForPlayerLoadout(int PlayerId, int InstanceId, const FEquipAssetResponseBP& OnCompletedRequestBP = FEquipAssetResponseBP(), const FEquipAssetResponse& OnCompletedRequest = FEquipAssetResponse());

	static void UnequipAssetForPlayerLoadout(int PlayerId, int LoadoutId, const FUnequipAssetResponseBP& OnCompletedRequestBP = FUnequipAssetResponseBP(), const FUnequipAssetResponse& OnCompletedRequest = FUnequipAssetResponse());

	static ULootLockerServerHttpClient* HttpClient;
};
