// Copyright (c) 2021 LootLocker

// Regression test for issue #1411:
// EnableFileLogging() and DisableFileLogging() must not overwrite settings in
// DefaultGame.ini that belong to other sections/plugins.
//
// Run headless from the command line (no backend connection required):
//   UnrealEditor-Cmd.exe "YourProject.uproject" -unattended -nullrhi -nosound
//     -ExecCmds="automation RunTests LootLockerServer.Config;quit"

#include "LootLockerServerConfig.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/ConfigCacheIni.h"

#if ENGINE_MAJOR_VERSION > 4

/**
 * Verifies that calling EnableFileLogging / DisableFileLogging does not wipe
 * other sections in DefaultGame.ini (regression for issue #1411).
 */
IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLootLockerServerConfigSavePreservesOtherIniSettingsTest,
    "LootLockerServer.Config.SaveConfigPreservesOtherIniSettings",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter
)

bool FLootLockerServerConfigSavePreservesOtherIniSettingsTest::RunTest(const FString& Parameters)
{
    // -------------------------------------------------------------------------
    // 1. Locate the DefaultGame.ini that ULootLockerServerConfig writes to.
    // -------------------------------------------------------------------------
    ULootLockerServerConfig* MutableConfig = GetMutableDefault<ULootLockerServerConfig>();
    const FString ConfigFilename = MutableConfig->GetDefaultConfigFilename();

    if (!TestFalse("DefaultGame.ini path should not be empty", ConfigFilename.IsEmpty()))
    {
        return false;
    }

    // -------------------------------------------------------------------------
    // 2. Save original file-logging state so we can restore it after the test.
    // -------------------------------------------------------------------------
    const bool bWasEnabled = ULootLockerServerConfig::IsFileLoggingEnabled();
    const FString OriginalLogFileName = MutableConfig->LogFileName;

    // -------------------------------------------------------------------------
    // 3. Write a "sentinel" entry into a section that LootLocker has nothing to
    //    do with, simulating settings from another plugin stored in the same
    //    DefaultGame.ini.
    //
    //    Written directly with FFileHelper to avoid GConfig path-normalisation
    //    issues or a missing Config/ directory in a fresh test project.
    // -------------------------------------------------------------------------
    const FString SentinelSection = TEXT("/Script/IssueRegression1411Server.SentinelConfig");
    const FString SentinelKey     = TEXT("SentinelValue_1411");
    const FString SentinelValue   = TEXT("MUST_BE_PRESERVED_ACROSS_SAVECONFIG");

    // Ensure the Config directory exists.
    IPlatformFile::GetPlatformPhysical().CreateDirectoryTree(*FPaths::GetPath(ConfigFilename));

    // Read any existing content, then append the sentinel section.
    FString InitialContent;
    FFileHelper::LoadFileToString(InitialContent, *ConfigFilename);

    if (!InitialContent.IsEmpty() && !InitialContent.EndsWith(TEXT("\n")))
    {
        InitialContent += TEXT("\r\n");
    }
    InitialContent += FString::Printf(
        TEXT("[%s]\r\n%s=%s\r\n"), *SentinelSection, *SentinelKey, *SentinelValue);

    if (!TestTrue("Setup: should be able to write sentinel to config file",
            FFileHelper::SaveStringToFile(InitialContent, *ConfigFilename)))
    {
        return false;
    }

    // Reload into GConfig so in-memory and on-disk state match.
    GConfig->LoadFile(ConfigFilename);

    // Confirm the sentinel is on disk before any LootLocker operations.
    FString DiskContentsBeforeEnable;
    if (!TestTrue("Config file should be readable from disk",
            FFileHelper::LoadFileToString(DiskContentsBeforeEnable, *ConfigFilename)))
    {
        return false;
    }
    TestTrue("Sentinel value should be present on disk before calling EnableFileLogging",
        DiskContentsBeforeEnable.Contains(SentinelValue));

    // -------------------------------------------------------------------------
    // 4. EnableFileLogging — this triggered the bug before the fix.
    // -------------------------------------------------------------------------
    const FString TestLogFileName = TEXT("LootLockerServerTestLog_1411");
    ULootLockerServerConfig::EnableFileLogging(TestLogFileName);

    FString DiskContentsAfterEnable;
    TestTrue("Config file should still be readable from disk after EnableFileLogging",
        FFileHelper::LoadFileToString(DiskContentsAfterEnable, *ConfigFilename));

    const bool bSentinelSurvivesEnable = DiskContentsAfterEnable.Contains(SentinelValue);
    TestTrue(
        "After EnableFileLogging, settings from unrelated sections must not be erased "
        "from DefaultGame.ini.  A FAIL here indicates issue #1411 is not fixed.",
        bSentinelSurvivesEnable);

    TestTrue(
        "After EnableFileLogging, bEnableFileLogging=True must be written to DefaultGame.ini on disk",
        DiskContentsAfterEnable.Contains(TEXT("bEnableFileLogging=True")));
    TestTrue(
        "After EnableFileLogging, the log file name must be written to DefaultGame.ini on disk",
        DiskContentsAfterEnable.Contains(TestLogFileName));

    // -------------------------------------------------------------------------
    // 5. DisableFileLogging — same checks.
    // -------------------------------------------------------------------------
    ULootLockerServerConfig::DisableFileLogging();

    FString DiskContentsAfterDisable;
    TestTrue("Config file should still be readable from disk after DisableFileLogging",
        FFileHelper::LoadFileToString(DiskContentsAfterDisable, *ConfigFilename));

    const bool bSentinelSurvivesDisable = DiskContentsAfterDisable.Contains(SentinelValue);
    TestTrue(
        "After DisableFileLogging, settings from unrelated sections must not be erased "
        "from DefaultGame.ini.  A FAIL here indicates issue #1411 is not fixed.",
        bSentinelSurvivesDisable);

    TestTrue(
        "After DisableFileLogging, bEnableFileLogging=False must be written to DefaultGame.ini on disk",
        DiskContentsAfterDisable.Contains(TEXT("bEnableFileLogging=False")));

    // -------------------------------------------------------------------------
    // 6. Cleanup — remove sentinel and restore original logging config.
    // -------------------------------------------------------------------------
    GConfig->RemoveKey(*SentinelSection, *SentinelKey, ConfigFilename);
    GConfig->Flush(false, ConfigFilename);

    if (bWasEnabled)
    {
        ULootLockerServerConfig::EnableFileLogging(
            OriginalLogFileName.IsEmpty() ? TEXT("LootLockerServerLog") : OriginalLogFileName);
    }

    return true;
}

#endif // ENGINE_MAJOR_VERSION > 4
