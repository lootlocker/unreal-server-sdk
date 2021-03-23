// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCharacters.h"

#include "LootLockerServerSDKManager.h"

void ADemoCharacters::DemoGetPlayerCharacters()
{
	ULootLockerServerSDKManager::GetPlayerCharacters(FCharactersResponse::CreateUObject(this, &ADemoCharacters::OnGetPlayerCharactersCompleted), PlayerId);
}

void ADemoCharacters::DemoGetInventoryToCharacter()
{
	ULootLockerServerSDKManager::GetInventoryToCharacter(FCharacterInventoryResponse::CreateUObject(this, &ADemoCharacters::OnGetInventoryToCharacterCompleted), PlayerId, CharacterId);
}

void ADemoCharacters::DemoGetCharacterLoadout()
{
	ULootLockerServerSDKManager::GetCharacterLoadout(FCharacterLoadoutResponse::CreateUObject(this, &ADemoCharacters::OnGetGetCharacterLoadoutCompleted), PlayerId, CharacterId);
}

void ADemoCharacters::DemoEquipAssetForCharacterLoadout()
{
	ULootLockerServerSDKManager::EquipAssetForCharacterLoadout(FEquipResponse::CreateUObject(this, &ADemoCharacters::OnEquipAssetForCharacterLoadoutCompleted), PlayerId, CharacterId, AssetId);
}

void ADemoCharacters::DemoUnEquipAssetForCharacterLoadout()
{
	ULootLockerServerSDKManager::UnequipAssetForCharacterLoadout(FUnequipResponse::CreateUObject(this, &ADemoCharacters::OnUnequipAssetForCharacterLoadoutCompleted), PlayerId, CharacterId, AssetId);
}

void ADemoCharacters::OnGetPlayerCharactersCompleted(FLootLockerServerGetPlayerCharactersResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerCharacters Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPlayerCharacters Failed"));
	}
}

void ADemoCharacters::OnGetInventoryToCharacterCompleted(FLootLockerServerCharacterInventoryResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetInventoryToCharacter Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetInventoryToCharacter Failed"));
	}
}

void ADemoCharacters::OnGetGetCharacterLoadoutCompleted(FLootLockerServerGetCharacterLoadoutResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetGetCharacterLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetGetCharacterLoadout Failed"));
	}
}

void ADemoCharacters::OnEquipAssetForCharacterLoadoutCompleted(FLootLockerServerEquipCharacterResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("EquipAssetForCharacterLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("EquipAssetForCharacterLoadout Failed"));
	}
}

void ADemoCharacters::OnUnequipAssetForCharacterLoadoutCompleted(FLootLockerServerUnequipCharacterResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("UnequipAssetForCharacterLoadout Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("UnequipAssetForCharacterLoadout Failed"));
	}
}
