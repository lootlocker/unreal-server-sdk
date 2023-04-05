// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Launch/Resources/Version.h"
#include "LootLockerServerStateData.generated.h"


UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerStateData : public UObject
{
	GENERATED_BODY()
    static FString ServerToken;

#if ENGINE_MAJOR_VERSION < 5
	static const FString SaveSlot;
    static constexpr int SaveIndex = 0;
#else
    inline static const FString SaveSlot = "LootLockerServer";
    inline static constexpr int SaveIndex = 0;
#endif
	static bool StateLoaded;

	static void LoadStateFromDiskIfNeeded();
	static void SaveStateToDisk();
public:
	static FString GetServerToken();
	static void SetServerToken(FString InServerToken);
    static void ClearState();
};