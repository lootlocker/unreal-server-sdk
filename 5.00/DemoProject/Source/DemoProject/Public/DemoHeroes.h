// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerAPI/LootLockerServerHeroesRequest.h"

#include "DemoHeroes.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoHeroes : public AActor
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
	int HeroId;
	

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetPlayerHeroes();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetInventoryToHero();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetHeroLoadout();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoEquipAssetForHeroLoadout();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoUnEquipAssetForHeroLoadout();
    
	void OnGetPlayerHeroesCompleted(FLootLockerServerGetPlayerHeroesResponse Response);

	void OnGetInventoryToHeroCompleted(FLootLockerServerHeroInventoryResponse Response);
	
	void OnGetGetHeroLoadoutCompleted(FLootLockerServerGetHeroLoadoutResponse Response);

	void OnEquipAssetForHeroLoadoutCompleted(FLootLockerServerEquipHeroResponse Response);

	void OnUnequipAssetForHeroLoadoutCompleted(FLootLockerServerUnequipHeroResponse Response);

};
