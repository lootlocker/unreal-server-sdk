// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "LootLockerServerAssetRequest.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerPlayerRequest.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerHeroesRequest.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerHero
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int hero_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString hero_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString character_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString class_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerServerHeroInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString mounted_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerRental rental;
};

USTRUCT(BlueprintType)
struct FLootLockerServerHeroInventoryResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerHeroInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerHeroesResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerHero> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetHeroLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerHeroInventory> items;
};

USTRUCT()
struct FLootLockerServerEquipHeroResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerHeroInventory> items;
	
};

USTRUCT()
struct FLootLockerServerUnequipHeroResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerHeroInventory> items;
	
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FHeroesResponseBP, FLootLockerServerGetPlayerHeroesResponse, HeroesResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FHeroInventoryResponseBP, FLootLockerServerHeroInventoryResponse, InventoryResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FHeroLoadoutResponseBP, FLootLockerServerGetHeroLoadoutResponse, LoadoutResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEquipHeroResponseBP, FLootLockerServerEquipHeroResponse, EquipResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FUnequipHeroResponseBP, FLootLockerServerUnequipHeroResponse, UnequipResponse);
DECLARE_DELEGATE_OneParam(FServerHeroesResponse, FLootLockerServerGetPlayerHeroesResponse);
DECLARE_DELEGATE_OneParam(FServerHeroInventoryResponse, FLootLockerServerHeroInventoryResponse);
DECLARE_DELEGATE_OneParam(FServerHeroLoadoutResponse, FLootLockerServerGetHeroLoadoutResponse);
DECLARE_DELEGATE_OneParam(FEquipHeroResponse, FLootLockerServerEquipHeroResponse);
DECLARE_DELEGATE_OneParam(FUnequipHeroResponse, FLootLockerServerUnequipHeroResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerHeroesRequest : public UObject
{
	GENERATED_BODY()
	public:
	ULootLockerServerHeroesRequest();

	static void GetPlayerHeroes(int PlayerId, const FHeroesResponseBP& OnCompletedRequestBP = FHeroesResponseBP(), const FServerHeroesResponse& OnCompletedRequest = FServerHeroesResponse());

	static void GetInventoryToHero(int PlayerId, int HeroId, const FHeroInventoryResponseBP& OnCompletedRequestBP = FHeroInventoryResponseBP(), const FServerHeroInventoryResponse& OnCompletedRequest = FServerHeroInventoryResponse());

	static void GetHeroLoadout(int PlayerId, int HeroId, const FHeroLoadoutResponseBP& OnCompletedRequestBP = FHeroLoadoutResponseBP(), const FServerHeroLoadoutResponse& OnCompletedRequest = FServerHeroLoadoutResponse());

	static void EquipAssetForHeroLoadout(int PlayerId, int HeroId, int InstanceId, const FEquipHeroResponseBP& OnCompletedRequestBP = FEquipHeroResponseBP(), const FEquipHeroResponse& OnCompletedRequest = FEquipHeroResponse());

	static void UnequipAssetForHeroLoadout(int PlayerId, int HeroId, int InstanceId, const FUnequipHeroResponseBP& OnCompletedRequestBP = FUnequipHeroResponseBP(), const FUnequipHeroResponse& OnCompletedRequest = FUnequipHeroResponse());

	static ULootLockerServerHttpClient* HttpClient;
	
};
