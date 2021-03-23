// Copyright Epic Games, Inc. All Rights Reserved.
#include "LootLockerServerSDK.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LootLockerServerConfig.h"
#endif
#include "UObject/ConstructorHelpers.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"



#define LOCTEXT_NAMESPACE "FLootLockerServerSDKModule"
 
void FLootLockerServerSDKModule::StartupModule()
{
#if WITH_EDITOR

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "LootLocker Server",
			LOCTEXT("LootLockerSDKSettingsName", "LootLockerServerSDK"),
			LOCTEXT("LootLockerSDKSettingsDescription", "Configure LootLockerServer SDK."),
			GetMutableDefault<ULootLockerServerConfig>()
		);
	}

#endif
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FLootLockerServerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLootLockerServerSDKModule, LootLockerServerSDK)