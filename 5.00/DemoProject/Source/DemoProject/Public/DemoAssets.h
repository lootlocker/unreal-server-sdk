// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "DemoAssets.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoAssets : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int StartFromIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ItemsCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ELootLockerServerAssetFilter AssetFilter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IncludeUGC;
    
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetAssetsToGame();
    
	void OnGetAssetsToGameCompleted(FLootLockerServerGetAssetsToGameResponse Response);
};
