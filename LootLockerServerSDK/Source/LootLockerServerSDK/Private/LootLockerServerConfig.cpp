// Copyright (c) 2021 LootLocker

#include "LootLockerServerConfig.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"

namespace {
    static bool bRuntimeLogLevelOverrideSet = false;
    static ELootLockerServerLogLevel RuntimeLogLevelOverride = ELootLockerServerLogLevel::Ignore;
}

ULootLockerServerConfig::ULootLockerServerConfig()
{
    LimitLogLevelTo = ELootLockerServerLogLevel::Warning;
}

void ULootLockerServerConfig::SetRuntimeLogLevel(ELootLockerServerLogLevel NewLevel)
{
    RuntimeLogLevelOverride = NewLevel;
    bRuntimeLogLevelOverrideSet = true;
}

ELootLockerServerLogLevel ULootLockerServerConfig::GetRuntimeLogLevel()
{
    if (bRuntimeLogLevelOverrideSet)
        return RuntimeLogLevelOverride;
    return GetConfiguredLogLevel();
}

void ULootLockerServerConfig::EnableFileLogging(const FString& FileName)
{
    ULootLockerServerConfig* Config = GetMutableDefault<ULootLockerServerConfig>();
    Config->bEnableFileLogging = true;
    Config->LogFileName = FileName;
    FString LogDir = FPaths::ProjectLogDir();
    if (LogDir.IsEmpty())
    {
        LogDir = FPaths::EngineSavedDir() / TEXT("Logs");
    }
    FString DateAppendix = FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d"));
    Config->LogFilePath = FPaths::Combine(LogDir, FileName + TEXT("_") + DateAppendix + TEXT(".log"));
    Config->LongLogFilePath = FPaths::ConvertRelativePathToFull(Config->LogFilePath);
    Config->SaveConfig();
}

void ULootLockerServerConfig::DisableFileLogging()
{
    ULootLockerServerConfig* Config = GetMutableDefault<ULootLockerServerConfig>();
    Config->bEnableFileLogging = false;
    Config->LogFilePath = TEXT("");
    Config->LongLogFilePath = "";
    Config->SaveConfig();
}

bool ULootLockerServerConfig::IsFileLoggingEnabled()
{
    const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
    return Config->bEnableFileLogging && !Config->LogFileName.IsEmpty();
}

FString ULootLockerServerConfig::GetLogFilePath()
{
    const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
    return Config->LogFilePath;
}
