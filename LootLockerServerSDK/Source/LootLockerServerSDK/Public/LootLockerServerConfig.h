// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"
#if ENGINE_MAJOR_VERSION >= 5
#include <regex>
#endif
#include "LootLockerServerLogger.h"
#include "LootLockerServerConfig.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "LootLocker Server SDK Settings"))
class LOOTLOCKERSERVERSDK_API ULootLockerServerConfig : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerConfig();

    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString LootLockerServerKey = "";
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString LootLockerDomainKey = "";
    UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLockerServer", Meta = (EditCondition = "IsLegacyKey", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
    FString LegacyKeyWarning = "You are using a legacy API Key, please generate a new one here: https://console.lootlocker.com/settings/api-keys";
    UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLockerServer", Meta = (EditCondition = "!IsValidGameVersion", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
    FString InvalidGameVersionWarning = "";
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString GameVersion = "";
    UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Meta = (EditCondition = "false", EditConditionHides), Category = "LootLockerServer")
    FString LootLockerVersion = "2021-06-01";
    // Logging configuration
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer|Logging")
    ELootLockerServerLogLevel LimitLogLevelTo = ELootLockerServerLogLevel::Display;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer|Logging")
    bool LogOutsideOfEditor = false;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer|Logging")
    bool bEnableFileLogging = false;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer|Logging")
    FString LogFileName = TEXT("LootLockerServer.log");
    UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLockerServer|Logging", Meta = (EditCondition = "bEnableFileLogging", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "Actual Log File (on current device)"), Transient)
    FString LongLogFilePath = "";
private:
    FString LogFilePath = "";
public:
    // Logging API
    static ELootLockerServerLogLevel GetConfiguredLogLevel()
    {
        return GetDefault<ULootLockerServerConfig>()->LimitLogLevelTo;
    }

    /**
     * Sets the log level at runtime (not persisted).
     * @param NewLevel The new log level to use for this session.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static void SetRuntimeLogLevel(ELootLockerServerLogLevel NewLevel);

    /**
     * Gets the current runtime log level (runtime override or config).
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static ELootLockerServerLogLevel GetRuntimeLogLevel();

    /**
     * Enables file logging to the specified file name.
     * @param FileName The log file name (relative to project log dir).
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static void EnableFileLogging(const FString& FileName);

    /**
     * Disables file logging.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static void DisableFileLogging();

    /**
     * Returns true if file logging is enabled and a log file name is set.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static bool IsFileLoggingEnabled();

    /**
     * Returns the current log file path (may be empty if not enabled).
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static FString GetLogFilePath();
	
private:
	
	UFUNCTION()
	bool IsLegacyAPIKey() const
	{
		return LootLockerServerKey.Find("dev_", ESearchCase::CaseSensitive) == -1 && LootLockerServerKey.Find("prod_", ESearchCase::CaseSensitive) == -1;
	}

	UFUNCTION()
	static bool ShouldLog()
	{
#if WITH_EDITOR
		return true;
#else
		return GetDefault<ULootLockerServerConfig>()->LogOutsideOfEditor;
#endif		
	}

	UFUNCTION()
	static bool IsSemverString(const FString& str)
	{
#if ENGINE_MAJOR_VERSION >= 5
		return std::regex_match(TCHAR_TO_UTF8(*str), SemverPattern);
#else
		return true;
#endif
	}
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		if (PropertyChangedEvent.GetPropertyName() == "LootLockerServerKey")
		{
			IsLegacyKey = IsLegacyAPIKey();
		}
		if (PropertyChangedEvent.GetPropertyName() == "GameVersion")
		{
			IsValidGameVersion = IsSemverString(GameVersion);
		}
		if (PropertyChangedEvent.GetPropertyName() == "bEnableFileLogging" || PropertyChangedEvent.GetPropertyName() == "LogFileName")
		{
			if (bEnableFileLogging)
			{
				EnableFileLogging(LogFileName.IsEmpty() ? "LootLockerServer.log" : LogFileName);
			}
			else
			{
				DisableFileLogging();
			}
		}
		UObject::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif //WITH_EDITOR
	virtual void PostInitProperties() override
	{
		IsLegacyKey = IsLegacyAPIKey();
		IsValidGameVersion = IsSemverString(GameVersion);
		if(bEnableFileLogging)
		{
			EnableFileLogging(LogFileName.IsEmpty() ? "LootLockerServer.log" : LogFileName);
		}
		else
		{
			DisableFileLogging();
		}
		UObject::PostInitProperties();
	}
private:
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLockerServer")
	bool IsLegacyKey = false;
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLockerServer")
	bool IsValidGameVersion = true;
#if ENGINE_MAJOR_VERSION >= 5
	inline static const std::regex SemverPattern = std::regex("^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:\\.(0|[1-9]\\d*))?(?:\\.(0|[1-9]\\d*))?$");
#endif
};
