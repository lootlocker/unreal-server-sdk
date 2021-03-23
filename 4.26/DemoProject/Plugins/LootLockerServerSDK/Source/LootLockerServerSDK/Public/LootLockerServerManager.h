// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerCharacterRequest.h"
#include "ServerAPI/LootLockerServerHeroesRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "ServerAPI/LootLockerServerStorageRequest.h"
#include "ServerAPI/LootLockerServerTriggerRequest.h"



#include "LootLockerServerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerManager : public UObject
{
    GENERATED_BODY()
 
public:
    
    //==================================================
    //Authentication
    //==================================================
    
    /**
    * Register a session.
    *
    * @param PlayerId - the ID of the player on the platform the game is currently running on.
    *  https://docs.lootlocker.io/game-api/#authentication-request
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Authentication")
    static void StartSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted);
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Authentication")
    static void MaintainSession(const FServerAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
    * Get all assets in a paginated form.
    *
    * @param StartFromIndex - index of the item to start from.
    * @param ItemsCount - number of items to receive (50-200).
    * @param AssetFilter - optional filter.
    * @param IncludeUGC - whether to include UGC Assets.
    * https://docs.lootlocker.io/server-api/#get-assets-to-game
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets")
    static void GetAssetsToGame(const FServerAssetsResponseDelegateBP& OnGetAssetsRequestCompleted,int StartFromIndex = 0, int ItemsCount = 50, ELootLockerServerAssetFilter AssetFilter = ELootLockerServerAssetFilter::None, bool IncludeUGC = false);

    /**
    * Get a paginated list of the players inventory.
    * https://docs.lootlocker.io/server-api/#get-player-inventory
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void GetInventory(const FInventoryResponseBP& OnGetInventoryRequestCompleted, int PlayerId, int StartFromIndex = 0, int ItemsCount = 50);

    /**
     * Grant an asset to a player as you see fit
     * https://docs.lootlocker.io/server-api/#add-asset-to-player-inventory
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void AddAssetToPlayerInventory(const FAddAssetResponseBP& OnAddAssetRequestCompleted, int32 PlayerId, FLootLockerServerAddAssetData AddAssetData);

	/**
	 * Return the players default characters loadout
	 * https://docs.lootlocker.io/server-api/#get-player-loadout 
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void GetPlayerLoadout(const FGetPlayerLoadoutResponseBP& OnGetPlayerLoadoutRequestCompleted, int PlayerId);

	/**
	 * Equip an asset instance to the players default character
	 * https://docs.lootlocker.io/server-api/#equip-asset-for-player-loadout
	 */ 
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void EquipAssetForPlayerLoadout(const FEquipAssetResponseBP& OnRequestCompleted, int PlayerId, int InstanceId);

	/**
	 * Unequip an asset instance for the players default character
	 * https://docs.lootlocker.io/server-api/#unequip-asset-for-player-loadout
	 */ 
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void UnequipAssetForPlayerLoadout(const FUnequipAssetResponseBP& OnRequestCompleted, int PlayerId, int LoadoutId);

	/**
	 * Read player storage one or more players
	 * https://docs.lootlocker.io/server-api/#player-persistent-storage
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void GetPersistentStorage(const FGetPersistentStorageResponseBP& OnRequestCompleted, TArray<int> PlayerIds);

	/**
	 * Update Persistent Storage
	 * https://docs.lootlocker.io/server-api/#update-persistent-storage
	 */ 
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void UpdatePersistentStorage(const FUpdatePersistentStorageResponseBP& OnCompletedRequest, FLootLockerServerPersistentStorageRequestData RequestData);

	/**
	 * List characters to a player
	 * https://docs.lootlocker.io/server-api/#get-player-characters
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void GetPlayerCharacters(const FCharactersResponseBP& OnCompletedRequestBP, int PlayerId);

	/**
	 * Get the inventory for a specific character belonging to a player
	 * https://docs.lootlocker.io/server-api/#get-inventory-to-character
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void GetInventoryToCharacter(const FCharacterInventoryResponseBP& OnCompletedRequestBP, int PlayerId, int CharacterId);

	/**
	 * Get a characters full loadout.
	 * https://docs.lootlocker.io/server-api/#get-character-loadout
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void GetCharacterLoadout(const FCharacterLoadoutResponseBP& OnCompletedRequestBP, int PlayerId, int CharacterId);

	/**
	 * Equip an asset instance to a specific character
	 * https://docs.lootlocker.io/server-api/#equip-asset-for-character-loadout
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void EquipAssetForCharacterLoadout(const FEquipResponseBP& OnCompletedRequestBP, int PlayerId, int CharacterId, int InstanceId);

	/**
	 * Unequip an asset instance for a character
	 * https://docs.lootlocker.io/server-api/#unequip-asset-for-character-loadout
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void UnequipAssetForCharacterLoadout(const FUnequipResponseBP& OnCompletedRequestBP, int PlayerId, int CharacterId, int InstanceId);

	/**
	 * List heroes to a player
	 * https://docs.lootlocker.io/server-api/#get-player-heroes
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void GetPlayerHeroes(const FHeroesResponseBP& OnCompletedRequestBP, int PlayerId);

	/**
	 * Get the inventory for a specific hero belonging to a player
	 * https://docs.lootlocker.io/server-api/#get-inventory-to-hero
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void GetInventoryToHero(const FHeroInventoryResponseBP& OnCompletedRequestBP, int PlayerId, int HeroId);

	/**
	 * Get a hero full loadout.
	 * https://docs.lootlocker.io/server-api/#get-hero-loadout
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void GetHeroLoadout(const FHeroLoadoutResponseBP& OnCompletedRequestBP, int PlayerId, int HeroId);

	/**
	 * Equip an asset instance to a specific hero
	 * https://docs.lootlocker.io/server-api/#equip-asset-for-hero-loadout
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void EquipAssetForHeroLoadout(const FEquipHeroResponseBP& OnCompletedRequestBP, int PlayerId, int HeroId, int InstanceId);

	/**
	 * Unequip an asset instance for a hero
	 * https://docs.lootlocker.io/server-api/#unequip-asset-for-hero-loadout
	 */
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
    static void UnequipAssetForHeroLoadout(const FUnequipHeroResponseBP& OnCompletedRequestBP, int PlayerId, int HeroId, int InstanceId);

	/**
	 * Invoke a trigger on behalf of a player
	 * https://docs.lootlocker.io/server-api/#invoke-trigger-on-behalf-of-player
	 */ 
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Players")
	static void InvokeTriggerOnBehalfOfPlayer(const FInvokeTriggerResponseBP& OnCompletedRequestBP, FString Name, int PlayerId);
};
