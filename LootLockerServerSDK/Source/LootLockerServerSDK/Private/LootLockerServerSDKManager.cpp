// Copyright (c) 2021 LootLocker


#include "LootLockerServerSDKManager.h"

//Authentication
void ULootLockerServerSDKManager::StartSession(const FServerAuthResponse& OnCompleteRequest)
{
	ULootLockerServerAuthRequest::StartSession( FServerAuthResponseBP(), OnCompleteRequest);
}

void ULootLockerServerSDKManager::MaintainSession(const FServerAuthResponse& OnCompleteRequest)
{
	ULootLockerServerAuthRequest::MaintainSession(FServerAuthResponseBP(), OnCompleteRequest);
}
