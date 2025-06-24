// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "Delegates/Delegate.h"
#include "Misc/DateTime.h"
#include "LootLockerServerLogger.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLootLockerServer, Log, All);

UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerLogLevel : uint8
{
    Ignore = 0 UMETA(DisplayName = "No Logging"),
    Fatal = 1 UMETA(DisplayName = "Fatal"),
    Error = 2 UMETA(DisplayName = "Error"),
    Warning = 3 UMETA(DisplayName = "Warning"),
    Display = 4 UMETA(DisplayName = "Display"),
    Log = 5 UMETA(DisplayName = "Log"),
    Verbose = 6 UMETA(DisplayName = "Verbose"),
    VeryVerbose = 7 UMETA(DisplayName = "Very Verbose")
};

USTRUCT(BlueprintType)
struct FLootLockerServerHttpLogEntry
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FString Method;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FString Path;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    int32 StatusCode = -1;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    float Duration = 0.0f;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FString RequestData;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FString ResponseData;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FString RequestHeaders;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FString ResponseHeaders;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    bool bSuccess = false;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FDateTime Timestamp;
    UPROPERTY(BlueprintReadOnly, Category = "LootLockerServer")
    FLootLockerServerErrorData ErrorData;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FLootLockerServerOnHttpLogEntry, const FLootLockerServerHttpLogEntry&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FLootLockerServerOnLogMessage, const FString&, ELootLockerServerLogLevel);

class LOOTLOCKERSERVERSDK_API FLootLockerServerLogger
{
public:
    static void Log(const FString& Message, ELootLockerServerLogLevel Verbosity);
    static void LogHttpRequest(const FLootLockerServerHttpLogEntry& Entry);
    static void WriteToFile(const FString& Message);
    static FLootLockerServerOnHttpLogEntry OnHttpLogEntry;
    static FLootLockerServerOnLogMessage OnLogMessage;
    static FCriticalSection FileLogCriticalSection;
};

