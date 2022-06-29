// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LootLockerServerHttpClient.h"

#include "LootLockerServerStorageRequest.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerStorageItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString value;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_public = false;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerStorageItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int player_id = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPlayerStorageItemData> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetPersistentStorageResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPlayerStorageItem> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerKeyValueSet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString value;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_public = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int order = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerStorageData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int player_id = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerKeyValueSet> sets;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPersistentStorageRequestData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPlayerStorageData> payload;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdatePersistentStorageResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPlayerStorageItem> items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FGetPersistentStorageResponseBP, FLootLockerServerGetPersistentStorageResponse, GetPersistentStorageResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FUpdatePersistentStorageResponseBP, FLootLockerServerUpdatePersistentStorageResponse, UpdatePersistentStorageResponse);
DECLARE_DELEGATE_OneParam(FGetPersistentStorageResponse, FLootLockerServerGetPersistentStorageResponse);
DECLARE_DELEGATE_OneParam(FUpdatePersistentStorageResponse, FLootLockerServerUpdatePersistentStorageResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerStorageRequest : public UObject
{
	GENERATED_BODY()

	public:	
	ULootLockerServerStorageRequest();

	static void GetPersistentStorage(TArray<int> PlayerIds, const FGetPersistentStorageResponseBP& OnCompletedRequestBP = FGetPersistentStorageResponseBP(), const FGetPersistentStorageResponse& OnCompletedRequest = FGetPersistentStorageResponse());
	static void UpdatePersistentStorage(FLootLockerServerPersistentStorageRequestData requestData, const FUpdatePersistentStorageResponseBP& OnCompletedRequestBP = FUpdatePersistentStorageResponseBP(), const FUpdatePersistentStorageResponse& OnCompletedRequest = FUpdatePersistentStorageResponse());

	static ULootLockerServerHttpClient* HttpClient;	
};
