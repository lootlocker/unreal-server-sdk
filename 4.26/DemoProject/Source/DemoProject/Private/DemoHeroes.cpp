// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoHeroes.h"

#include "LootLockerServerSDKManager.h"

void ADemoHeroes::DemoGetPlayerHeroes()
{
	ULootLockerServerSDKManager::GetPlayerHeroes(FHeroesResponse::CreateUObject(this, &ADemoHeroes::OnGetPlayerHeroesCompleted), PlayerId);
}

void ADemoHeroes::DemoGetInventoryToHero()
{
	ULootLockerServerSDKManager::GetInventoryToHero(FHeroInventoryResponse::CreateUObject(this, &ADemoHeroes::OnGetInventoryToHeroCompleted), PlayerId, HeroId);
}

void ADemoHeroes::DemoGetHeroLoadout()
{
	ULootLockerServerSDKManager::GetHeroLoadout(FHeroLoadoutResponse::CreateUObject(this, &ADemoHeroes::OnGetGetHeroLoadoutCompleted), PlayerId, HeroId);
}

void ADemoHeroes::DemoEquipAssetForHeroLoadout()
{
	ULootLockerServerSDKManager::EquipAssetForHeroLoadout(FEquipHeroResponse::CreateUObject(this, &ADemoHeroes::OnEquipAssetForHeroLoadoutCompleted), PlayerId, HeroId, AssetId);
}

void ADemoHeroes::DemoUnEquipAssetForHeroLoadout()
{
	ULootLockerServerSDKManager::UnequipAssetForHeroLoadout(FUnequipHeroResponse::CreateUObject(this, &ADemoHeroes::OnUnequipAssetForHeroLoadoutCompleted), PlayerId, HeroId, AssetId);
}

void ADemoHeroes::OnGetPlayerHeroesCompleted(FLootLockerServerGetPlayerHeroesResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerHeroes Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerHeroes Failed"));
	}
}

void ADemoHeroes::OnGetInventoryToHeroCompleted(FLootLockerServerHeroInventoryResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetInventoryToHero Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetInventoryToHero Failed"));
	}
}

void ADemoHeroes::OnGetGetHeroLoadoutCompleted(FLootLockerServerGetHeroLoadoutResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetGetHeroLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetGetHeroLoadout Failed"));
	}
}

void ADemoHeroes::OnEquipAssetForHeroLoadoutCompleted(FLootLockerServerEquipHeroResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("EquipAssetForHeroLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("EquipAssetForHeroLoadout Failed"));
	}
}

void ADemoHeroes::OnUnequipAssetForHeroLoadoutCompleted(FLootLockerServerUnequipHeroResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("UnequipAssetForHeroLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("UnequipAssetForHeroLoadout Failed"));
	}
}

