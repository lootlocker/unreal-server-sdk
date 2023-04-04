// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"

#include "LootLockerServerSDKManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerSDKManager : public UObject
{
	GENERATED_BODY()

public:
    
    //==================================================
    //Authentication
    //==================================================
    
    /**
     * Register a session.
     * @param PlayerId - the ID of the player on the platform the game is currently running on.
     * @param OnCompletedRequest - callback to be invoked with the server response.
     * https://docs.lootlocker.io/game-api/#authentication-request
     */
	static void StartSession(const FServerAuthResponse& OnCompletedRequest);

    static void MaintainSession(const FServerAuthResponse& OnCompletedRequest);
};
