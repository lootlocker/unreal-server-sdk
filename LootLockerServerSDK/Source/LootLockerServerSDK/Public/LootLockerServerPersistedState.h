// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LootLockerServerPersistedState.generated.h"

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPersistedState : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "LootLockerServer")
	FString ServerToken = "";

	ULootLockerServerPersistedState() {}
};
