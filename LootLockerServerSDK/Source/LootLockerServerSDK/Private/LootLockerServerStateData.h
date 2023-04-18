// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerStateData.generated.h"


UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerStateData : public UObject
{
	GENERATED_BODY()
    static FString ServerToken;

public:
	static FString GetServerToken();
	static void SetServerToken(FString InServerToken);
    static void ClearState();
};