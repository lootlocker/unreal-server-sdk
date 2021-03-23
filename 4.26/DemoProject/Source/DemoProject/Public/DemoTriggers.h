// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerAPI/LootLockerServerTriggerRequest.h"

#include "DemoTriggers.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoTriggers : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TriggerName;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoInvokeTriggerOnBehalfOfPlayer();

	void OnInvokeTriggerOnBehalfOfPlayerCompleted(FLootLockerServerInvokeTriggerResponse Response);

};
