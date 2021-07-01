// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerAPI/LootLockerServerStorageRequest.h"

#include "DemoPlayerPersistentStorage.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoPlayerPersistentStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Order;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Value;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsPublic;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
	void DemoGetPersistentStorage();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoUpdatePersistentStorage();

	void OnGetPersistentStorageCompleted(FLootLockerServerGetPersistentStorageResponse Response);

	void OnUpdatePersistentStorageCompleted(FLootLockerServerUpdatePersistentStorageResponse Response);

};
