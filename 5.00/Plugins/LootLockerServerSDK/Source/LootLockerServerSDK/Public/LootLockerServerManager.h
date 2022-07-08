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
#include "ServerAPI/LootLockerServerLeaderboardRequest.h"


#include "LootLockerServerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerManager : public UObject
{
    GENERATED_BODY()
 
public:
	UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Set Configuration")
		static void SetConfig(FString LootLockerServerKey, bool OnDevelopmentMode, FString GameVersion, FString LootLockerVersion);


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
    static void MaintainSession(const FServerPingResponseBP& OnPingRequestCompleted);

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


    //==================================================
    //Leaderboard
    //==================================================

     /**
    * Get rank for single member for a leaderboard. If leaderboard is of type player a player will also be in the response.
    *
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param MemberId - the id of player in the leaderboard
    *
    * https://ref.lootlocker.io/game-api/#get-member-rank
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequestBP);


    /**
   * Get ranks for list of members for a leaderboard. This can be helpful when getting a players friends on leaderboard.
   * If leaderboard is of type player a player will also be in the response.
   * @param Members - the ids of all leaderboard members you need to get info on.
   *
   * https://ref.lootlocker.io/game-api/#get-by-list-of-members
   */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void UpdateLeaderboard(const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequests, int LeaderboardId, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequestBP );

    /**
   * Get list of members in rank range. Result is sorted by rank ascending.
   * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
   * @param LeaderboardId - the id of the leaderboard you need to connect to.
   * @param Count - Number of members returned per page
   * @param After - Curser for pagination, a cursor will be returned in the response
   *
   * https://ref.lootlocker.io/game-api/#get-score-list
   */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void DeleteLeaderboard(int LeaderboardId, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequestBP );

    /**
   * Submit scores for member on leaderboard.
   * @param LeaderboardId - the id of the leaderboard you need to connect to.
   * @param MemberId - the id of player in the leaderboard.
   * @param Score - the score to be submitted.
   *
   * https://ref.lootlocker.io/game-api/#submit-scorem
   */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void SubmitScore(FString MemberId, int LeaderboardId, int Score, const FLootLockerServerSubmitScoreResponseBP& OnCompletedRequestBP);
   // //==================================================
   // //Drop Table
   // //==================================================
   // /**
   // * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
   // * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
   // * @param LeaderboardId - the id of the leaderboard you need to connect to.
   // * @param MemberId - the id of player in the leaderboard.
   // * @param Score - the score to be submitted.
   // *
   // * https://ref.lootlocker.io/game-api/#compute-and-lock-drop-table
   // */
   // UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable")
   // static void ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP);

   // /**
   //* Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
   //* The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
   //* @param LeaderboardId - the id of the leaderboard you need to connect to.
   //* @param MemberId - the id of player in the leaderboard.
   //* @param Score - the score to be submitted.
   //*
   //* https://ref.lootlocker.io/game-api/#pick-drops-from-drop-table
   //*/
   // UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable")
   // static void PickDropsFromDropTable(TArray<int> picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP);
};
