// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerLeaderboardRequest.h"

#include "LootLockerServerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerManager : public UObject
{
    GENERATED_BODY()
 
public:
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Configuration")
	static void SetConfig(FString LootLockerServerKey, FString LootLockerDomainKey, FString GameVersion, FString LootLockerVersion);

    //==================================================
    //Authentication
    //==================================================
    
    /**
    * TODO: Document
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Authentication")
    static void StartSession(const FLootLockerServerAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * TODO: Document
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Authentication")
    static void MaintainSession(const FLootLockerServerAuthResponseBP& OnStartedSessionRequestCompleted);

    //==================================================
    // Leaderboards
    //==================================================

    /**
     * TODO: Document
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Leaderboards")
    static void CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequest);

    /**
     * TODO: Document
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Leaderboards")
    static void UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequest);

    /**
     * TODO: Document
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Leaderboards")
    static void DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequest);

    /**
     * TODO: Document
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Leaderboards")
    static void SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequest);

    /**
     * TODO: Document
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Leaderboards")
    static void GetAllMemberRanks(FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest);

    /**
     * TODO: Document
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer | Leaderboards")
    static void GetScoresFromLeaderboard(FString LeaderboardKey, int Count, int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest);
};
