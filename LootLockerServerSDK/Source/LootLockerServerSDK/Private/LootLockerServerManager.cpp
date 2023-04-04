// Copyright (c) 2021 LootLocker

#include "LootLockerServerManager.h"

void ULootLockerServerManager::SetConfig(FString LootLockerServerKey, FString LootLockerDomainKey, FString GameVersion, FString LootLockerVersion)
{
    ULootLockerServerConfig* config = GetMutableDefault<ULootLockerServerConfig>();
    config->LootLockerServerKey = LootLockerServerKey;
    config->LootLockerDomainKey = LootLockerDomainKey;
    config->GameVersion = GameVersion;
    config->LootLockerVersion = LootLockerVersion;
    config->SaveConfig();
}

void ULootLockerServerManager::StartSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerServerAuthRequest::StartSession(OnStartedSessionRequestCompleted);
}
void ULootLockerServerManager::MaintainSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerServerAuthRequest::MaintainSession(OnStartedSessionRequestCompleted);
}
