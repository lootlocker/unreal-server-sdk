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
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString LootLockerServerKey = "";
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLockerServer", Meta = (EditCondition = "IsLegacyKey", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString LegacyKeyWarning = "You are using a legacy API Key, please generate a new one here: https://console.lootlocker.com/settings/api-keys";
	// Domain Key used to talk to LootLocker. The Domain key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString LootLockerDomainKey = "";
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString GameVersion = "";
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLockerServer", Meta = (EditCondition = "!IsValidGameVersion", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString InvalidGameVersionWarning = "Game version needs to follow a numeric Semantic Versioning pattern: X.Y.Z.B with the sections denoting MAJOR.MINOR.PATCH.BUILD and the last two being optional. Read more at https://docs.lootlocker.com/the-basics/core-concepts/glossary#game-version";
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Meta = (EditCondition = "false", EditConditionHides), Category = "LootLockerServer")
	FString LootLockerVersion = "2021-06-01";
	// Limit the log level for the LootLocker Server SDK to this log level, will neither affect nor override the log level for the rest of your game 
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	ELootLockerServerLogLevelConfiguration LimitLogLevelTo = ELootLockerServerLogLevelConfiguration::Display;
	// Set to true if you want LootLocker to log outside of an editor context. We recommend that this only be enabled for debugging purposes.
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	bool LogOutsideOfEditor = false;
	
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
		return GetDefault<ULootLockerConfig>()->LogOutsideOfEditor;
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
		UObject::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif //WITH_EDITOR
	virtual void PostInitProperties() override
	{
		IsLegacyKey = IsLegacyAPIKey();
		IsValidGameVersion = IsSemverString(GameVersion);
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
