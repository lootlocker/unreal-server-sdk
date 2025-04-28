// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerBalanceRequest.h"
#include "ServerAPI/LootLockerServerCharacterProgressionRequest.h"
#include "ServerAPI/LootLockerServerCharacterRequest.h"
#include "ServerAPI/LootLockerServerCurrencyRequest.h"
#include "ServerAPI/LootLockerServerDropTableRequest.h"
#include "ServerAPI/LootLockerServerGameProgressionRequest.h"
#include "ServerAPI/LootLockerServerHeroRequest.h"
#include "ServerAPI/LootLockerServerInstanceProgressionRequest.h"
#include "ServerAPI/LootLockerServerLeaderboardArchiveRequestHandler.h"
#include "ServerAPI/LootLockerServerLeaderboardRequest.h"
#include "ServerAPI/LootLockerServerMetadataRequest.h"
#include "ServerAPI/LootLockerServerOAuthRequest.h"
#include "ServerAPI/LootLockerServerPlayerFileRequest.h"
#include "ServerAPI/LootLockerServerPlayerInventoryRequest.h"
#include "ServerAPI/LootLockerServerPlayerProgressionRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "ServerAPI/LootLockerServerStorageRequest.h"
#include "ServerAPI/LootLockerServerTriggerRequest.h"

