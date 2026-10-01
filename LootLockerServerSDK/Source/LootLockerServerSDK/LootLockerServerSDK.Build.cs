// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LootLockerServerSDK : ModuleRules
{
	// Set bForceLocalDevEnv = true here to always target localhost regardless of the environment variable.
	// Leave false (the default) so the env var LOOTLOCKER_USE_LOCAL_DEVENV controls it at build time.
	public static bool bForceLocalDevEnv = false;
	public static bool bTargetLocalDevEnv = bForceLocalDevEnv || !string.IsNullOrEmpty(System.Environment.GetEnvironmentVariable("LOOTLOCKER_USE_LOCAL_DEVENV"));

	public LootLockerServerSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"HTTP",
				"Json",
				"JsonUtilities",
				"Projects"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		if (bTargetLocalDevEnv)
		{
			PublicDefinitions.Add("LOOTLOCKER_USE_LOCAL_DEVENV=1");
		}
}
}
