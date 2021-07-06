// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoLeaderboard.h"
#include "LootLockerServerSDKManager.h"



void ADemoLeaderboard::CreateLeaderboard()
{
	FLootLockerServerCreateLeaderboardRequest request = FLootLockerServerCreateLeaderboardRequest();
	request.name = name;
	request.key = key;
	FString localType = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerLeaderboardType"), static_cast<int32>(type));
	FString localDirection = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerLeaderboardDirection"), static_cast<int32>(direction_method));


	request.direction_method = localDirection;
	request.type = localType;
	request.enable_game_api_writes = enable_game_api_writes;
	request.overwrite_score_on_submit = overwrite_score_on_submit;

	ULootLockerServerSDKManager::CreateLeaderboard(request, FLootLockerServerCreateLeaderboardResponseDelegate::CreateUObject(this, &ADemoLeaderboard::OnCreateLeaderboardCompleted));
}

void ADemoLeaderboard::UpdateLeaderboard()
{
	FLootLockerServerUpdateLeaderboardRequest request = FLootLockerServerUpdateLeaderboardRequest();
	request.name = name;
	FString localType = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerLeaderboardType"), static_cast<int32>(type));
	FString localDirection = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerLeaderboardDirection"), static_cast<int32>(direction_method));

	
	request.direction_method = localDirection;
	request.type = localType;
	request.key = key;
	request.enable_game_api_writes = enable_game_api_writes;
	request.overwrite_score_on_submit = overwrite_score_on_submit;

	ULootLockerServerSDKManager::UpdateLeaderboard(request,leaderboardId ,FLootLockerServerUpdateLeaderboardResponseDelegate::CreateUObject(this, &ADemoLeaderboard::OnUpdateLeaderboardCompleted));
}

void ADemoLeaderboard::DeleteLeaderboard()
{
	ULootLockerServerSDKManager::DeleteLeaderboard( leaderboardId, FLootLockerServerDeleteLeaderboardResponseDelegate::CreateUObject(this, &ADemoLeaderboard::OnDeleteLeaderboardCompleted));
}

void ADemoLeaderboard::SubmitScore()
{
	ULootLockerServerSDKManager::SubmitScore(member_id,leaderboardId, score, FLootLockerServerSubmitScoreResponseDelegate::CreateUObject(this, &ADemoLeaderboard::OnSubmitScoreCompleted));
}

void ADemoLeaderboard::OnCreateLeaderboardCompleted(FLootLockerServerCreateLeaderboardResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Failed"));
	}
}

void ADemoLeaderboard::OnUpdateLeaderboardCompleted(FLootLockerServerUpdateLeaderboardResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Failed"));
	}
}

void ADemoLeaderboard::OnDeleteLeaderboardCompleted(FLootLockerServerDeleteLeaderboardResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Failed"));
	}
}

void ADemoLeaderboard::OnSubmitScoreCompleted(FLootLockerServerSubmitScoreResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnCreateLeaderboardCompleted Failed"));
	}
}