#include "LootLockerServerForBlueprints.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerForBlueprints : public UObject
{
    GENERATED_BODY()
 
public:
    //==================================================
    // Authentication https://ref.lootlocker.com/server-api/#authentication
    //==================================================

    /**
     * Start a session connecting to the LootLocker services with the server API key
     * https://ref.lootlocker.com/server-api/#registering-a-server-session
     *
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Authentication")
    static void StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequest);

    /**
     * Keep the session alive, you should call this endpoint at least once per hour, to extend your tokens lifetime.
     * https://ref.lootlocker.com/server-api/#maintaining-a-server-session
     *
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Authentication")
    static void MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequest);

    //==================================================
    // Token Exchange
    //==================================================

    /**
     Get a new active game api session token for the player holding the supplied game api session token

     This will allow the server to make requests to the game api on behalf of the user corresponding to the original token.

     @param GameApiSessionToken The session token for a current game api session to use in exchange for a new one
     @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Token Exchange")
    static void GameApiTokenExchange(const FString& GameApiSessionToken, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest);

    /**
     Get a new active game api session token for the specified player

     This will allow the server to make requests to the game api on behalf of the specified user.

     @param PlayerUlid The ulid of the player you wish to impersonate
     @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Token Exchange")
    static void GameApiUserImpersonation(const FString& PlayerUlid, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest);

    //==================================================
    // Leaderboards https://ref.lootlocker.com/server-api/#leaderboards
    //==================================================
    
    /**
     * Get information about a given leaderboard.
     *
     * @param LeaderboardKey The key of the leaderboard to get information for
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Create a new leaderboard with the provided details.
     * https://ref.lootlocker.com/server-api/#create-leaderboard
     *
     * @param LeaderboardKey Unique key for the leaderboard
     * @param Name Name of the leaderboard
     * @param Type Type of the leaderboard (https://ref.lootlocker.com/server-api/#leaderboard-types)
     * @param HasMetadata Whether the leaderboard has metadata (https://ref.lootlocker.com/server-api/#metadata)
     * @param DirectionMethod Sort order (Ascending or Descending), based on whether highest rank is lowest or highest number
     * @param EnableGameApiWrites Whether the Game API is permitted to write to this leaderboard
     * @param OverwriteScoreOnSubmit Submitting a new score for member will always overwrite their existing score on leaderboard
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Update an existing leaderboard with the provided details.
     * https://ref.lootlocker.com/server-api/#update-leaderboard
     *
     * @param LeaderboardKey The key of the leaderboard to update
     * @param NewLeaderboardKey The unique key to set for the leaderboard, if you do not want to change it then set it to the same as LeaderboardKey
     * @param Name Name of the leaderboard
     * @param DirectionMethod sort order (Ascending or Descending), based on whether highest rank is lowest or highest number
     * @param EnableGameApiWrites Whether the Game API is permitted to write to this leaderboard
     * @param OverwriteScoreOnSubmit Submitting a new score for member will always overwrite their existing score on leaderboard
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Delete an existing leaderboard
     * https://ref.lootlocker.com/server-api/#delete-leaderboard
     *
     * @param LeaderboardKey The key of the leaderboard to delete
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Submit a score to the given leaderboard
     * https://ref.lootlocker.com/server-api/#submit-score
     *
     * @param LeaderboardKey The key of the leaderboard to delete
     * @param MemberID The ID of the member to submit the score for. For player type leaderboards this is the PlayerID, for Generic type leaderboards it can be any string so you need to know what/who you want to submit for.
     * @param Score The score to submit
     * @param Metadata Metadata to add to the score (will only be used if the leaderboard has metadata enabled)
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequest);

    /**
     * For all leaderboards that this member has scores on, get the score, member information, rank, score, and metadata (if metadata is enabled on that leaderboard), as well as player information if the leaderboard is of type player.
     * https://ref.lootlocker.com/server-api/#get-all-member-ranks
     *
     * @param MemberID The ID of the member to get the scores for. For player type leaderboards this is the PlayerID, for Generic type leaderboards it can be any string so you need to know what/who you want to submit for.

     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void GetAllMemberRanks(FString MemberID, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest);

    /**
     * For all leaderboards that this member has scores on, get the score, member information, rank, score, and metadata (if metadata is enabled on that leaderboard), as well as player information if the leaderboard is of type player, using pagination settings.
     * https://ref.lootlocker.com/server-api/#get-all-member-ranks
     * Pagination: https://ref.lootlocker.com/server-api/#pagination
     *
     * @param MemberID The ID of the member to get the scores for. For player type leaderboards this is the PlayerID, for Generic type leaderboards it can be any string so you need to know what/who you want to submit for.
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response

     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void GetPaginatedAllMemberRanks(FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest);

    /**
     * From the requested leaderboard get <count> number of scores. The list of scores has member information, rank, score, and metadata (if metadata is enabled on that leaderboard) for the given leaderboard. If leaderboard is of type player a player will also be in the response.
     * Results are sorted in ascending order.
     * https://ref.lootlocker.com/server-api/#get-score-list
     *
     * @param LeaderboardKey The key of the leaderboard you want to connect to.
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void GetScoresFromLeaderboard(FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest);

    /**
     * From the requested leaderboard get <count> number of scores. The list of scores has member information, rank, score, and metadata (if metadata is enabled on that leaderboard) for the given leaderboard. If leaderboard is of type player a player will also be in the response, using pagination settings.
     * Results are sorted in ascending order.
     * Maximum allowed scores to query for at a time is currently 2000.
     * https://ref.lootlocker.com/server-api/#get-score-list
     * Pagination: https://ref.lootlocker.com/server-api/#pagination
     *
     * @param LeaderboardKey The key of the leaderboard you want to connect to.
     * @param Count Number of scores returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static void GetPaginatedScoresFromLeaderboard(FString LeaderboardKey, int Count, int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest);

    /**
    * Get the schedule for the specified leaderboard
    * @param LeaderboardKey The Key of the leaderboard for which to fetch the schedule
    * @param OnCompletedRequestBP Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequestBP);
    
    /**
    * Set the provided schedule for the specified leaderboard
    * NOTE: Cron expressions are used for setting up the schedule. These expressions follow the traditional cron spec.
    * See crontab.guru for a good resource in exploring cron expressions.
    * Additionally, we do support non-standard descriptors as follows:
    *     - @hourly: every hour at minute 00.
    *     - @daily: everyday, at midnight UTC.
    *     - @weekly: on Sunday, at midnight UTC.
    *     - @monthly: on the first day of the month, at midnight UTC.
    *     - @yearly: on the first day of the year, at midnight UTC.
    * @param Key The Key of the leaderboard for which to set the schedule
    * @param CronExpression The cron expression describing the schedule to set
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest);
    
    /**
    * Remove the schedule (if any) from the specified leadeboard
    * @param Key the Key of the leaderboard for which to remove the schedule
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseBP& OnCompletedRequest);

    //==================================================
    // Leaderboard Archives
    //==================================================

    /**
    * List the archive of a specific Leaderboard,
    * @param LeaderboardKey The Key of the Leaderboard you want the list of archives
    * @param OnCompletedRequestBP Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static void ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseBP& OnCompletedRequestBP);

    /**
    * Get the specified Archive which includes details such as ranks, scores and rewards.
    * @param Key the Key of the leaderboard archive entry you want to fetch details for
    * @param Count Optional: The count of items you want to retrieve.
    * @param After Optional: Used for pagination, id from which the pagination starts from.
    * @param OnCompletedRequestBP Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard", meta = (AdvancedDisplay = "Count,After", Count = -1, After = ""))
    static void GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP);

    //==================================================
    // Triggers https://ref.lootlocker.com/server-api/#triggers
    //==================================================

    /**
     * Trigger the requested trigger on behalf of the provided player
     * https://ref.lootlocker.com/server-api/#invoke-trigger-on-behalf-of-player
     *
     * To see the configured triggers for your game, go here: https://console.lootlocker.com/triggers
     *
     * @param TriggerName The name of the trigger to invoke for the provided player
     * @param PlayerID The ID of the player to invoke the trigger for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Triggers")
    static void InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseBP& OnCompletedRequest);

    //==================================================
    // Player Persistent Storage https://ref.lootlocker.com/server-api/#player-persistent-storage
    //==================================================

    /**
     * Get the persistent storage for the provided player
     * https://ref.lootlocker.com/server-api/#get-persistent-storage
     *
     * @param PlayerID The ID of the player to fetch the persistent storage for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static void GetPersistentStorageForPlayer(int PlayerID, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest);

    /**
     * Get the persistent storage for all the player ids provided
     * https://ref.lootlocker.com/server-api/#get-persistent-storage
     *
     * @param PlayerIDs The IDs of the players to fetch the persistent storage for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static void GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest);

    /**
     * Get all the public (if any) persistent storage for the provided players
     * https://ref.lootlocker.com/server-api/#get-multiple-players-public-persistent-storage-values
     *
     * @param PlayerIDs The IDs of the players to fetch the persistent storage for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static void GetEntirePublicPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);

    /**
     * Get all the public (if any) persistent storage for the provided players, but filter the list by the provided keys
     * https://ref.lootlocker.com/server-api/#get-multiple-players-public-persistent-storage-values
     *
     * @param PlayerIDs The IDs of the players to fetch the persistent storage for
     * @param Keys The keys to filter the persistent storage by, if empty all keys will be returned.
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static void GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);

    /**
     * Update the persistent storage for the provided player according to the objects provided
     * https://ref.lootlocker.com/server-api/#update-persistent-storage
     *
     * @param StorageEntriesToUpdate The data to update the persistent storage with
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static void UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);

    /**
     * Delete the persistent storage for the provided keys on the provided players
     * If the request fails you will be given an error message. We recommend you make a get request on the players and keys to see what keys failed to delete.
     * https://ref.lootlocker.com/server-api/#delete-persistent-storage
     *
     * @param PlayerIDs The IDs of the players for whom to apply the delete
     * @param Keys The keys to delete for the provided players
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static void DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);
    
    //==================================================
    // Characters https://ref.lootlocker.com/server-api/#characters-and-heroes
    //==================================================
    
    /**
     * List all characters for this player.
     * If your game uses heroes the characters underlaying the heroes will be listed too.
     * https://ref.lootlocker.com/server-api/#get-player-characters
     *
     * @param PlayerID The ID of the player for whom to get the characters
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseBP& OnCompletedRequest);
    
    /**
     * Get the inventory for the specified player and character
     * https://ref.lootlocker.com/server-api/#get-inventory-to-character
     *
     * @param PlayerID The ID of the player for whom to get the character inventory
     * @param CharacterID The ID of the character on the specified player for which to get the inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get a subset of the inventory for the specified player and character using pagination settings
     * https://ref.lootlocker.com/server-api/#get-inventory-to-character
     * Pagination: https://ref.lootlocker.com/server-api/#pagination
     *
     * @param PlayerID The ID of the player for whom to get the character inventory
     * @param CharacterID The ID of the character on the specified player for which to get the inventory
     * @param Count The number of inventory items to get. Must be a value between 1 and 200
     * @param After The id of the inventory item from where to start getting inventory items (non inclusive). Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the full loadout for the specified player and character
     * https://ref.lootlocker.com/server-api/#get-character-loadout
     *
     * @param PlayerID The ID of the player for whom to get the character loadout
     * @param CharacterID The ID of the character on the specified player for which to get the loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and character using an asset instance id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-character-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to equip the asset instance
     * @param AssetInstanceID The ID of the asset instance to equip to the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and character using an asset id and an asset variation id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-character-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player character's loadout
     * @param AssetVariationID The ID of the variation of the specified asset to equip to the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and character using an asset id and a rental option id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-character-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player character's loadout
     * @param RentalOptionID The ID of the rental option of the specified asset to equip to the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest);
    /**
     * Unequip an asset instance from the loadout of specified player and character using the instance id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-character-loadout
     *
     * @param PlayerID The ID of the player for whom to unequip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to unequip the asset instance
     * @param InstanceID The ID of the asset instance to unequip from the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static void UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP& OnCompletedRequest);
    
    //==================================================
    // Heroes https://ref.lootlocker.com/server-api/#characters-and-heroes
    //==================================================
    
    /**
     * List all heroes for this player.
     * https://ref.lootlocker.com/server-api/#get-player-heroes
     *
     * @param PlayerID The ID of the player for whom to get the heroes
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseBP& OnCompletedRequest);
    
    /**
     * Get the inventory for the specified player and hero
     * https://ref.lootlocker.com/server-api/#get-inventory-to-hero
     *
     * @param PlayerID The ID of the player for whom to get the hero inventory
     * @param HeroID The ID of the hero on the specified player for which to get the inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get a subset of the inventory for the specified player and hero using pagination settings
     * https://ref.lootlocker.com/server-api/#get-inventory-to-hero
     * Pagination: https://ref.lootlocker.com/server-api/#pagination
     *
     * @param PlayerID The ID of the player for whom to get the hero inventory
     * @param HeroID The ID of the hero on the specified player for which to get the inventory
     * @param Count The number of inventory items to get. Must be a value between 1 and 200
     * @param After The id of the inventory item from where to start getting inventory items (non inclusive). Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the full loadout for the specified player and hero
     * https://ref.lootlocker.com/server-api/#get-hero-loadout
     *
     * @param PlayerID The ID of the player for whom to get the hero loadout
     * @param HeroID The ID of the hero on the specified player for which to get the loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and hero using an asset instance id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-hero-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to equip the asset instance
     * @param AssetInstanceID The ID of the asset instance to equip to the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and hero using an asset id and an asset variation id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-hero-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player hero's loadout
     * @param AssetVariationID The ID of the variation of the specified asset to equip to the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and hero using an asset id and a rental option id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-hero-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player hero's loadout
     * @param RentalOptionID The ID of the rental option of the specified asset to equip to the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest);
    /**
     * Unequip an asset instance from the loadout of specified player and hero using the instance id
     * https://ref.lootlocker.com/server-api/#equip-asset-for-hero-loadout
     *
     * @param PlayerID The ID of the player for whom to unequip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to unequip the asset instance
     * @param InstanceID The ID of the asset instance to unequip from the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static void UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP& OnCompletedRequest);

    //==================================================
    // Player Inventory https://ref.lootlocker.com/server-api/#player-inventory
    //==================================================
    
    /**
     * Get a list of assets that are available for all player's in the game
     * https://ref.lootlocker.com/server-api/#get-universal-inventory-global-assets
     *
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the specified player's default character's inventory
     * https://ref.lootlocker.com/server-api/#get-player-inventory
     *
     * @param PlayerID The ID of the player for whom to get the inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the specified player's default character's inventory according to the specified pagination parameters
     * https://ref.lootlocker.com/server-api/#get-player-inventory
     * Pagination: https://ref.lootlocker.com/server-api/#pagination
     *
     * @param PlayerID The ID of the player for whom to get the inventory
     * @param Count The number of inventory items to get. Must be a value between 1 and 200
     * @param After The id of the inventory item from where to start getting inventory items (non inclusive). Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the specified player's default character's loadout
     * https://ref.lootlocker.com/server-api/#get-player-loadout
     *
     * @param PlayerID The ID of the player for whom to get the loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the specified player's default character's loadout using an asset id which will equip that asset's default variation
     * If the request is successfull, the returned list contains the full loadout
     * https://ref.lootlocker.com/server-api/#equip-asset-for-player-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetID The ID of the asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip the specified asset instance to the specified player's default character's loadout
     * If the request is successfull, the returned list contains the full loadout
     * https://ref.lootlocker.com/server-api/#equip-asset-for-player-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetInstanceID The Instance ID of the asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the specified player's default character's loadout by specifiying an asset id and which variation id of the asset to equip
     * If the request is successfull, the returned list contains the full loadout
     * https://ref.lootlocker.com/server-api/#equip-asset-for-player-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetID The ID of the asset to equip to the specified player's loadout
     * @param AssetVariationID The ID of the variation of the specified asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the specified player's default character's loadout by specyfiying an asset id and which rental option id of the asset to equip
     * If the request is successfull, the returned list contains the full loadout
     * https://ref.lootlocker.com/server-api/#equip-asset-for-player-loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetID The ID of the asset to equip to the specified player's loadout
     * @param RentalOptionID The ID of the rental option of the specified asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Unequip an asset instance from the specified player's default character's loadout
     * If the request is successfull, the returned list contains the full loadout
     * https://ref.lootlocker.com/server-api/#unequip-asset-for-player-loadout
     *
     * @param PlayerID The ID of the player for whom to unequip the asset
     * @param InstanceID The Instance ID of the asset in the specified player's loadout to unequip
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Add the specified asset to the specified player's inventory (grant the asset) using an asset id which will equip that asset's default variation
     * If the request is successfull, the returned list contains all assets that were granted to the player
     * https://ref.lootlocker.com/server-api/#add-asset-to-player-inventory
     *
     * @param PlayerID The ID of the player for whom to add the asset
     * @param AssetID The ID of the asset to add to the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Add the specified asset to the specified player's inventory (grant the asset) by specifiying an asset id and which variation id of the asset to equip
     * If the request is successfull, the returned list contains all assets that were granted to the player
     * https://ref.lootlocker.com/server-api/#add-asset-to-player-inventory
     *
     * @param PlayerID The ID of the player for whom to add the asset
     * @param AssetID The ID of the asset to add to the specified player's inventory
     * @param VariationID The ID of the specific variation of the specified asset to add to the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Add the specified asset to the specified player's inventory (grant the asset) by specyfiying an asset id and which rental option id of the asset to equip
     * If the request is successfull, the returned list contains all assets that were granted to the player
     * https://ref.lootlocker.com/server-api/#add-asset-to-player-inventory
     *
     * @param PlayerID The ID of the player for whom to add the asset
     * @param AssetID The ID of the asset to add to the specified player's inventory
     * @param RentalOptionID The ID of the specific rental option of the specified asset to add to the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Bulk add (grant) and/or remove assets to/from the specified player's inventory
     * Add assets by supplying a list of asset id's for which the default variation will be used
     * If the request is successfull, the return will contain two lists; one specifying the id's of all the assets that were removed, one specifying all added assets
     * https://ref.lootlocker.com/server-api/#alter-player-inventory
     *
     * @param PlayerID The ID of the player for whom to alter the inventory
     * @param AssetsToAdd A list of assets to add to the specified player's inventory
     * @param AssetsToRemove A list of asset instance id's of assets to remove from the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Bulk add (grant) and/or remove assets to/from the specified player's inventory
     * Add assets by supplying a list of asset ids and variation ids of those assets to use
     * If the request is successfull, the return will contain two lists; one specifying the id's of all the assets that were removed, one specifying all added assets
     * https://ref.lootlocker.com/server-api/#alter-player-inventory
     *
     * @param PlayerID The ID of the player for whom to alter the inventory
     * @param AssetsToAdd A list of assets to add to the specified player's inventory
     * @param AssetsToRemove A list of asset instance id's of assets to remove from the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Bulk add (grant) and/or remove assets to/from the specified player's inventory
     * Add assets by supplying a list of asset ids and rental option ids of those assets to use
     * If the request is successfull, the return will contain two lists; one specifying the id's of all the assets that were removed, one specifying all added assets
     * https://ref.lootlocker.com/server-api/#alter-player-inventory
     *
     * @param PlayerID The ID of the player for whom to alter the inventory
     * @param AssetsToAdd A list of assets to add to the specified player's inventory
     * @param AssetsToRemove A list of asset instance id's of assets to remove from the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static void AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest);

    //==================================================
    // Assets https://ref.lootlocker.com/server-api/#assets
    //==================================================

    /**
     * List all the assets from this game
     * Note that this is a paginated call and it will likely require multiple calls to LootLocker with a parameter for every call except the first to step forward in the results.
     * Up to 200 (the default limit is 50 though) assets are returned at a time, and to fetch the next page you have to use the largest ID you've gotten returned in the previous response
     * https://ref.lootlocker.com/server-api/#get-assets-to-game
     *
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets")
    static void GetAssets(const FLootLockerServerGetAssetsResponseBP& OnCompletedRequest);

    /**
     * List a set of assets from this game according to the supplied pagination options
     * https://ref.lootlocker.com/server-api/#get-assets-to-game
     * Note that this is a paginated call and it will likely require multiple calls to LootLocker with a parameter for every call except the first to step forward in the results.
     * Up to 200 (the default limit is 50 though) assets are returned at a time, and to fetch the next page you have to use the largest ID you've gotten returned in the previous response
     * https://ref.lootlocker.com/server-api/#pagination
     *
     * @param Count The number of assets to get. Must be a value between 1 and 200
     * @param After The id of the asset from where to start getting assets (non inclusive). Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets")
    static void GetPaginatedAssets(int Count, int After, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequest);

    /**
     * Get all assets for a context.
     * https://ref.lootlocker.com/server-api/#get-assets-to-game
     *
     * @param Count The number of assets to get. Must be a value between 1 and 200
     * @param After The id of the asset from where to start getting assets (non inclusive). Set to 0 to start from the first item
     * @param Context The context id to filter by
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets")
    static void GetAssetsByContext(int Count, int After, int Context, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequest);

    //==================================================
    // Asset Instances https://ref.lootlocker.com/server-api/#asset-instances
    //==================================================

    /**
     * Get a list of key value pairs from the specified asset instance
     * https://ref.lootlocker.com/server-api/#getting-all-key-value-pairs-to-an-instance
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static void GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    /**
     * Get a single Key Value Pair from the specified asset instance by key value pair id
     * https://ref.lootlocker.com/server-api/#getting-a-key-value-pair-by-id
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The ID of the asset instance on this player for which to complete the operation
     * @param KeyValuePairID The ID of the specific key value pair to get
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static void GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest);

    /**
     * Create a key value pair on the specified asset instance
     * https://ref.lootlocker.com/server-api/#creating-a-key-value-pair
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param Key The key to add
     * @param Value The value to set for the added key
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static void AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    /**
     * Create or update a list of key value pairs on the specified asset instance
     * https://ref.lootlocker.com/server-api/#updating-one-or-more-key-value-pairs
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param KeyValuePairs A list of key value pairs to update
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static void UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    /**
     * Update a single key value pair on the specified asset instance by key value pair id
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param KeyValuePairID The ID of the specific key value pair to update
     * @param Key The key to set for the key value pair
     * @param Value The value to set for the updated key
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static void UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest);

    /**
     * Delete a key value pair from the specified asset instance by key value pair id
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param KeyValuePairID The ID of the specific key value pair to delete
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static void DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    //==================================================
    // Drop Tables https://ref.lootlocker.com/server-api/#drop-tables
    //==================================================
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory
     * https://ref.lootlocker.com/server-api/#compute-and-lock-drop-table
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static void ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory, but only use items with the specified tag
     * https://ref.lootlocker.com/server-api/#compute-and-lock-drop-table
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param Tag Which tag to limit drop table computation to
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static void ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory and include the full asset information in the response
     * https://ref.lootlocker.com/server-api/#compute-and-lock-drop-table
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static void ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory, but only use items with the specified tag and include the full asset information in the response
     * https://ref.lootlocker.com/server-api/#compute-and-lock-drop-table
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param Tag Which tag to limit drop table computation to
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static void ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);

    /**
     * Pick drop table items from the specified drop table and player
     * https://ref.lootlocker.com/server-api/#pick-drops-from-drop-table
     *
     * @param PlayerID The id of the player for whom the drop table applies
     * @param DropTableID The id of the drop table from which to pick items
     * @param DropTableItemIDsToPick A list of drop table item ids to pick
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static void PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseBP& OnCompletedRequest);

    //==================================================
    // Player https://ref.lootlocker.com/server-api/#player-names
    //==================================================

    /**
     * Lookup a number of player names from the player's id
     *
     * @param IdsToLookUp A list of ids to lookup also specyfying for each id which type of id it is
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player")
    static void LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequest);

    /**
     * Lookup players by their game session tokens
     * Use this to verify in the server that the client player is who they say they are
     *
     * @param GameSessionTokensToLookUp A list of game session tokens to lookup
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player")
    static void GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequest);

    //==================================================
    // Player Files https://ref.lootlocker.com/server-api/#player-files
    //==================================================

    /**
     * List files currently associated with the specified player
     *
     * @param PlayerID ID of the player for whom to list files
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static void ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseBP& OnCompletedRequest);

    /**
     * Get the specified file currently associated with the specified player
     *
     * @param PlayerID ID of the player for whom to get the specified file
     * @param FileID ID of the file to get
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static void GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    /**
     * Delete the specified file currently associated with the specified player
     * The response will be empty unless there's an error
     *
     * @param PlayerID ID of the player for whom to delete the specified file
     * @param FileID ID of the file to delete
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static void DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseBP& OnCompletedRequest);

    /**
     * Upload the specified file to the specified player
     * Each file can be a maximum of 5MB and each player can have a maximum of 50 files
     *
     * @param PlayerID ID of the player for whom to upload the specified file
     * @param FilePath The path on disk to the file you want to upload
     * @param Purpose A tag specifying the purpose of this file
     * @param IsPublic Whether this file is publically available (accessible for other players)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static void UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    /**
     * Upload the supplied raw data as a file to the specified player
     * Each file can be a maximum of 5MB and each player can have a maximum of 50 files
     *
     * @param PlayerID ID of the player for whom to upload the specified file
     * @param RawData The raw data to upload to a player file
     * @param FileName The name to set for the file
     * @param Purpose A tag specifying the purpose of this file
     * @param IsPublic Whether this file is publically available (accessible for other players)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static void UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    /**
     * Update the specified file for the specified player with the supplied file content
     *
     * @param PlayerID ID of the player for whom to update the specified file
     * @param FileID ID of the file to update
     * @param FilePath The path on disk to the file you want to update the specified file with
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static void UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    /**
     * Update the specified file for the specified player with the supplied raw data
     *
     * @param PlayerID ID of the player for whom to update the specified file
     * @param FileID ID of the file to update
     * @param RawData The raw data to update the specified file with
     * @param FileName The name to set for the file
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static void UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    //==================================================
    // Game Progressions https://ref.lootlocker.com/server-api/#progressions
    //==================================================

    /**
     * Get a list of progressions for the game
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedProgressions
     * https://ref.lootlocker.com/server-api/#get-all-progressions
     *
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static void GetProgressions(const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a list of progressions for the game using pagination settings
     * https://ref.lootlocker.com/server-api/#get-all-progressions
     *
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static void GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get the specified progression
     * https://ref.lootlocker.com/server-api/#get-progression-by-key
     *
     * @param ProgressionKey The key of the progression you want to get
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static void GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseBP& OnCompletedRequest);

    /**
     * Get a list of tiers for the specified progression
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedTiersForProgression
     * https://ref.lootlocker.com/server-api/#get-progressions-tiers
     *
     * @param ProgressionKey The key of the progression for which you want to get the tiers
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static void GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest);

    /**
     * Get a list of tiers for the specified progression using pagination settings
     * https://ref.lootlocker.com/server-api/#get-progressions-tiers
     *
     * @param ProgressionKey The key of the progression for which you want to get the tiers
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The tier step (non inclusive) to start getting tiers from. Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static void GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest);

    //==================================================
    // Player Progressions https://ref.lootlocker.com/server-api/#player-progressions
    //==================================================

    /**
     * Get a list of progressions for the specified player
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedProgressionsForPlayer
     * https://ref.lootlocker.com/server-api/#get-player-progressions
     *
     * @param PlayerID ID of the player for whom to get progressions
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static void GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a list of progressions for the specified player
     * https://ref.lootlocker.com/server-api/#get-player-progressions
     *
     * @param PlayerID ID of the player for whom to get progressions
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static void GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a specific progression for the specified player
     * https://ref.lootlocker.com/server-api/#get-player-progression-by-key
     *
     * @param PlayerID ID of the player for whom to get the specified progression
     * @param ProgressionKey Key of the progression to get
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static void GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseBP& OnCompletedRequest);

    /**
     * Add points to the specified progression for the specified player
     * https://ref.lootlocker.com/server-api/#add-points-to-a-player-progression
     *
     * @param PlayerID ID of the player for whom to add points to the specified progression
     * @param ProgressionKey Key of the progression to add points to for the specified player
     * @param Amount The number of points to add to the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static void AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Subtract points from the specified progression for the specified player
     * https://ref.lootlocker.com/server-api/#subtract-points-from-a-player-progression
     *
     * @param PlayerID ID of the player for whom to subtract points from the specified progression
     * @param ProgressionKey Key of the progression to subtract points from for the specified player
     * @param Amount The number of points to subtract from the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static void SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Reset the specified progression for the specified player
     * https://ref.lootlocker.com/server-api/#reset-a-player-progression
     *
     * @param PlayerID ID of the player for whom to reset the specified progression
     * @param ProgressionKey Key of the progression to reset for the specified player
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static void ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Delete the specified progression for the specified player
     * https://ref.lootlocker.com/server-api/#delete-a-player-progression
     *
     * @param PlayerID ID of the player for whom to delete the specified progression
     * @param ProgressionKey Key of the progression to delete for the specified player
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static void DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequest);

    //==================================================
    // Character Progressions https://ref.lootlocker.com/server-api/#character-progressions
    //==================================================

    /**
     * Get a list of progressions for the specified player and character
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedProgressionsForCharacter
     * https://ref.lootlocker.com/server-api/#get-character-progressions
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to get progressions
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static void GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a list of progressions for the specified player and character
     * https://ref.lootlocker.com/server-api/#get-character-progressions
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to get progressions
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static void GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a specific progression for the specified player and character
     * https://ref.lootlocker.com/server-api/#get-character-progression-by-key
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to get the specified progression
     * @param ProgressionKey Key of the progression to get
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static void GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseBP& OnCompletedRequest);

    /**
     * Add points to the specified progression for the specified player and character
     * https://ref.lootlocker.com/server-api/#add-points-to-a-character-progression
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to add points to the specified progression
     * @param ProgressionKey Key of the progression to add points to for the specified player and character
     * @param Amount The number of points to add to the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static void AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Subtract points from the specified progression for the specified player and character
     * https://ref.lootlocker.com/server-api/#subtract-points-from-a-character-progression
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to subtract points from the specified progression
     * @param ProgressionKey Key of the progression to subtract points from for the specified player and character
     * @param Amount The number of points to subtract from the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static void SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Reset the specified progression for the specified player and character
     * https://ref.lootlocker.com/server-api/#reset-a-character-progression
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to reset the specified progression
     * @param ProgressionKey Key of the progression to reset for the specified player and character
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static void ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Delete the specified progression for the specified player and character
     * https://ref.lootlocker.com/server-api/#delete-a-character-progression
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to delete the specified progression
     * @param ProgressionKey Key of the progression to delete for the specified player and character
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static void DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseBP& OnCompletedRequest);

    //==================================================
    // Instance Progressions https://ref.lootlocker.com/server-api/#asset-instance-progressions
    //==================================================

     /**
     * Get a list of progressions for the specified instance
     * The list will contain the first 20 items, if you want to get more items or list items from somewhere else than the beginning; use GetPaginatedProgressionsForInstance
     * https://ref.lootlocker.com/server-api/#get-asset-instance-progressions
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static void GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP);

     /**
     * Get a list of progressions for the specified instance
     * https://ref.lootlocker.com/server-api/#get-asset-instance-progressions
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static void GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP);

     /**
     * Get a specific progression for the specified instance
     * https://ref.lootlocker.com/server-api/#get-asset-instance-progression-by-key
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param ProgressionKey Key of the progression to get
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static void GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseBP& OnCompletedRequestBP);

    /**
    * Add points to the specified progression for the specified instance
    * https://ref.lootlocker.com/server-api/#add-points-to-an-asset-instance-progression
    *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
    * @param ProgressionKey Key of the progression to add points to for the specified instance
    * @param Amount The number of points to add to the specified progression (only positive integers allowed)
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static void AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);
    
    /**
    * Subtract points from the specified progression for the specified instance
    * https://ref.lootlocker.com/server-api/#subtract-points-from-an-asset-instance-progression
    *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
    * @param ProgressionKey Key of the progression to subtract points from for the specified instance
    * @param Amount The number of points to subtract from the specified progression (only positive integers allowed)
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static void SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
     * Reset the specified progression for the specified instance
     * https://ref.lootlocker.com/server-api/#reset-an-asset-instance-progression
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param ProgressionKey Key of the progression to reset for the specified instance
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static void ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
    * Delete the specified progression for the specified instance
    * https://ref.lootlocker.com/server-api/#delete-an-asset-instance-progression
    *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
    * @param ProgressionKey Key of the progression to delete for the specified instance
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static void DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseBP& OnCompletedRequestBP);

    //==================================================
    // Currencies
    // https://ref.lootlocker.com/server-api/#currencies
    //==================================================

    /**
     * Get a list of available currencies for the game
     *
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Currency")
    static void ListCurrencies(const FLootLockerServerListCurrenciesResponseBP& OnCompletedRequest);

    //==================================================
    // Balances
    // https://ref.lootlocker.com/server-api/#balances
    //==================================================

    /**
     * Get a list of balances in a specified wallet
     *
     * @param WalletID Unique ID of the wallet to get balances for
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static void ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseBP& OnComplete);

    /**
     * Get information about a specified wallet
     *
     * @param WalletID Unique ID of the wallet to get information for
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static void GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseBP& OnComplete);

    /**
     * Get information about a wallet for a specified holder
     *
     * @param HolderULID ULID of the holder of the wallet you want to get information for
     * @param HolderType The type of the holder to get the wallet for
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static void GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseBP& OnComplete);

    /**
     * Credit (increase) the specified amount of the provided currency to the provided wallet
     *
     * @param WalletID Unique ID of the wallet to credit the given amount of the given currency to
     * @param CurrencyID Unique ID of the currency to credit
     * @param Amount The amount of the given currency to credit to the given wallet
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static void CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseBP& OnComplete);

    /**
     * Debit (decrease) the specified amount of the provided currency to the provided wallet
     *
     * @param WalletID Unique ID of the wallet to debit the given amount of the given currency from
     * @param CurrencyID Unique ID of the currency to debit
     * @param Amount The amount of the given currency to debit from the given wallet
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static void DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseBP& OnComplete);

    //==================================================
    // Metadata
    //==================================================

    /**
    List the requested page of Metadata for the specified source with the specified pagination (if you don't specify pagination settings then default pagination will be used)

    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata
    @param Page Optional: Used together with PerPage to apply pagination to this request. Page designates which "page" of items to fetch
    @param PerPage Optional: Used together with Page to apply pagination to this request.PerPage designates how many items are considered a "page"
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Page,PerPage,IgnoreFiles", Page = -1, PerPage = -1, IgnoreFiles = false))
    static void ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete);

    /**
    List the requested page of Metadata for the specified source that has all of the provided tags and paginate according to the supplied pagination settings (if you don't specify pagination settings then default pagination will be used)

    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata
    @param Tags The tags that the requested metadata should have, only metadata matching *all of* the given tags will be returned
    @param Page Optional: Used together with PerPage to apply pagination to this request. Page designates which "page" of items to fetch
    @param PerPage Optional: Used together with Page to apply pagination to this request.PerPage designates how many items are considered a "page"
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Page,PerPage,Tags,IgnoreFiles", Page = -1, PerPage = -1, IgnoreFiles = false))
    static void ListMetadataWithTags(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete);

    /**
    Get Metadata for the specified source with the given key

    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata
    @param Key The key of the metadata to fetch, use this to fetch metadata for a specific key for the specified source.
    @param OnComplete delegate for handling the server response
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "IgnoreFiles", IgnoreFiles = false))
    static void GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerServerGetMetadataResponseBP& OnComplete);

    /**
    Get Metadata for the specified keys on the specified sources

    @param SourcesAndKeysToGet The combination of sources to get keys for, and the keys to get for those sources
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "IgnoreFiles", IgnoreFiles = false))
    static void GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerServerGetMultisourceMetadataResponseBP& OnComplete);

    /*
     Parse a LootLockerServer Metadata Entry

     This is a convenience node that replaces switching on the metadata type and converting the values manually
     The output execution pin corresponding to the Entry Type will be triggered at which point the corresponding value pin for that type will be populated.
     If the entry could not be parsed, the OnError execution pin will be triggered and the ErrorMessage will be populated.

     @param Entry The entry to parse
     @param MetadataTypeSwitch Generated output execution pins for the possible metadata types
     @param StringValue The parsed String Value, populated if the OnString output pin was triggered
     @param IntegerValue The parsed integer Value, populated if the OnInteger output pin was triggered
     @param FloatValue The parsed decimal Value, populated if the OnFloat output pin was triggered
     @param NumberString The parsed Number String Value, populated if the OnNumber output pin was triggered
     @param BoolValue The parsed boolean Value, populated if the OnBool output pin was triggered
     @param JsonStringValue The parsed Json String Value, populated if the OnJsonString output pin was triggered
     @param Base64Value The parsed Base64 Value, populated if the OnBase64 output pin was triggered
     @param ErrorMessage An error message populated if the parsing failed and the OnError output pin was triggered
     @param OutEntry Outputs a reference to the entry that was parsed for convenience
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (ExpandEnumAsExecs = "MetadataTypeSwitch", AdvancedDisplay = "OutEntry"))
    static void ParseLootLockerServerMetadataEntry(const FLootLockerServerMetadataEntry& Entry,
                                                   ELootLockerServerMetadataParserOutputTypes& MetadataTypeSwitch,
                                                   FString& StringValue,
                                                   int& IntegerValue,
                                                   float& FloatValue,
                                                   FString& NumberString,
                                                   bool& BoolValue,
                                                   FString& JsonStringValue,
                                                   FLootLockerServerMetadataBase64Value& Base64Value,
                                                   FString& ErrorMessage,
                                                   FLootLockerServerMetadataEntry& OutEntry);

    /**
    Set the provided metadata for the specified source

    Use the provided Make<type>MetadataAction when constructing the array of actions to perform.
    Note that a subset of the specified operations can fail without the full request failing. Make sure to check the errors array in the response.

    @param Source The source type for which to set metadata
    @param SourceID The specific source id for which to set metadata
    @param MetadataToActionsToPerform List of actions to take during this set operation.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata")
    static void SetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerServerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerServerSetMetadataResponseBP& OnComplete);

    /**
    Construct a Metadata Action consisting of a metadata entry with a String value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read", "game_api.write" and "player.read"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm="Tags,Access"))
    static FLootLockerServerSetMetadataAction MakeMetadataActionString(ELootLockerServerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Decimal value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read", "game_api.write" and "player.read"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerServerSetMetadataAction MakeMetadataActionFloat(ELootLockerServerMetadataActions Action, const FString& Key, const float& Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with an Integer value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read", "game_api.write" and "player.read"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerServerSetMetadataAction MakeMetadataActionInteger(ELootLockerServerMetadataActions Action, const FString& Key, const int Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Bool value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read", "game_api.write" and "player.read"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerServerSetMetadataAction MakeMetadataActionBool(ELootLockerServerMetadataActions Action, const FString& Key, const bool Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Json value in string format

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read", "game_api.write" and "player.read"
    @param Succeeded Output: True if the json string could be parsed as an array or object, false if it could not be parsed
    @param ConstructedEntry Output: A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static void MakeMetadataActionJson(ELootLockerServerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access, bool& Succeeded, FLootLockerServerSetMetadataAction& ConstructedEntry);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Base64 value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read", "game_api.write" and "player.read"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerServerSetMetadataAction MakeMetadataActionBase64(ELootLockerServerMetadataActions Action, const FString& Key, const FLootLockerServerMetadataBase64Value& Value, const TArray<FString>& Tags, const TArray<FString>& Access);

};
