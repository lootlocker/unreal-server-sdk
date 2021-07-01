// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"


#include "DemoPlayerInventory.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoPlayerInventory : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int StartFromIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ItemsCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int AssetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int AssetRentalOptionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int AssetVariationId;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetPlayerInventory();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
	void DemoAddAssetToPlayerInventory();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
	void DemoGetPlayerLoadout();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
	void DemoEquipAssetForPlayerLoadout();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoUnEquipAssetForPlayerLoadout();
    
	void OnGetPlayerInventoryCompleted(FLootLockerServerInventoryResponse Response);

	void OnAddAssetToPlayerInventoryCompleted(FLootLockerServerAddAssetResponse Response);
	
	void OnGetPlayerLoadoutCompleted(FLootLockerServerGetPlayerLoadoutResponse Response);

	void OnEquipAssetForPlayerLoadoutCompleted(FLootLockerServerEquipAssetForPlayerLoadoutResponse Response);

	void OnUnequipAssetForPlayerLoadoutCompleted(FLootLockerServerUnequipAssetForPlayerLoadoutResponse Response);
};
