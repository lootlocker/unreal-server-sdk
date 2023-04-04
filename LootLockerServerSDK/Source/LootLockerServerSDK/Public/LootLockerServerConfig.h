// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "LootLockerServerConfig.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLootLockerServerSDK, Log, All);

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "LootLocker Server SDK Settings"))
class LOOTLOCKERSERVERSDK_API ULootLockerServerConfig : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString LootLockerServerKey;
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLockerServer", Meta = (EditCondition = "IsLegacyKey", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString LegacyKeyWarning = "You are using a legacy API Key, please generate a new one here: https://console.lootlocker.com/settings/api-keys";
	// Domain Key used to talk to LootLocker. The Domain key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString LootLockerDomainKey;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
	FString GameVersion;
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Meta = (EditCondition = "false", EditConditionHides), Category = "LootLockerServer")
	FString LootLockerVersion = "2021-03-01";

	static FString GetEnum(const TCHAR* Enum, int32 EnumValue);
	
	UFUNCTION()
	bool IsLegacyAPIKey() const
	{
		return LootLockerServerKey.Find("dev_", ESearchCase::CaseSensitive) == -1 && LootLockerServerKey.Find("prod_", ESearchCase::CaseSensitive) == -1;
	}
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		if (PropertyChangedEvent.GetPropertyName() == "LootLockerServerKey")
		{
			IsLegacyKey = IsLegacyAPIKey();
		}
		UObject::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif //WITH_EDITOR
	virtual void PostInitProperties() override
	{
		UObject::PostInitProperties();
		IsLegacyKey = IsLegacyAPIKey();
	}
private:
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLockerServer")
	bool IsLegacyKey;
};
