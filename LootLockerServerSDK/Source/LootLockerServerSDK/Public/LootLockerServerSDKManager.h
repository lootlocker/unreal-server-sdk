// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerLeaderboardRequest.h"

#include "LootLockerServerSDKManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerSDKManager : public UObject
{
	GENERATED_BODY()

public:
    
    //==================================================
    // Authentication
    //==================================================
    
    /**
     * TODO: Document
     */
	static void StartSession(const FLootLockerServerAuthResponseDelegate& OnCompletedRequest);

    /**
     * TODO: Document
     */
    static void MaintainSession(const FLootLockerServerAuthResponseDelegate& OnCompletedRequest);

    //==================================================
    // Leaderboards
    //==================================================

    /**
     * TODO: Document
     */
    static void CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection
                                  DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest);

    /**
     * TODO: Document
     */
    static void UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest);

    /**
     * TODO: Document
     */
    static void DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest);

    /**
     * TODO: Document
     */
    static void SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest);
};
