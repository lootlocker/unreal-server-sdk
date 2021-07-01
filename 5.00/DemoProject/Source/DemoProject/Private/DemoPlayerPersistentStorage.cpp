// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPlayerPersistentStorage.h"

#include "LootLockerServerSDKManager.h"

void ADemoPlayerPersistentStorage::DemoGetPersistentStorage()
{
	TArray<int> PlayerIds;
	PlayerIds.Add(PlayerId);
	ULootLockerServerSDKManager::GetPersistentStorage(FGetPersistentStorageResponse::CreateUObject(this, &ADemoPlayerPersistentStorage::OnGetPersistentStorageCompleted), PlayerIds);
}

void ADemoPlayerPersistentStorage::DemoUpdatePersistentStorage()
{
	FLootLockerServerPersistentStorageRequestData RequestData;
	FLootLockerServerPlayerStorageData Payload;
	FLootLockerServerKeyValueSet Set;
	Payload.player_id = PlayerId;
	Set.is_public = IsPublic;
	Set.key = Key;
	Set.value = Value;
	Set.order = Order;
	Payload.sets = {Set};
	RequestData.payload = {Payload};
	
	ULootLockerServerSDKManager::UpdatePersistentStorage(FUpdatePersistentStorageResponse::CreateUObject(this, &ADemoPlayerPersistentStorage::OnUpdatePersistentStorageCompleted), RequestData);
}

void ADemoPlayerPersistentStorage::OnGetPersistentStorageCompleted(
	FLootLockerServerGetPersistentStorageResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPersistentStorage Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("GetPersistentStorage Failed"));
	}
}

void ADemoPlayerPersistentStorage::OnUpdatePersistentStorageCompleted(
	FLootLockerServerUpdatePersistentStorageResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("UpdatePersistentStorage Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("UpdatePersistentStorage Failed"));
	}
}
