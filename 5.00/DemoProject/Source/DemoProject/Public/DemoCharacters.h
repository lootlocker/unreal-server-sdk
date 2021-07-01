// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerAPI/LootLockerServerCharacterRequest.h"

#include "DemoCharacters.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoCharacters : public AActor
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
	int CharacterId;
	

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetPlayerCharacters();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetInventoryToCharacter();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetCharacterLoadout();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoEquipAssetForCharacterLoadout();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoUnEquipAssetForCharacterLoadout();
    
	void OnGetPlayerCharactersCompleted(FLootLockerServerGetPlayerCharactersResponse Response);

	void OnGetInventoryToCharacterCompleted(FLootLockerServerCharacterInventoryResponse Response);
	
	void OnGetGetCharacterLoadoutCompleted(FLootLockerServerGetCharacterLoadoutResponse Response);

	void OnEquipAssetForCharacterLoadoutCompleted(FLootLockerServerEquipCharacterResponse Response);

	void OnUnequipAssetForCharacterLoadoutCompleted(FLootLockerServerUnequipCharacterResponse Response);

};
