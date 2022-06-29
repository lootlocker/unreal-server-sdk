// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerPlayerRequest.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerCharacterRequest.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerCharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int Id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool Default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Name;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCharacterInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
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
struct FLootLockerServerCharacterInventoryResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 total = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerCharacterInventory> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerCharactersResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerCharacter> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetCharacterLoadoutResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerCharacterInventory> items;
};

USTRUCT()
struct FLootLockerServerEquipCharacterResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerCharacterInventory> items;
	
};

USTRUCT()
struct FLootLockerServerUnequipCharacterResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerCharacterInventory> items;
	
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FCharactersResponseBP, FLootLockerServerGetPlayerCharactersResponse, CharactersResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FCharacterInventoryResponseBP, FLootLockerServerCharacterInventoryResponse, InventoryResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FCharacterLoadoutResponseBP, FLootLockerServerGetCharacterLoadoutResponse, LoadoutResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEquipResponseBP, FLootLockerServerEquipCharacterResponse, EquipResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FUnequipResponseBP, FLootLockerServerUnequipCharacterResponse, UnequipResponse);
DECLARE_DELEGATE_OneParam(FCharactersResponse, FLootLockerServerGetPlayerCharactersResponse);
DECLARE_DELEGATE_OneParam(FServerCharacterInventoryResponse, FLootLockerServerCharacterInventoryResponse);
DECLARE_DELEGATE_OneParam(FServerCharacterLoadoutResponse, FLootLockerServerGetCharacterLoadoutResponse);
DECLARE_DELEGATE_OneParam(FEquipResponse, FLootLockerServerEquipCharacterResponse);
DECLARE_DELEGATE_OneParam(FUnequipResponse, FLootLockerServerUnequipCharacterResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerCharacterRequest : public UObject
{
	GENERATED_BODY()
	public:
	ULootLockerServerCharacterRequest();

	static void GetPlayerCharacters(int PlayerId, const FCharactersResponseBP& OnCompletedRequestBP = FCharactersResponseBP(), const FCharactersResponse& OnCompletedRequest = FCharactersResponse());

	static void GetInventoryToCharacter(int PlayerId, int CharacterId, const FCharacterInventoryResponseBP& OnCompletedRequestBP = FCharacterInventoryResponseBP(), const FServerCharacterInventoryResponse& OnCompletedRequest = FServerCharacterInventoryResponse());

	static void GetCharacterLoadout(int PlayerId, int CharacterId, const FCharacterLoadoutResponseBP& OnCompletedRequestBP = FCharacterLoadoutResponseBP(), const FServerCharacterLoadoutResponse& OnCompletedRequest = FServerCharacterLoadoutResponse());

	static void EquipAssetForCharacterLoadout(int PlayerId, int CharacterId, int InstanceId, const FEquipResponseBP& OnCompletedRequestBP = FEquipResponseBP(), const FEquipResponse& OnCompletedRequest = FEquipResponse());

	static void UnequipAssetForCharacterLoadout(int PlayerId, int CharacterId, int InstanceId, const FUnequipResponseBP& OnCompletedRequestBP = FUnequipResponseBP(), const FUnequipResponse& OnCompletedRequest = FUnequipResponse());

	static ULootLockerServerHttpClient* HttpClient;
};
