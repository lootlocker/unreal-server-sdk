// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPlayerInventory.h"

#include "LootLockerServerSDKManager.h"

void ADemoPlayerInventory::DemoGetPlayerInventory()
{
	ULootLockerServerSDKManager::GetInventory(FInventoryResponse::CreateUObject(this, &ADemoPlayerInventory::OnGetPlayerInventoryCompleted), PlayerId, StartFromIndex, ItemsCount);
}

void ADemoPlayerInventory::DemoAddAssetToPlayerInventory()
{
	FLootLockerServerAddAssetData Data = FLootLockerServerAddAssetData();
	Data.asset_id = AssetId;
	Data.asset_rental_option_id = AssetRentalOptionId;
	Data.asset_variation_id = AssetVariationId;
	ULootLockerServerSDKManager::AddAssetToPlayerInventory(FAddAssetResponse::CreateUObject(this, &ADemoPlayerInventory::OnAddAssetToPlayerInventoryCompleted), PlayerId, Data);
}

void ADemoPlayerInventory::DemoGetPlayerLoadout()
{
	ULootLockerServerSDKManager::GetPlayerLoadout(FGetPlayerLoadoutResponse::CreateUObject(this, &ADemoPlayerInventory::OnGetPlayerLoadoutCompleted), PlayerId);
}

void ADemoPlayerInventory::DemoEquipAssetForPlayerLoadout()
{
	ULootLockerServerSDKManager::EquipAssetForPlayerLoadout(FEquipAssetResponse::CreateUObject(this, &ADemoPlayerInventory::OnEquipAssetForPlayerLoadoutCompleted), PlayerId, AssetId);
}

void ADemoPlayerInventory::DemoUnEquipAssetForPlayerLoadout()
{
	ULootLockerServerSDKManager::UnequipAssetForPlayerLoadout(FUnequipAssetResponse::CreateUObject(this, &ADemoPlayerInventory::OnUnequipAssetForPlayerLoadoutCompleted), PlayerId, AssetId);
}

void ADemoPlayerInventory::OnGetPlayerInventoryCompleted(FLootLockerServerInventoryResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerInventory Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerInventory Failed"));
	}
}

void ADemoPlayerInventory::OnAddAssetToPlayerInventoryCompleted(FLootLockerServerAddAssetResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("AddAssetToPlayerInventory Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("AddAssetToPlayerInventory Failed"));
	}
}

void ADemoPlayerInventory::OnGetPlayerLoadoutCompleted(FLootLockerServerGetPlayerLoadoutResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerLoadout Failed"));
	}
}

void ADemoPlayerInventory::OnEquipAssetForPlayerLoadoutCompleted(
	FLootLockerServerEquipAssetForPlayerLoadoutResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("EquipAssetForPlayerLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("EquipAssetForPlayerLoadout Failed"));
	}
}

void ADemoPlayerInventory::OnUnequipAssetForPlayerLoadoutCompleted(
	FLootLockerServerUnequipAssetForPlayerLoadoutResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("UnEquipAssetForPlayerLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("UnEquipAssetForPlayerLoadout Failed"));
	}
}
