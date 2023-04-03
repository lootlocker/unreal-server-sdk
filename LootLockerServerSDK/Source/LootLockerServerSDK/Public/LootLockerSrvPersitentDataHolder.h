// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSrvPersitentDataHolder.generated.h"

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerSrvPersitentDataHolder : public UObject
{
	GENERATED_BODY()
	public:	
	static FString Token;
	static FString ServerToken;
	static FString CachedLastEndpointUsed;
	static FString CachedLastRequestTypeUsed;
	static FString CachedLastDataSentToServer;
	static FString CachedSteamToken;
	static FString CachedPlayerIdentifier;
	static FString AdminToken;	
};
