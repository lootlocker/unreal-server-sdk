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



#include "LootLockerServerSDKManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerSDKManager : public UObject
{
	GENERATED_BODY()

public:
    
    //==================================================
    //Authentication
    //==================================================
    
    /**
     * Register a session.
     * @param PlayerId - the ID of the player on the platform the game is currently running on.
     * @param OnCompletedRequest - callback to be invoked with the server response.
     * https://docs.lootlocker.io/game-api/#authentication-request
     */
	static void StartSession(const FServerAuthResponse& OnCompletedRequest);

    static void MaintainSession(const FServerAuthResponse& OnCompletedRequest);

	/**
	* Get all assets in a paginated form.
	*
	* @param OnCompletedRequest - callback to be invoked with the server response.
	* @param StartFromIndex - index of the item to start from.
	* @param ItemsCount - number of items to receive (50-200).
	* @param AssetFilter - optional filter.
	* @param IncludeUGC - whether to include UGC Assets.
	* https://docs.lootlocker.io/game-api/#getting-asset-list
	*/
	static void GetAssetsToGame(const FServerAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex = 0, int ItemsCount = 50, ELootLockerServerAssetFilter AssetFilter = ELootLockerServerAssetFilter::None, bool IncludeUGC = false);

	/**
	* Get a paginated list of the players inventory.
	* @param OnGetInventoryRequestCompleted - callback to be invoked with the server response
	* @param StartFromIndex - index of the item to start from
	* @param ItemsCount - number of items to receive (50-200)
	* https://docs.lootlocker.io/server-api/#get-player-inventory
	*/
    static void GetInventory(const FInventoryResponse& OnGetInventoryRequestCompleted, int PlayerId, int StartFromIndex = 0, int ItemsCount = 50);

	/**
	 * Grant an asset to a player as you see fit
	 * @param OnAddAssetRequestCompleted - callback to be invoked with the server response
	 * @param PlayerId - Player identifier
	 * @param AddAssetData - Data about the asset to be added
	 * https://docs.lootlocker.io/server-api/#add-asset-to-player-inventory
	 */
	static void AddAssetToPlayerInventory(const FAddAssetResponse& OnAddAssetRequestCompleted, int PlayerId, FLootLockerServerAddAssetData AddAssetData);

	/**
	 * Return the players default characters loadout
	 * @param OnGetPlayerLoadoutRequestCompleted - callback to be invoked with the server response
	 * @param PlayerId - Player identifier
	 * https://docs.lootlocker.io/server-api/#get-player-loadout
	 */ 
	static void GetPlayerLoadout(const FGetPlayerLoadoutResponse& OnGetPlayerLoadoutRequestCompleted, int PlayerId);

	/**
     * Equip an asset instance to the players default character
     * @param OnRequestCompleted - callback to be invoked with the server response
     * @param PlayerId - Player identifier
     * @param InstanceId - Asset id
	 * https://docs.lootlocker.io/server-api/#equip-asset-for-player-loadout
	 */ 
	static void EquipAssetForPlayerLoadout(const FEquipAssetResponse& OnRequestCompleted, int PlayerId, int InstanceId);

	/**
	 * Unequip an asset instance for the players default character
	 * @param OnRequestCompleted - callback to be invoked with the server response
	 * @param PlayerId - Player identifier
	 * @param LoadoutId - Asset id
	 * https://docs.lootlocker.io/server-api/#equip-asset-for-player-loadout
	*/ 
	static void UnequipAssetForPlayerLoadout(const FUnequipAssetResponse& OnRequestCompleted, int PlayerId, int LoadoutId);

	/**
	 * Read player storage one or more players
	 * @param OnRequestCompleted - callback to be invoked with the server response
	 * @param PlayerIds - array of player ids
	 * https://docs.lootlocker.io/server-api/#player-persistent-storage
	 */
	static void GetPersistentStorage(const FGetPersistentStorageResponse& OnRequestCompleted, TArray<int> PlayerIds);

	/**
	 * Update Persistent Storage
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param RequestData - payload
	 * https://docs.lootlocker.io/server-api/#update-persistent-storage
	 */ 
    static void UpdatePersistentStorage(const FUpdatePersistentStorageResponse& OnCompletedRequest, FLootLockerServerPersistentStorageRequestData RequestData);

	/**
	 * List characters to a player
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * https://docs.lootlocker.io/server-api/#get-player-characters
	 */
    static void GetPlayerCharacters(const FCharactersResponse& OnCompletedRequest, int PlayerId);

	/**
	 * Get the inventory for a specific character belonging to a player
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param CharacterId - character identifier
	 * https://docs.lootlocker.io/server-api/#get-inventory-to-character
	 */
    static void GetInventoryToCharacter(const FCharacterInventoryResponse& OnCompletedRequest, int PlayerId, int CharacterId);

	/**
	 * Get a characters full loadout.
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param CharacterId - character identifier 
	 * https://docs.lootlocker.io/server-api/#get-character-loadout
	 */
    static void GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest, int PlayerId, int CharacterId);

	/**
	 * Equip an asset instance to a specific character
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param CharacterId - character identifier 
	 * @param InstanceId - instance identifier 
	 * https://docs.lootlocker.io/server-api/#equip-asset-for-character-loadout
	 */
    static void EquipAssetForCharacterLoadout(const FEquipResponse& OnCompletedRequest, int PlayerId, int CharacterId, int InstanceId);

	/**
	 * Unequip an asset instance for a character
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param CharacterId - character identifier 
	 * @param InstanceId - instance identifier
	 * https://docs.lootlocker.io/server-api/#unequip-asset-for-character-loadout
	 */
    static void UnequipAssetForCharacterLoadout(const FUnequipResponse& OnCompletedRequest, int PlayerId, int CharacterId, int InstanceId);

	/**
	 * List heroes to a player
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * https://docs.lootlocker.io/server-api/#get-player-heroes
	 */
    static void GetPlayerHeroes(const FHeroesResponse& OnCompletedRequest, int PlayerId);

	/**
	 * Get the inventory for a specific hero belonging to a player
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param HeroId - hero identifier
	 * https://docs.lootlocker.io/server-api/#get-inventory-to-hero
	 */
    static void GetInventoryToHero(const FHeroInventoryResponse& OnCompletedRequest, int PlayerId, int HeroId);

	/**
	 * Get a heroes full loadout.
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param HeroId - hero identifier 
	 * https://docs.lootlocker.io/server-api/#get-hero-loadout
	 */
    static void GetHeroLoadout(const FHeroLoadoutResponse& OnCompletedRequest, int PlayerId, int HeroId);

	/**
	 * Equip an asset instance to a specific hero
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param HeroId - hero identifier 
	 * @param InstanceId - instance identifier 
	 * https://docs.lootlocker.io/server-api/#equip-asset-for-hero-loadout
	 */
    static void EquipAssetForHeroLoadout(const FEquipHeroResponse& OnCompletedRequest, int PlayerId, int HeroId, int InstanceId);

	/**
	 * Unequip an asset instance for a hero
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param PlayerId - player identifier
	 * @param HeroId - hero identifier 
	 * @param InstanceId - instance identifier
	 * https://docs.lootlocker.io/server-api/#unequip-asset-for-hero-loadout
	 */
    static void UnequipAssetForHeroLoadout(const FUnequipHeroResponse& OnCompletedRequest, int PlayerId, int HeroId, int InstanceId);

	/**
	 * Invoke a trigger on behalf of a player
	 * @param OnCompletedRequest - callback to be invoked with the server response
	 * @param Name - trigger name 
	 * @param PlayerId - player identifier 
	 * https://docs.lootlocker.io/server-api/#invoke-trigger-on-behalf-of-player
	 */ 
    static void InvokeTriggerOnBehalfOfPlayer(const FInvokeTriggerResponse& OnCompletedRequest, FString Name, int PlayerId);
};
