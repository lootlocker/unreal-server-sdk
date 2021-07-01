// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAssets.h"

#include "LootLockerServerSDKManager.h"

void ADemoAssets::DemoGetAssetsToGame()
{
	ULootLockerServerSDKManager::GetAssetsToGame(FServerAssetsResponseDelegate::CreateUObject(this, &ADemoAssets::OnGetAssetsToGameCompleted), StartFromIndex, ItemsCount, AssetFilter, IncludeUGC);
}

void ADemoAssets::OnGetAssetsToGameCompleted(FLootLockerServerGetAssetsToGameResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetAssetsToGame Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetAssetsToGame Failed"));
	}
}
