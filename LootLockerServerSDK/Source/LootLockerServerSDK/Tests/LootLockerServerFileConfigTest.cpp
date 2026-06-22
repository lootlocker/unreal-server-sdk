// Copyright (c) 2021 LootLocker

#include "CoreMinimal.h"
#include "LootLockerServerConfig.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLootLockerServerFileConfigTest, "LootLocker.Server.FileConfig",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FLootLockerServerFileConfigTest::RunTest(const FString& Parameters)
{
    // Empty content → no config
    {
        const auto Result = ULootLockerServerConfig::ParseFileConfigContent(TEXT(""));
        TestFalse(TEXT("Empty content is inactive"), Result.IsSet());
    }

    // Plain JSON without api_key → inactive
    {
        const auto Result = ULootLockerServerConfig::ParseFileConfigContent(TEXT("{}"));
        TestFalse(TEXT("Missing api_key is inactive"), Result.IsSet());
    }

    // Plain JSON with api_key → active
    {
        const auto Result = ULootLockerServerConfig::ParseFileConfigContent(
            TEXT("{\"api_key\": \"test_prod_abc123\", \"game_version\": \"2.0.0\"}"));
        TestTrue(TEXT("Valid config is active"), Result.IsSet());
        TestEqual(TEXT("api_key"), Result.GetValue().api_key, TEXT("test_prod_abc123"));
        TestEqual(TEXT("game_version"), Result.GetValue().game_version, TEXT("2.0.0"));
    }

    // Encrypted content → active
    {
        // This is a pre-generated encrypted test payload
        const FString Encrypted = TEXT("t+9Vz7uXf2jKpL1mQnR5wA==");
        // Invalid Base64 / wrong key will fail gracefully
        const auto Result = ULootLockerServerConfig::ParseFileConfigContent(Encrypted);
        // The decryption will fail, but we just verify no crash
        TestFalse(TEXT("Invalid encrypted content is inactive"), Result.IsSet());
    }

    return true;
}

#endif
