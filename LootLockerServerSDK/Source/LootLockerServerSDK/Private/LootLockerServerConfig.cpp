// Copyright (c) 2021 LootLocker

#include "LootLockerServerConfig.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Interfaces/IPluginManager.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/AES.h"
#include "Misc/Base64.h"

#if ENGINE_MAJOR_VERSION < 5
const FString ULootLockerServerConfig::PreConfigFileName = TEXT("LootLockerServerPreConfig.bytes");
bool ULootLockerServerConfig::bFileConfigChecked = false;
TOptional<FLootLockerServerFileConfig> ULootLockerServerConfig::FileConfig;
#endif

namespace {
    static bool bRuntimeLogLevelOverrideSet = false;
    static ELootLockerServerLogLevel RuntimeLogLevelOverride = ELootLockerServerLogLevel::Ignore;
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
#if ENGINE_MAJOR_VERSION >= 5
    Config->TryUpdateDefaultConfigFile();
#else
    Config->UpdateDefaultConfigFile();
#endif
}

void ULootLockerServerConfig::DisableFileLogging()
{
    ULootLockerServerConfig* Config = GetMutableDefault<ULootLockerServerConfig>();
    Config->bEnableFileLogging = false;
    Config->LogFilePath = TEXT("");
    Config->LongLogFilePath = "";
#if ENGINE_MAJOR_VERSION >= 5
    Config->TryUpdateDefaultConfigFile();
#else
    Config->UpdateDefaultConfigFile();
#endif
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

// ========================================================================
// FILE CONFIG IMPLEMENTATION
// ========================================================================

bool ULootLockerServerConfig::IsFileConfigActive()
{
    if (!bFileConfigChecked)
    {
        ULootLockerServerConfig::LoadFileConfig();
    }
    return FileConfig.IsSet();
}

// Hardcoded decryption key for pre-config files.
// This is intentionally embedded rather than configurable — the scheme is only meant to
// keep the API key out of casual plain-text searches, not to provide cryptographic security.
inline static const FAES::FAESKey GetServerFileConfigDecryptionKey()
{
    static const uint8 KeyBytes[32] = {
        0x4C, 0x6F, 0x6F, 0x74, 0x4C, 0x6F, 0x63, 0x6B,
        0x65, 0x72, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72,
        0x50, 0x72, 0x65, 0x43, 0x6F, 0x6E, 0x66, 0x69,
        0x67, 0x4B, 0x65, 0x79, 0x32, 0x30, 0x32, 0x35
    };
    FAES::FAESKey Key;
    FMemory::Memcpy(Key.Key, KeyBytes, 32);
    return Key;
}

TOptional<FLootLockerServerFileConfig> ULootLockerServerConfig::ParseFileConfigContent(const FString& Content)
{
    if (Content.IsEmpty())
    {
        return {};
    }

    FString JsonString;

    // Try plain JSON first
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        JsonString = Content;
    }
    else
    {
        // Try AES-256-ECB + PKCS7 + Base64 decryption
        TArray<uint8> EncryptedData;
        if (!FBase64::Decode(Content, EncryptedData))
        {
            return {};
        }

        // FAES operates on whole blocks (AES block size is 16 bytes)
        if (EncryptedData.Num() == 0 || (EncryptedData.Num() % 16) != 0)
        {
            return {};
        }

        const FAES::FAESKey DecryptionKey = GetServerFileConfigDecryptionKey();
        FAES::DecryptData(EncryptedData.GetData(), EncryptedData.Num(), DecryptionKey);

        // Remove PKCS7 padding
        if (EncryptedData.Num() > 0)
        {
            const uint8 PaddingValue = EncryptedData.Last();
            if (PaddingValue > 0 && PaddingValue <= 16 && PaddingValue <= EncryptedData.Num())
            {
                bool bValidPadding = true;
                for (int32 i = 1; i <= PaddingValue; ++i)
                {
                    if (EncryptedData[EncryptedData.Num() - i] != PaddingValue)
                    {
                        bValidPadding = false;
                        break;
                    }
                }
                if (bValidPadding)
                {
                    EncryptedData.SetNum(EncryptedData.Num() - PaddingValue);
                }
            }
        }

        // Convert decrypted bytes to UTF-8 string (ensure null-terminated for UTF8_TO_TCHAR)
        EncryptedData.Add(0);
        JsonString = UTF8_TO_TCHAR(reinterpret_cast<const char*>(EncryptedData.GetData()));

        // Re-parse the decrypted JSON
        Reader = TJsonReaderFactory<>::Create(JsonString);
        if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
        {
            return {};
        }
    }

    FLootLockerServerFileConfig Config;
    if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &Config, 0, 0))
    {
        return {};
    }

    // api_key is the gating field — empty or missing means "inactive"
    if (Config.api_key.IsEmpty())
    {
        return {};
    }

    return Config;
}

void ULootLockerServerConfig::LoadFileConfig()
{
    if (bFileConfigChecked)
    {
        return;
    }

    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("LootLockerServerSDK"));
    if (!Plugin.IsValid())
    {
        bFileConfigChecked = true;
        return;
    }

    const FString FilePath = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Config"), PreConfigFileName);

    FString Content;
    if (!FFileHelper::LoadFileToString(Content, *FilePath))
    {
        bFileConfigChecked = true;
        return;
    }

    FileConfig = ParseFileConfigContent(Content);
    bFileConfigChecked = true;
}

void ULootLockerServerConfig::ApplyFileConfigIfPresent()
{
    if (!IsFileConfigActive())
    {
        ULootLockerServerConfig* Default = GetMutableDefault<ULootLockerServerConfig>();
        Default->bIsFileConfigLocked = false;
        return;
    }

    const FLootLockerServerFileConfig& FC = FileConfig.GetValue();
    ULootLockerServerConfig* Config = GetMutableDefault<ULootLockerServerConfig>();

    Config->LootLockerServerKey = FC.api_key;
    if (!FC.domain_key.IsEmpty())
    {
        Config->LootLockerDomainKey = FC.domain_key;
    }
    if (!FC.game_version.IsEmpty())
    {
        Config->GameVersion = FC.game_version;
    }
    Config->IsValidGameVersion = IsSemverString(Config->GameVersion);
    Config->LogOutsideOfEditor = FC.log_outside_of_editor;

    // Map log_level enum string -> ELootLockerServerLogLevel
    if (!FC.log_level.IsEmpty())
    {
        const UEnum* Enum = StaticEnum<ELootLockerServerLogLevel>();
        const int64 Value = Enum->GetValueByNameString(FC.log_level);
        if (Value != INDEX_NONE)
        {
            Config->LimitLogLevelTo = static_cast<ELootLockerServerLogLevel>(Value);
        }
    }

    Config->bEnableFileLogging = FC.enable_file_logging;
    Config->bIsFileConfigLocked = true;

    if (Config->bEnableFileLogging)
    {
        EnableFileLogging(Config->LogFileName.IsEmpty() ? TEXT("LootLockerServerLog") : Config->LogFileName);
    }
    else
    {
        DisableFileLogging();
    }
}
