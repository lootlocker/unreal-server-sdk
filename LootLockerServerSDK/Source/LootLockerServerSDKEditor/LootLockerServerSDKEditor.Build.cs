// Copyright (c) 2025 LootLocker
using UnrealBuildTool;

public class LootLockerServerSDKEditor : ModuleRules
{
    public LootLockerServerSDKEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "Slate", "SlateCore", "UnrealEd", "ToolMenus", "LootLockerServerSDK", "InputCore", "Json", "JsonUtilities"
        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore", "UnrealEd", "Projects", "HTTP"
        });
    }
}
