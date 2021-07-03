// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerAPI/LootLockerLeaderboardRequestHandler.h"

#include "DemoLeaderboard.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoLeaderboard : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	ELootLockerLeaderboardType type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	ELootLockerLeaderboardDirection direction_method;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool enable_game_api_writes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool overwrite_score_on_submit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int leaderboardId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString member_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int score;

	 UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Leaderboard")
	 void CreateLeaderboard();
	 UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Leaderboard")
	 void UpdateLeaderboard();
	 UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Leaderboard")
	 void DeleteLeaderboard();
	 UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Leaderboard")
	 void SubmitScore();

	void OnCreateLeaderboardCompleted(FLootLockerCreateLeaderboardResponse Response);
	void OnUpdateLeaderboardCompleted(FLootLockerUpdateLeaderboardResponse Response);
	void OnDeleteLeaderboardCompleted(FLootLockerDeleteLeaderboardResponse Response);
	void OnSubmitScoreCompleted(FLootLockerSubmitScoreResponse Response);

};
