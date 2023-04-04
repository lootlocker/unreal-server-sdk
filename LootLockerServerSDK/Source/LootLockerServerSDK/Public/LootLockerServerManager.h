// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"

#include "LootLockerServerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerManager : public UObject
{
    GENERATED_BODY()
 
public:
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Configuration")
	static void SetConfig(FString LootLockerServerKey, FString LootLockerDomainKey, FString GameVersion, FString LootLockerVersion);

    //==================================================
    //Authentication
    //==================================================
    
    /**
    * TODO: Document
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Authentication")
    static void StartSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted);
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Authentication")
    static void MaintainSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted);
};
