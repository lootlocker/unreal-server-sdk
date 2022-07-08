// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LootLockerServerSDKManager.h"
#include "GameFramework/Actor.h"
#include "DemoAuth.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoAuth : public AActor
{
	GENERATED_BODY()
public:	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoStartSession();
    
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoMaintainSession();
    
	void OnStartSessionCompleted(FLootLockerServerAuthenticationResponse Response);
	void OnMaintainSessionCompleted(FLootLockerServerPingResponse Response);

};
