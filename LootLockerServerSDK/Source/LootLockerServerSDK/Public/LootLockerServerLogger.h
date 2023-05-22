// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerLogger.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLootLockerServer, Log, All);

UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerLogLevel : uint8
{
		Ignore = 0			UMETA(DisplayName = "No Logging"),
		Fatal = 1			UMETA(DisplayName = "Fatal"),
		Error = 2			UMETA(DisplayName = "Error"),
		Warning = 3			UMETA(DisplayName = "Warning"),
		Display = 4			UMETA(DisplayName = "Display"),
		Log = 5				UMETA(DisplayName = "Log"),
		Verbose = 6			UMETA(DisplayName = "Verbose"),
		VeryVerbose = 7		UMETA(DisplayName = "Very Verbose")
};

UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerLogLevelConfiguration : uint8
{
		NoLogging = 0		UMETA(DisplayName = "No Logging"),
		Fatal = 1			UMETA(DisplayName = "Fatal"),
		Error = 2			UMETA(DisplayName = "Error"),
		Warning = 3			UMETA(DisplayName = "Warning"),
		Display = 4			UMETA(DisplayName = "Display"),
		Log = 5				UMETA(DisplayName = "Log"),
		Verbose = 6			UMETA(DisplayName = "Verbose"),
		VeryVerbose = 7		UMETA(DisplayName = "Very Verbose"),
		All = VeryVerbose	UMETA(DisplayName = "All"),
		// Log errors and warnings as normal log messages
		AllAsNormal = 8		UMETA(DisplayName = "All as normal")
};

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerLogger : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerLogger();	

	static void Log(FString LogMessage);
	static void Log(ELootLockerServerLogLevel LogLevel, FString LogMessage);
};

