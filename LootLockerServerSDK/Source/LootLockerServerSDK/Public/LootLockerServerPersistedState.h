// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LootLockerServerPersistedState.generated.h"

/**
 Data definition of properties that are persisted to disk
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPersistedState : public USaveGame
{
	GENERATED_BODY()
public:
	/*
	 The session token for the authenticated session
	 */
	UPROPERTY(VisibleAnywhere, Category = "LootLockerServer")
	FString ServerToken = "";

	ULootLockerServerPersistedState() {}
};
