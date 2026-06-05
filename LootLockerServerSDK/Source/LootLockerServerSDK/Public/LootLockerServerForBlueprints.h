// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "ServerAPI/LootLockerServerAssetRequest.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerBalanceRequest.h"
#include "ServerAPI/LootLockerServerCatalogRequest.h"
#include "ServerAPI/LootLockerServerCharacterProgressionRequest.h"
#include "ServerAPI/LootLockerServerCharacterRequest.h"
#include "ServerAPI/LootLockerServerConnectedAccountsRequest.h"
#include "ServerAPI/LootLockerServerCurrencyRequest.h"
#include "ServerAPI/LootLockerServerDropTableRequest.h"
#include "ServerAPI/LootLockerServerFriendsRequest.h"
#include "ServerAPI/LootLockerServerGameProgressionRequest.h"
#include "ServerAPI/LootLockerServerHeroRequest.h"
#include "ServerAPI/LootLockerServerInstanceProgressionRequest.h"
#include "ServerAPI/LootLockerServerLeaderboardArchiveRequestHandler.h"
#include "ServerAPI/LootLockerServerLeaderboardRequest.h"
#include "ServerAPI/LootLockerServerMetadataRequest.h"
#include "ServerAPI/LootLockerServerNotificationsRequest.h"
#include "ServerAPI/LootLockerServerOAuthRequest.h"
#include "ServerAPI/LootLockerServerPlayerFileRequest.h"
#include "ServerAPI/LootLockerServerPlayerInventoryRequest.h"
#include "ServerAPI/LootLockerServerPlayerProgressionRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "ServerAPI/LootLockerServerStorageRequest.h"
#include "ServerAPI/LootLockerServerTriggerRequest.h"

#include "LootLockerServerForBlueprints.generated.h"

//==================================================
// General Response Delegates
//==================================================

/*
 Blueprint response delegate for a generic LootLocker Response
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerResponseCallbackBP, FLootLockerServerResponse, Response);

//==================================================
// Auth Response Delegates
//==================================================

/*
 Blueprint response delegate for start session responses
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAuthResponseBP, FLootLockerServerAuthenticationResponse, Response);
/*
 Blueprint response delegate for maintain session responses
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerMaintainSessionResponseBP, FLootLockerServerMaintainSessionResponse, Response);

//==================================================
// Asset Response Delegates
//==================================================

/*
 Blueprint response delegate for getting assets
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetAssetsResponseBP, FLootLockerServerGetAssetsResponse, Response);
/*
 Blueprint response delegate for receiving a list of asset instance key value pairs
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAssetInstanceKeyValuePairsListResponseBP, FLootLockerServerAssetInstanceKeyValuePairsListResponse, Response);
/*
 Blueprint response delegate for receiving a single asset instance key value pair
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAssetInstanceKeyValuePairItemResponseBP, FLootLockerServerAssetInstanceKeyValuePairItemResponse, Response);
/*
 Blueprint response delegate for listing simple assets
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListAssetsResponseBP, FLootLockerServerListAssetsResponse, Response);
/*
 Blueprint response delegate for listing contexts
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListContextsResponseBP, FLootLockerServerListContextsResponse, Response);

//==================================================
// Balance Response Delegates
//==================================================

/**
 * Blueprint response delegate for listing balances in a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListBalancesForWalletResponseBP, FLootLockerServerListBalancesForWalletResponse, Response);
/**
 * Blueprint response delegate for getting a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetWalletResponseBP, FLootLockerServerGetWalletResponse, Response);
/**
 * Blueprint response delegate for crediting currency to a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreditWalletResponseBP, FLootLockerServerCreditWalletResponse, Response);
/**
 * Blueprint response delegate for debiting currency from a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDebitWalletResponseBP, FLootLockerServerDebitWalletResponse, Response);
/**
 * Blueprint response delegate for creating a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreateWalletResponseBP, FLootLockerServerCreateWalletResponse, Response);

//==================================================
// Character Progression Response Delegates
//==================================================

/*
 Blueprint response delegate for receiving a single character progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleCharacterProgressionResponseBP, FLootLockerServerSingleCharacterProgressionResponse, Response);
/*
 Blueprint response delegate for receiving a list of character progressions
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCharacterProgressionListResponseBP, FLootLockerServerCharacterProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single character progression with rewards
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP, FLootLockerServerSingleCharacterProgressionWithRewardsResponse, Response);
/*
 Blueprint response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteCharacterProgressionResponseBP, FLootLockerServerResponse, Response);

//==================================================
// Character Response Delegates
//==================================================

/*
 Blueprint response delegate for getting a player's characters
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerCharacterResponseBP, FLootLockerServerGetPlayerCharactersResponse, Response);
/*
 Blueprint response delegate for getting a player characters inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetCharacterInventoryResponseBP, FLootLockerServerGetCharacterInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player characters loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetCharacterLoadoutResponseBP, FLootLockerServerGetCharacterLoadoutResponse, Response);
/*
 Blueprint response delegate for equipping an asset to a player characters loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerEquipAssetToCharacterLoadoutResponseBP, FLootLockerServerEquipAssetToCharacterLoadoutResponse, Response);
/*
 Blueprint response delegate for unequipping an asset from a player characters loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP, FLootLockerServerUnequipAssetFromCharacterLoadoutResponse, Response);

//==================================================
// Connected Account Response Delegates
//==================================================

/**
 * Blueprint response delegate for listing connected accounts
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListConnectedAccountsResponseBP, FLootLockerServerListConnectedAccountsResponse, Response);

//==================================================
// Currency Response Delegates
//==================================================

/**
 * Blueprint response delegate for listing currencies
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListCurrenciesResponseBP, FLootLockerServerListCurrenciesResponse, Response);

//==================================================
// Catalog Response Delegates
//==================================================

/**
 * Blueprint response delegate for listing catalog prices
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListCatalogPricesResponseBP, FLootLockerServerListCatalogPricesResponse, Response);

//==================================================
// Drop Table Response Delegates
//==================================================

/*
 Blueprint response delegate for computing and locking a drop table
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerComputeAndLockDropTableResponseBP, FLootLockerServerComputeAndLockDropTableResponse, Response);
/*
 Blueprint response delegate for picking from a drop table
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPickFromDropTableResponseBP, FLootLockerServerPickFromDropTableResponse, Response);

//==================================================
// Friends Response Delegates
//==================================================

/**
 * Blueprint response delegate for listing currencies
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListFriendsResponseBP, FLootLockerServerListFriendsResponse, Response);

//==================================================
// Game Progression Response Delegates
//==================================================

/*
 Blueprint response delegate for listing game progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGameProgressionListResponseBP, FLootLockerServerGameProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single game progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleGameProgressionResponseBP, FLootLockerServerSingleGameProgressionResponse, Response);
/*
 Blueprint response delegate for receiving the tiers of a single game progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerProgressionTiersResponseBP, FLootLockerServerProgressionTiersResponse, Response);

//==================================================
// Hero Response Delegates
//==================================================

/*
 Blueprint response delegate for getting a player's heroes
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerHeroResponseBP, FLootLockerServerGetPlayerHeroesResponse, Response);
/*
 Blueprint response delegate for getting a player heroes inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetHeroInventoryResponseBP, FLootLockerServerGetHeroInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player heroes loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetHeroLoadoutResponseBP, FLootLockerServerGetHeroLoadoutResponse, Response);
/*
 Blueprint response delegate for equipping an asset to a player heroes loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerEquipAssetToHeroLoadoutResponseBP, FLootLockerServerEquipAssetToHeroLoadoutResponse, Response);
/*
 Blueprint response delegate for unequipping an asset from a player heroes loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP, FLootLockerServerUnequipAssetFromHeroLoadoutResponse, Response);

//==================================================
// Instance Progression Response Delegates
//==================================================

/*
 Blueprint response delegate for receiving a single instance progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleInstanceProgressionResponseBP, FLootLockerServerSingleInstanceProgressionResponse, Response);
/*
 Blueprint response delegate for receiving a list of instance progressions
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerInstanceProgressionListResponseBP, FLootLockerServerInstanceProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single instance progression with rewards
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP, FLootLockerServerSingleInstanceProgressionWithRewardsResponse, Response);
/*
 Blueprint response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteInstanceProgressionResponseBP, FLootLockerServerResponse, Response);

//==================================================
// Leaderboard Archives Response Delegates
//==================================================

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerLeaderboardArchiveResponseBP, FLootLockerServerLeaderboardArchiveResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerLeaderboardArchiveDetailReponseBP, FLootLockerServerLeaderboardArchiveDetailsResponse, Response);

//==================================================
// Leaderboard Response Delegates
//==================================================

/*
 Blueprint response delegate for listing leaderboards
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListLeaderboardsResponseBP, FLootLockerServerListLeaderboardsResponse, Response);
/*
 Blueprint response delegate for getting leaderboard information
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetLeaderboardResponseBP, FLootLockerServerGetLeaderboardResponse, Response);
/*
 Blueprint response delegate for leaderboard creation
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreateLeaderboardResponseBP, FLootLockerServerCreateLeaderboardResponse, Response);
/*
 Blueprint response delegate for leaderboard updates
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUpdateLeaderboardResponseBP, FLootLockerServerUpdateLeaderboardResponse, Response);
/*
 Blueprint response delegate for leaderboard deletion
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardResponseBP, FLootLockerServerResponse, Response);
/*
 Blueprint response delegate for leaderboard score submission
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerLeaderboardSubmitScoreResponseBP, FLootLockerServerLeaderboardSubmitScoreResponse, Response);
/*
 Blueprint response delegate for leaderboard score increment
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerLeaderboardIncrementScoreResponseBP, FLootLockerServerLeaderboardSubmitScoreResponse, Response);
/*
 Blueprint response delegate for getting all member ranks
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetAllMemberRanksResponseBP, FLootLockerServerGetAllMemberRanksResponse, Response);
/*
 Blueprint response delegate for getting scores from a leaderboard
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetScoresFromLeaderboardResponseBP, FLootLockerServerGetScoresFromLeaderboardResponse, Response);
/*
 Blueprint response delegate for getting the schedule for a leaderboard
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetLeaderboardScheduleResponseBP, FLootLockerServerGetLeaderboardScheduleResponse, Response);
/*
 Blueprint response delegate for leaderboard schedule deletion
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardScheduleResponseBP, FLootLockerServerResponse, Response);
/*
 Blueprint response delegate for requesting a manual leaderboard reset
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerRequestManualLeaderboardResetResponseBP, FLootLockerServerManualLeaderboardResetResponse, Response);
/*
 Blueprint response delegate for listing manual leaderboard resets
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListManualLeaderboardResetsResponseBP, FLootLockerServerListManualLeaderboardResetsResponse, Response);
/*
 Blueprint response delegate for getting a specific manual leaderboard reset
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetManualLeaderboardResetResponseBP, FLootLockerServerManualLeaderboardResetResponse, Response);
/*
 Blueprint response delegate for cancelling a manual leaderboard reset
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCancelManualLeaderboardResetResponseBP, FLootLockerServerResponse, Response);

//==================================================
// Metadata Response Delegates
//==================================================

/*
 Blueprint response delegate for listing metadata
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListMetadataResponseBP, FLootLockerServerListMetadataResponse, Response);
/*
 Blueprint response delegate for getting a single metadata entry
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetMetadataResponseBP, FLootLockerServerGetMetadataResponse, Response);
/*
 Blueprint response delegate for getting multi source metadata
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetMultisourceMetadataResponseBP, FLootLockerServerGetMultisourceMetadataResponse, Response);
/*
 Blueprint response delegate for setting metadata
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSetMetadataResponseBP, FLootLockerServerSetMetadataResponse, Response);

//==================================================
// Notifications Response Delegates
//==================================================

/*
 Blueprint response delegate for sending notifications
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSendNotificationsResponseBP, FLootLockerServerSendNotificationsResponse, Response);

//==================================================
// OAuth Response Delegates
//==================================================

/*
 Blueprint response delegate for handling token exchange responses
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerTokenExchangeResponseBP, FLootLockerServerTokenExchangeResponse, Response);

//==================================================
// Player File Response Delegates
//==================================================

/*
 Blueprint response delegate for listing player files
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerFileListResponseBP, FLootLockerServerPlayerFileListResponse, Response);
/*
 Blueprint response delegate for a single returned file
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSinglePlayerFileResponseBP, FLootLockerServerSinglePlayerFileResponse, Response);
/*
 Blueprint response delegate for deleting a file, will be empty unless there's an error
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerFileDeleteResponseBP, FLootLockerServerPlayerFileDeleteResponse, Response);

//==================================================
// Player Inventory Response Delegates
//==================================================

/*
 Blueprint response delegate for getting a game's universal inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetUniversalInventoryResponseBP, FLootLockerServerGetUniversalInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player's inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerInventoryResponseBP, FLootLockerServerGetPlayerInventoryResponse, Response);
/*
 Blueprint response delegate for adding an asset to a player's inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAddAssetToPlayerInventoryResponseBP, FLootLockerServerAddAssetToPlayerInventoryResponse, Response);
/*
 Blueprint response delegate for altering a player's inventory
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerAlterPlayerInventoryResponseBP, FLootLockerServerAlterPlayerInventoryResponse, Response);
/*
 Blueprint response delegate for getting a player's loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerLoadoutResponseBP, FLootLockerServerGetPlayerLoadoutResponse, Response);
/*
 Blueprint response delegate for equipping an asset to a player's loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerEquipAssetToPlayerLoadoutResponseBP, FLootLockerServerEquipAssetToPlayerLoadoutResponse, Response);
/*
 Blueprint response delegate for unequipping an asset from a player's loadout
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP, FLootLockerServerUnequipAssetFromPlayerLoadoutResponse, Response);

//==================================================
// Player Progression Response Delegates
//==================================================

/*
 Blueprint response delegate for receiving a single player progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionResponseBP, FLootLockerServerSinglePlayerProgressionResponse, Response);
/*
 Blueprint response delegate for receiving a list of player progressions
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerProgressionListResponseBP, FLootLockerServerPlayerProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single player progression with rewards
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP, FLootLockerServerSinglePlayerProgressionWithRewardsResponse, Response);
/*
 Blueprint response delegate for deleting a progression. Will be empty if no error occured.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeletePlayerProgressionResponseBP, FLootLockerServerResponse, Response);

//==================================================
// Player Response Delegates
//==================================================

/*
 Blueprint response delegate for looking up player names
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerNameLookupResponseBP, FLootLockerServerPlayerNameLookupResponse, Response);
/*
 Blueprint response delegate for looking up players by their game session tokens
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP, FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse, Response);
/*
 Blueprint response delegate for creating a player
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreatePlayerResponseBP, FLootLockerServerCreatePlayerResponse, Response);

//==================================================
// Storage Response Delegates
//==================================================

/*
 Blueprint response delegate for fetching persistent storage for player(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPersistentStorageForPlayersResponseBP, FLootLockerServerGetPersistentStorageForPlayersResponse, Response);

/*
 Blueprint response delegate for fetching persistent storage for player(s) and key(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse, Response);

/*
 Blueprint response delegate for updating persistent storage for player(s) and key(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse, Response);

/*
 Blueprint response delegate for deleting persistent storage for player(s) and key(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse, Response);

//==================================================
// Trigger Response Delegates
//==================================================

/*
 Blueprint response delegate for invoking a trigger
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerInvokeTriggerResponseBP, FLootLockerServerInvokeTriggerResponse, Response);

UCLASS(Blueprintable)
class LOOTLOCKERSERVERSDK_API ULootLockerServerForBlueprints : public UObject
{
    GENERATED_BODY()
 
public:
    //==================================================
    // Authentication
    //==================================================

    /**
     * Start a session connecting to the LootLocker services with the server API key
     *
     * @param OnCompletedRequest Delegate for handling the response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Authentication")
    static UPARAM(DisplayName = "RequestId") FString StartSession(const FLootLockerServerAuthResponseBP& OnCompletedRequest);

    /**
     * Keep the session alive, you should call this endpoint at least once per hour, to extend your tokens lifetime.
     *
     * @param OnCompletedRequest Delegate for handling the response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Authentication")
    static UPARAM(DisplayName = "RequestId") FString MaintainSession(const FLootLockerServerMaintainSessionResponseBP& OnCompletedRequest);

    //==================================================
    // Token Exchange
    //==================================================

    /**
     Get a new active game api session token for the player holding the supplied game api session token

     This will allow the server to make requests to the game api on behalf of the user corresponding to the original token.

     @param GameApiSessionToken The session token for a current game api session to use in exchange for a new one
     @param OnCompletedRequest Delegate for handling the response
     
     @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Token Exchange")
    static UPARAM(DisplayName = "RequestId") FString GameApiTokenExchange(const FString& GameApiSessionToken, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest);

    /**
     Get a new active game api session token for the specified player

     This will allow the server to make requests to the game api on behalf of the specified user.

     @param PlayerUlid The ulid of the player you wish to impersonate
     @param OnCompletedRequest Delegate for handling the response
     
     @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Token Exchange")
    static UPARAM(DisplayName = "RequestId") FString GameApiUserImpersonation(const FString& PlayerUlid, const FLootLockerServerTokenExchangeResponseBP& OnCompletedRequest);

    //==================================================
    // Leaderboards
    //==================================================

    /**
     * List leaderboards with details on each leaderboard
     *
     * @param Count Optional: The count of items you want to retrieve.
     * @param After Optional: Used for pagination, id from which the pagination starts from.
     * @param OnCompletedRequestBP Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard", meta = (AdvancedDisplay = "Count,After", Count = 50, After = 0))
    static UPARAM(DisplayName = "RequestId") FString ListLeaderboards(int Count, int After, const FLootLockerServerListLeaderboardsResponseBP& OnCompletedRequestBP);

    /**
     * Get information about a given leaderboard.
     *
     * @param LeaderboardKey The key of the leaderboard to get information for
     * @param OnCompletedRequest Delegate for handling the response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Create a new leaderboard with the provided details.
     *
     * @param LeaderboardKey Unique key for the leaderboard
     * @param Name Name of the leaderboard
     * @param Type Type of the leaderboard
     * @param HasMetadata Whether the leaderboard has metadata
     * @param DirectionMethod Sort order (Ascending or Descending), based on whether highest rank is lowest or highest number
     * @param EnableGameApiWrites Whether the Game API is permitted to write to this leaderboard
     * @param OverwriteScoreOnSubmit Submitting a new score for member will always overwrite their existing score on leaderboard
     * @param OnCompletedRequest Delegate for handling the response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString CreateLeaderboard(FString LeaderboardKey, FString Name, ELootLockerServerLeaderboardType Type, bool HasMetadata, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Update an existing leaderboard with the provided details.
     *
     * @param LeaderboardKey The key of the leaderboard to update
     * @param NewLeaderboardKey The unique key to set for the leaderboard, if you do not want to change it then set it to the same as LeaderboardKey
     * @param Name Name of the leaderboard
     * @param DirectionMethod sort order (Ascending or Descending), based on whether highest rank is lowest or highest number
     * @param EnableGameApiWrites Whether the Game API is permitted to write to this leaderboard
     * @param OverwriteScoreOnSubmit Submitting a new score for member will always overwrite their existing score on leaderboard
     * @param OnCompletedRequest Delegate for handling the response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString UpdateLeaderboard(FString LeaderboardKey, FString NewLeaderboardKey, FString Name, ELootLockerServerLeaderboardDirection DirectionMethod, bool EnableGameApiWrites, bool OverwriteScoreOnSubmit, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Delete an existing leaderboard
     *
     * @param LeaderboardKey The key of the leaderboard to delete
     * @param OnCompletedRequest Delegate for handling the response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString DeleteLeaderboard(FString LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequest);

    /**
     * Submit a score to the given leaderboard
     *
     * @param LeaderboardKey The key of the leaderboard to delete
     * @param MemberID The ID of the member to submit the score for. For player type leaderboards this is the PlayerID, for Generic type leaderboards it can be any string so you need to know what/who you want to submit for.
     * @param Score The score to submit
     * @param Metadata Metadata to add to the score (will only be used if the leaderboard has metadata enabled)
     * @param OnCompletedRequest Delegate for handling the response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString SubmitScore(FString LeaderboardKey, FString MemberID, int Score, FString Metadata, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequest);

    /**
     * Increment a member's score on the given leaderboard by the specified amount.
     *
     * @param LeaderboardKey The key of the leaderboard to increment the score on
     * @param MemberID The ID of the member whose score to increment. For player type leaderboards this is the PlayerID, for generic type leaderboards it can be any string.
     * @param Amount The amount to increment the score by
     * @param OnCompletedRequest Delegate for handling the response
     *
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString IncrementScore(FString LeaderboardKey, FString MemberID, int Amount, const FLootLockerServerLeaderboardIncrementScoreResponseBP& OnCompletedRequest);

    /**
     * For all leaderboards that this member has scores on, get the score, member information, rank, score, and metadata (if metadata is enabled on that leaderboard), as well as player information if the leaderboard is of type player.
     *
     * @param MemberID The ID of the member to get the scores for. For player type leaderboards this is the PlayerID, for Generic type leaderboards it can be any string so you need to know what/who you want to submit for.

     * @param OnCompletedRequest Delegate for handling the response
     
     @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString GetAllMemberRanks(FString MemberID, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest);

    /**
     * For all leaderboards that this member has scores on, get the score, member information, rank, score, and metadata (if metadata is enabled on that leaderboard), as well as player information if the leaderboard is of type player, using pagination settings.
     ion
     *
     * @param MemberID The ID of the member to get the scores for. For player type leaderboards this is the PlayerID, for Generic type leaderboards it can be any string so you need to know what/who you want to submit for.
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response

     * @param OnCompletedRequest Delegate for handling the response
     
     @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedAllMemberRanks(FString MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequest);

    /**
     * From the requested leaderboard get <count> number of scores. The list of scores has member information, rank, score, and metadata (if metadata is enabled on that leaderboard) for the given leaderboard. If leaderboard is of type player a player will also be in the response.
     * Results are sorted in ascending order.
     *
     * @param LeaderboardKey The key of the leaderboard you want to connect to.
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString GetScoresFromLeaderboard(FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest);

    /**
     * From the requested leaderboard get <count> number of scores. The list of scores has member information, rank, score, and metadata (if metadata is enabled on that leaderboard) for the given leaderboard. If leaderboard is of type player a player will also be in the response, using pagination settings.
     * Results are sorted in ascending order.
     * Maximum allowed scores to query for at a time is currently 2000.
     agination
     *
     * @param LeaderboardKey The key of the leaderboard you want to connect to.
     * @param Count Number of scores returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboards")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedScoresFromLeaderboard(FString LeaderboardKey, int Count, int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequest);

    /**
    * Get the schedule for the specified leaderboard
    * @param LeaderboardKey The Key of the leaderboard for which to fetch the schedule
    * @param OnCompletedRequestBP Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequestBP);
    
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
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequest);
    
    /**
    * Remove the schedule (if any) from the specified leadeboard
    * @param Key the Key of the leaderboard for which to remove the schedule
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseBP& OnCompletedRequest);

    /**
    * Request a manual reset of a leaderboard
    * @param LeaderboardKey The Key of the leaderboard to reset
    * @param Request Request body specifying an optional name and optional scheduled time for the reset
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString RequestManualLeaderboardReset(const FString& LeaderboardKey, const FLootLockerServerCreateManualLeaderboardResetRequest& Request, const FLootLockerServerRequestManualLeaderboardResetResponseBP& OnCompletedRequest);

    /**
    * List all manual reset requests for a leaderboard
    * @param LeaderboardKey The Key of the leaderboard
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString ListManualLeaderboardResets(const FString& LeaderboardKey, const FLootLockerServerListManualLeaderboardResetsResponseBP& OnCompletedRequest);

    /**
    * Get a specific manual reset request for a leaderboard
    * @param LeaderboardKey The Key of the leaderboard
    * @param ResetId The ID of the manual reset to retrieve
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString GetManualLeaderboardReset(const FString& LeaderboardKey, const FString& ResetId, const FLootLockerServerGetManualLeaderboardResetResponseBP& OnCompletedRequest);

    /**
    * Cancel a pending manual reset request for a leaderboard
    * Only pending resets can be cancelled.
    * @param LeaderboardKey The Key of the leaderboard
    * @param ResetId The ID of the manual reset to cancel
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString CancelManualLeaderboardReset(const FString& LeaderboardKey, const FString& ResetId, const FLootLockerServerCancelManualLeaderboardResetResponseBP& OnCompletedRequest);

    //==================================================
    // Leaderboard Archives
    //==================================================

    /**
    * List the archive of a specific Leaderboard,
    * @param LeaderboardKey The Key of the Leaderboard you want the list of archives
    * @param OnCompletedRequestBP Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard")
    static UPARAM(DisplayName = "RequestId") FString ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseBP& OnCompletedRequestBP);

    /**
    * Get the specified Archive which includes details such as ranks, scores and rewards.
    * @param Key the Key of the leaderboard archive entry you want to fetch details for
    * @param Count Optional: The count of items you want to retrieve.
    * @param After Optional: Used for pagination, id from which the pagination starts from.
    * @param OnCompletedRequestBP Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Leaderboard", meta = (AdvancedDisplay = "Count,After", Count = -1, After = ""))
    static UPARAM(DisplayName = "RequestId") FString GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP);

    //==================================================
    // Triggers
    //==================================================

    /**
     * Trigger the requested trigger on behalf of the provided player
     *
     * To see the configured triggers for your game, go here: https://console.lootlocker.com/triggers
     *
     * @param TriggerName The name of the trigger to invoke for the provided player
     * @param PlayerID The ID of the player to invoke the trigger for
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Triggers")
    static UPARAM(DisplayName = "RequestId") FString InvokeTriggerForPlayer(FString TriggerName, int PlayerID, const FLootLockerServerInvokeTriggerResponseBP& OnCompletedRequest);

    //==================================================
    // Player Persistent Storage
    //==================================================

    /**
     * Get the persistent storage for the provided player
     *
     * @param PlayerID The ID of the player to fetch the persistent storage for
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static UPARAM(DisplayName = "RequestId") FString GetPersistentStorageForPlayer(int PlayerID, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest);

    /**
     * Get the persistent storage for all the player ids provided
     *
     * @param PlayerIDs The IDs of the players to fetch the persistent storage for
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static UPARAM(DisplayName = "RequestId") FString GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompletedRequest);

    /**
     * Get all the public (if any) persistent storage for the provided players
     *
     * @param PlayerIDs The IDs of the players to fetch the persistent storage for
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static UPARAM(DisplayName = "RequestId") FString GetEntirePublicPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);

    /**
     * Get all the public (if any) persistent storage for the provided players, but filter the list by the provided keys
     *
     * @param PlayerIDs The IDs of the players to fetch the persistent storage for
     * @param Keys The keys to filter the persistent storage by, if empty all keys will be returned.
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static UPARAM(DisplayName = "RequestId") FString GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);

    /**
     * Update the persistent storage for the provided player according to the objects provided
     *
     * @param StorageEntriesToUpdate The data to update the persistent storage with
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static UPARAM(DisplayName = "RequestId") FString UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);

    /**
     * Delete the persistent storage for the provided keys on the provided players
     * If the request fails you will be given an error message. We recommend you make a get request on the players and keys to see what keys failed to delete.
     *
     * @param PlayerIDs The IDs of the players for whom to apply the delete
     * @param Keys The keys to delete for the provided players
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Persistent Storage")
    static UPARAM(DisplayName = "RequestId") FString DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP& OnCompletedRequest);
    
    //==================================================
    // Characters
    //==================================================
    
    /**
     * List all characters for this player.
     * If your game uses heroes the characters underlaying the heroes will be listed too.
     *
     * @param PlayerID The ID of the player for whom to get the characters
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseBP& OnCompletedRequest);
    
    /**
     * Get the inventory for the specified player and character
     *
     * @param PlayerID The ID of the player for whom to get the character inventory
     * @param CharacterID The ID of the character on the specified player for which to get the inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get a subset of the inventory for the specified player and character using pagination settings
     n
     *
     * @param PlayerID The ID of the player for whom to get the character inventory
     * @param CharacterID The ID of the character on the specified player for which to get the inventory
     * @param Count The number of inventory items to get. Must be a value between 1 and 200
     * @param After The id of the inventory item from where to start getting inventory items (non inclusive). Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the full loadout for the specified player and character
     *
     * @param PlayerID The ID of the player for whom to get the character loadout
     * @param CharacterID The ID of the character on the specified player for which to get the loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and character using an asset instance id
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to equip the asset instance
     * @param AssetInstanceID The ID of the asset instance to equip to the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and character using an asset id and an asset variation id
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player character's loadout
     * @param AssetVariationID The ID of the variation of the specified asset to equip to the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and character using an asset id and a rental option id
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player character's loadout
     * @param RentalOptionID The ID of the rental option of the specified asset to equip to the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseBP& OnCompletedRequest);
    /**
     * Unequip an asset instance from the loadout of specified player and character using the instance id
     *
     * @param PlayerID The ID of the player for whom to unequip the asset instance
     * @param CharacterID The ID of the character on the specified player for whose loadout to unequip the asset instance
     * @param InstanceID The ID of the asset instance to unequip from the specified player character's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character")
    static UPARAM(DisplayName = "RequestId") FString UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseBP& OnCompletedRequest);
    
    //==================================================
    // Heroes
    //==================================================
    
    /**
     * List all heroes for this player.
     *
     * @param PlayerID The ID of the player for whom to get the heroes
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseBP& OnCompletedRequest);
    
    /**
     * Get the inventory for the specified player and hero
     *
     * @param PlayerID The ID of the player for whom to get the hero inventory
     * @param HeroID The ID of the hero on the specified player for which to get the inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get a subset of the inventory for the specified player and hero using pagination settings
     on
     *
     * @param PlayerID The ID of the player for whom to get the hero inventory
     * @param HeroID The ID of the hero on the specified player for which to get the inventory
     * @param Count The number of inventory items to get. Must be a value between 1 and 200
     * @param After The id of the inventory item from where to start getting inventory items (non inclusive). Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the full loadout for the specified player and hero
     *
     * @param PlayerID The ID of the player for whom to get the hero loadout
     * @param HeroID The ID of the hero on the specified player for which to get the loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and hero using an asset instance id
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to equip the asset instance
     * @param AssetInstanceID The ID of the asset instance to equip to the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and hero using an asset id and an asset variation id
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player hero's loadout
     * @param AssetVariationID The ID of the variation of the specified asset to equip to the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the loadout of specified player and hero using an asset id and a rental option id
     *
     * @param PlayerID The ID of the player for whom to equip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to equip the asset instance
     * @param AssetID The ID of the asset to equip to the specified player hero's loadout
     * @param RentalOptionID The ID of the rental option of the specified asset to equip to the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequest);
    /**
     * Unequip an asset instance from the loadout of specified player and hero using the instance id
     *
     * @param PlayerID The ID of the player for whom to unequip the asset instance
     * @param HeroID The ID of the hero on the specified player for whose loadout to unequip the asset instance
     * @param InstanceID The ID of the asset instance to unequip from the specified player hero's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Heroes")
    static UPARAM(DisplayName = "RequestId") FString UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP& OnCompletedRequest);

    //==================================================
    // Player Inventory
    //==================================================
    
    /**
     * Get a list of assets that are available for all player's in the game
     *
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the specified player's default character's inventory
     *
     * @param PlayerID The ID of the player for whom to get the inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the specified player's default character's inventory according to the specified pagination parameters
     ion
     *
     * @param PlayerID The ID of the player for whom to get the inventory
     * @param Count The number of inventory items to get. Must be a value between 1 and 200
     * @param After The id of the inventory item from where to start getting inventory items (non inclusive). Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Get the specified player's default character's loadout
     *
     * @param PlayerID The ID of the player for whom to get the loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the specified player's default character's loadout using an asset id which will equip that asset's default variation
     * If the request is successfull, the returned list contains the full loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetID The ID of the asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip the specified asset instance to the specified player's default character's loadout
     * If the request is successfull, the returned list contains the full loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetInstanceID The Instance ID of the asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the specified player's default character's loadout by specifiying an asset id and which variation id of the asset to equip
     * If the request is successfull, the returned list contains the full loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetID The ID of the asset to equip to the specified player's loadout
     * @param AssetVariationID The ID of the variation of the specified asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Equip an asset instance to the specified player's default character's loadout by specyfiying an asset id and which rental option id of the asset to equip
     * If the request is successfull, the returned list contains the full loadout
     *
     * @param PlayerID The ID of the player for whom to equip the asset
     * @param AssetID The ID of the asset to equip to the specified player's loadout
     * @param RentalOptionID The ID of the rental option of the specified asset to equip to the specified player's loadout
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Unequip an asset instance from the specified player's default character's loadout
     * If the request is successfull, the returned list contains the full loadout
     *
     * @param PlayerID The ID of the player for whom to unequip the asset
     * @param InstanceID The Instance ID of the asset in the specified player's loadout to unequip
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP& OnCompletedRequest);
    
    /**
     * Add the specified asset to the specified player's inventory (grant the asset) using an asset id which will equip that asset's default variation
     * If the request is successfull, the returned list contains all assets that were granted to the player
     *
     * @param PlayerID The ID of the player for whom to add the asset
     * @param AssetID The ID of the asset to add to the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Add the specified asset to the specified player's inventory (grant the asset) by specifiying an asset id and which variation id of the asset to equip
     * If the request is successfull, the returned list contains all assets that were granted to the player
     *
     * @param PlayerID The ID of the player for whom to add the asset
     * @param AssetID The ID of the asset to add to the specified player's inventory
     * @param VariationID The ID of the specific variation of the specified asset to add to the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Add the specified asset to the specified player's inventory (grant the asset) by specyfiying an asset id and which rental option id of the asset to equip
     * If the request is successfull, the returned list contains all assets that were granted to the player
     *
     * @param PlayerID The ID of the player for whom to add the asset
     * @param AssetID The ID of the asset to add to the specified player's inventory
     * @param RentalOptionID The ID of the specific rental option of the specified asset to add to the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Bulk add (grant) and/or remove assets to/from the specified player's inventory
     * Add assets by supplying a list of asset id's for which the default variation will be used
     * If the request is successfull, the return will contain two lists; one specifying the id's of all the assets that were removed, one specifying all added assets
     *
     * @param PlayerID The ID of the player for whom to alter the inventory
     * @param AssetsToAdd A list of assets to add to the specified player's inventory
     * @param AssetsToRemove A list of asset instance id's of assets to remove from the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Bulk add (grant) and/or remove assets to/from the specified player's inventory
     * Add assets by supplying a list of asset ids and variation ids of those assets to use
     * If the request is successfull, the return will contain two lists; one specifying the id's of all the assets that were removed, one specifying all added assets
     *
     * @param PlayerID The ID of the player for whom to alter the inventory
     * @param AssetsToAdd A list of assets to add to the specified player's inventory
     * @param AssetsToRemove A list of asset instance id's of assets to remove from the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest);
    
    /**
     * Bulk add (grant) and/or remove assets to/from the specified player's inventory
     * Add assets by supplying a list of asset ids and rental option ids of those assets to use
     * If the request is successfull, the return will contain two lists; one specifying the id's of all the assets that were removed, one specifying all added assets
     *
     * @param PlayerID The ID of the player for whom to alter the inventory
     * @param AssetsToAdd A list of assets to add to the specified player's inventory
     * @param AssetsToRemove A list of asset instance id's of assets to remove from the specified player's inventory
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Inventory")
    static UPARAM(DisplayName = "RequestId") FString AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseBP& OnCompletedRequest);

    //==================================================
    // Assets
    //==================================================

    /**
     * List all the assets from this game
     * Note that this is a paginated call and it will likely require multiple calls to LootLocker with a parameter for every call except the first to step forward in the results.
     * Up to 200 (the default limit is 50 though) assets are returned at a time, and to fetch the next page you have to use the largest ID you've gotten returned in the previous response
     *
     * @param IncludeUGC Optional: Include user generated assets
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets", meta = (AdvancedDisplay = "IncludeUGC", IncludeUGC = false))
    static UPARAM(DisplayName = "RequestId") FString GetAssets(bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequest);

    /**
     * List a set of assets from this game according to the supplied pagination options
     quire multiple calls to LootLocker with a parameter for every call except the first to step forward in the results.
     * Up to 200 (the default limit is 50 though) assets are returned at a time, and to fetch the next page you have to use the largest ID you've gotten returned in the previous response
     *
     * @param Count The number of assets to get. Must be a value between 1 and 200
     * @param After The id of the asset from where to start getting assets (non inclusive). Set to 0 to start from the first item
     * @param IncludeUGC Optional: Include user generated assets
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets", meta = (AdvancedDisplay = "IncludeUGC", IncludeUGC = false))
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedAssets(int Count, int After, bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequest);

    /**
     * Get all assets for a context.
     *
     * @param Count The number of assets to get. Must be a value between 1 and 200
     * @param After The id of the asset from where to start getting assets (non inclusive). Set to 0 to start from the first item
     * @param Context The context id to filter by
     * @param IncludeUGC Optional: Include user generated assets
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets", meta = (AdvancedDisplay = "IncludeUGC", IncludeUGC = false))
    static UPARAM(DisplayName = "RequestId") FString GetAssetsByContext(int Count, int After, int Context, bool IncludeUGC, const FLootLockerServerGetAssetsResponseBP& OnCompletedRequest);

    /**
     * List assets with configurable response data. Use this to limit the fields returned in the response and improve performance.
     * Lightweight alternative for retrieving assets where only selected data is needed
     * @param Request Request payload specifying includes/excludes/filters
     * @param PerPage Optional: page size (ignored if 0 or negative)
     * @param Page Optional: page index (ignored if 0 or negative)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets", meta=(AdvancedDisplay="PerPage,Page", PerPage=-1, Page=-1))
    static UPARAM(DisplayName = "RequestId") FString ListAssets(const FLootLockerServerListAssetsRequest& Request, int PerPage, int Page, const FLootLockerServerListAssetsResponseBP& OnCompletedRequest);

    /**
    * List assets with default parameters (no filters, first page, default page size)
    * Lightweight alternative for retrieving assets where only selected data is needed
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets")
    static UPARAM(DisplayName = "RequestId") FString ListAssetsWithDefaultParameters(const FLootLockerServerListAssetsResponseBP& OnCompletedRequest);

    /**
     * List contexts with pagination support
     *
     * @param PerPage Optional: page size (ignored if 0 or negative)
     * @param Page Optional: page index (ignored if 0 or negative)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Assets", meta=(AdvancedDisplay="PerPage,Page", PerPage=-1, Page=-1))
    static UPARAM(DisplayName = "RequestId") FString ListContexts(int PerPage, int Page, const FLootLockerServerListContextsResponseBP& OnCompletedRequest);

    //==================================================
    // Asset Instances
    //==================================================

    /**
     * Get a list of key value pairs from the specified asset instance
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static UPARAM(DisplayName = "RequestId") FString GetKeyValuePairsFromAssetInstance(int PlayerID, int AssetInstanceID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    /**
     * Get a single Key Value Pair from the specified asset instance by key value pair id
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The ID of the asset instance on this player for which to complete the operation
     * @param KeyValuePairID The ID of the specific key value pair to get
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static UPARAM(DisplayName = "RequestId") FString GetAssetInstanceKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest);

    /**
     * Create a key value pair on the specified asset instance
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param Key The key to add
     * @param Value The value to set for the added key
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static UPARAM(DisplayName = "RequestId") FString AddKeyValuePairToAssetInstance(int PlayerID, int AssetInstanceID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    /**
     * Create or update a list of key value pairs on the specified asset instance
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param KeyValuePairs A list of key value pairs to update
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static UPARAM(DisplayName = "RequestId") FString UpdateKeyValuePairsOnAssetInstance(int PlayerID, int AssetInstanceID, TArray<FLootLockerServerAssetStorageKeyValueSet> KeyValuePairs, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    /**
     * Update a single key value pair on the specified asset instance by key value pair id
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param KeyValuePairID The ID of the specific key value pair to update
     * @param Key The key to set for the key value pair
     * @param Value The value to set for the updated key
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static UPARAM(DisplayName = "RequestId") FString UpdateKeyValuePairOnAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FString Key, FString Value, const FLootLockerServerAssetInstanceKeyValuePairItemResponseBP& OnCompletedRequest);

    /**
     * Delete a key value pair from the specified asset instance by key value pair id
     *
     * @param PlayerID The player ID of the player that this player asset instance belongs to
     * @param AssetInstanceID The id of the asset instance on this player for which to complete the operation
     * @param KeyValuePairID The ID of the specific key value pair to delete
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Asset Instances")
    static UPARAM(DisplayName = "RequestId") FString DeleteKeyValuePairFromAssetInstanceById(int PlayerID, int AssetInstanceID, int KeyValuePairID, const FLootLockerServerAssetInstanceKeyValuePairsListResponseBP& OnCompletedRequest);

    //==================================================
    // Drop Tables
    //==================================================
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static UPARAM(DisplayName = "RequestId") FString ComputeAndLockDropTable(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory, but only use items with the specified tag
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param Tag Which tag to limit drop table computation to
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static UPARAM(DisplayName = "RequestId") FString ComputeAndLockDropTableForTag(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory and include the full asset information in the response
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static UPARAM(DisplayName = "RequestId") FString ComputeAndLockDropTableWithAssetInformation(int PlayerID, int DropTableID, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);
    
    /**
     * Use this method to compute and lock the specified drop table item from the specified player's inventory, but only use items with the specified tag and include the full asset information in the response
     *
     * @param PlayerID The id of the player for whom to compute and lock the drop table
     * @param DropTableID The id of the drop table item to compute and lock
     * @param Tag Which tag to limit drop table computation to
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static UPARAM(DisplayName = "RequestId") FString ComputeAndLockDropTableForTagWithAssetInformation(int PlayerID, int DropTableID, const FString& Tag, const FLootLockerServerComputeAndLockDropTableResponseBP& OnCompletedRequest);

    /**
     * Pick drop table items from the specified drop table and player
     *
     * @param PlayerID The id of the player for whom the drop table applies
     * @param DropTableID The id of the drop table from which to pick items
     * @param DropTableItemIDsToPick A list of drop table item ids to pick
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Drop Tables")
    static UPARAM(DisplayName = "RequestId") FString PickDropsFromDropTable(int PlayerID, int DropTableID, TArray<int> DropTableItemIDsToPick, const FLootLockerServerPickFromDropTableResponseBP& OnCompletedRequest);

    //==================================================
    // Friends
    //==================================================

    /**
     * List friends for the specified player
     *
     * @param PlayerULID The ULID of the player for whom to list friends
     * @param Page The page number to retrieve. Each page contains 'PerPage' number of items.
     * @param PerPage The number of items to retrieve per page.
     * @param OnCompletedRequest Delegate for handling the the server response.
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Friends")
    static UPARAM(DisplayName = "RequestId") FString ListFriendsForPlayer(const FString& PlayerULID, int Page, int PerPage, const FLootLockerServerListFriendsResponseBP& OnCompletedRequest);

    //==================================================
    // Connected Accounts
    //==================================================

    /**
     * List connected accounts for multiple players (up to 25)
     * You can provide player ULIDs, legacy player IDs, or both
     *
     * @param PlayerULIDs List of Player ULIDs
     * @param LegacyPlayerIDs List of legacy integer Player IDs
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Connected Accounts")
    static UPARAM(DisplayName = "RequestId") FString ListConnectedAccounts(const TArray<FString>& PlayerULIDs, const TArray<int>& LegacyPlayerIDs, const FLootLockerServerListConnectedAccountsResponseBP& OnCompletedRequest);

    //==================================================
    // Player
    //==================================================

    /**
     * Lookup a number of player names from the player's id
     *
     * @param IdsToLookUp A list of ids to lookup also specyfying for each id which type of id it is
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player")
    static UPARAM(DisplayName = "RequestId") FString LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequest);

    /**
     * Lookup players by their game session tokens
     * Use this to verify in the server that the client player is who they say they are
     *
     * @param GameSessionTokensToLookUp A list of game session tokens to lookup
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player")
    static UPARAM(DisplayName = "RequestId") FString GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequest);

    /**
     * Creates a player in LootLocker for the platform player. This works by creating an unverified session for a player with the platform and identifier from the input. 
     * No verification is performed by LootLocker. If a player already exists, the player integer ID and ULID will be returned. If a player doesn't exist yet, one will be created before returning the same integer ID and ULID.
     * If the player identifier isn't normally sent in the Game API session endpoint, you should ensure that you resolve it correctly from the original platform (eg steam) before calling this endpoint.
     *
     * @param Platform The platform of the player you want to create (e.g. "Steam", "Xbox", or "Guest")
     * @param PlatformPlayerIdentifier The unique identifier for the player on the specified platform (e.g. a SteamID)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player")
    static UPARAM(DisplayName = "RequestId") FString CreatePlayer(ELootLockerServerCreatePlayerPlatforms Platform, const FString& PlatformPlayerIdentifier, const FLootLockerServerCreatePlayerResponseBP& OnCompletedRequest);

    //==================================================
    // Player Files
    //==================================================

    /**
     * List files currently associated with the specified player
     *
     * @param PlayerID ID of the player for whom to list files
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static UPARAM(DisplayName = "RequestId") FString ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseBP& OnCompletedRequest);

    /**
     * Get the specified file currently associated with the specified player
     *
     * @param PlayerID ID of the player for whom to get the specified file
     * @param FileID ID of the file to get
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static UPARAM(DisplayName = "RequestId") FString GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    /**
     * Delete the specified file currently associated with the specified player
     * The response will be empty unless there's an error
     *
     * @param PlayerID ID of the player for whom to delete the specified file
     * @param FileID ID of the file to delete
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static UPARAM(DisplayName = "RequestId") FString DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseBP& OnCompletedRequest);

    /**
     * Upload the specified file to the specified player
     * Each file can be a maximum of 5MB and each player can have a maximum of 50 files
     *
     * @param PlayerID ID of the player for whom to upload the specified file
     * @param FilePath The path on disk to the file you want to upload
     * @param Purpose A tag specifying the purpose of this file
     * @param IsPublic Whether this file is publically available (accessible for other players)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static UPARAM(DisplayName = "RequestId") FString UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

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
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static UPARAM(DisplayName = "RequestId") FString UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    /**
     * Update the specified file for the specified player with the supplied file content
     *
     * @param PlayerID ID of the player for whom to update the specified file
     * @param FileID ID of the file to update
     * @param FilePath The path on disk to the file you want to update the specified file with
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static UPARAM(DisplayName = "RequestId") FString UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    /**
     * Update the specified file for the specified player with the supplied raw data
     *
     * @param PlayerID ID of the player for whom to update the specified file
     * @param FileID ID of the file to update
     * @param RawData The raw data to update the specified file with
     * @param FileName The name to set for the file
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Files")
    static UPARAM(DisplayName = "RequestId") FString UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequest);

    //==================================================
    // Game Progressions
    //==================================================

    /**
     * Get a list of progressions for the game
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedProgressions
     *
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressions(const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a list of progressions for the game using pagination settings
     *
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get the specified progression
     *
     * @param ProgressionKey The key of the progression you want to get
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseBP& OnCompletedRequest);

    /**
     * Get a list of tiers for the specified progression
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedTiersForProgression
     *
     * @param ProgressionKey The key of the progression for which you want to get the tiers
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest);

    /**
     * Get a list of tiers for the specified progression using pagination settings
     *
     * @param ProgressionKey The key of the progression for which you want to get the tiers
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The tier step (non inclusive) to start getting tiers from. Set to 0 to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Game Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequest);

    //==================================================
    // Player Progressions
    //==================================================

    /**
     * Get a list of progressions for the specified player
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedProgressionsForPlayer
     *
     * @param PlayerID ID of the player for whom to get progressions
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressionsForPlayer(int PlayerID, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a list of progressions for the specified player
     *
     * @param PlayerID ID of the player for whom to get progressions
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedProgressionsForPlayer(int PlayerID, int32 Count, const FString& After, const FLootLockerServerPlayerProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a specific progression for the specified player
     *
     * @param PlayerID ID of the player for whom to get the specified progression
     * @param ProgressionKey Key of the progression to get
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressionForPlayerByKey(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionResponseBP& OnCompletedRequest);

    /**
     * Add points to the specified progression for the specified player
     *
     * @param PlayerID ID of the player for whom to add points to the specified progression
     * @param ProgressionKey Key of the progression to add points to for the specified player
     * @param Amount The number of points to add to the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static UPARAM(DisplayName = "RequestId") FString AddPointsToProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Subtract points from the specified progression for the specified player
     *
     * @param PlayerID ID of the player for whom to subtract points from the specified progression
     * @param ProgressionKey Key of the progression to subtract points from for the specified player
     * @param Amount The number of points to subtract from the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static UPARAM(DisplayName = "RequestId") FString SubtractPointsFromProgressionForPlayer(int PlayerID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Reset the specified progression for the specified player
     *
     * @param PlayerID ID of the player for whom to reset the specified progression
     * @param ProgressionKey Key of the progression to reset for the specified player
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static UPARAM(DisplayName = "RequestId") FString ResetProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerSinglePlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Delete the specified progression for the specified player
     *
     * @param PlayerID ID of the player for whom to delete the specified progression
     * @param ProgressionKey Key of the progression to delete for the specified player
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Player Progressions")
    static UPARAM(DisplayName = "RequestId") FString DeleteProgressionForPlayer(int PlayerID, const FString& ProgressionKey, const FLootLockerServerDeletePlayerProgressionResponseBP& OnCompletedRequest);

    //==================================================
    // Character Progressions
    //==================================================

    /**
     * Get a list of progressions for the specified player and character
     * The list will contain the first 20 items, if you want to get more items or not list items from somewhere else than the beginning; use GetPaginatedProgressionsForCharacter
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to get progressions
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressionsForCharacter(int PlayerID, int CharacterID, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a list of progressions for the specified player and character
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to get progressions
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedProgressionsForCharacter(int PlayerID, int CharacterID, int32 Count, const FString& After, const FLootLockerServerCharacterProgressionListResponseBP& OnCompletedRequest);

    /**
     * Get a specific progression for the specified player and character
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to get the specified progression
     * @param ProgressionKey Key of the progression to get
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressionForCharacterByKey(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionResponseBP& OnCompletedRequest);

    /**
     * Add points to the specified progression for the specified player and character
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to add points to the specified progression
     * @param ProgressionKey Key of the progression to add points to for the specified player and character
     * @param Amount The number of points to add to the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static UPARAM(DisplayName = "RequestId") FString AddPointsToProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Subtract points from the specified progression for the specified player and character
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to subtract points from the specified progression
     * @param ProgressionKey Key of the progression to subtract points from for the specified player and character
     * @param Amount The number of points to subtract from the specified progression (only positive integers allowed)
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static UPARAM(DisplayName = "RequestId") FString SubtractPointsFromProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Reset the specified progression for the specified player and character
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to reset the specified progression
     * @param ProgressionKey Key of the progression to reset for the specified player and character
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static UPARAM(DisplayName = "RequestId") FString ResetProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerSingleCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     * Delete the specified progression for the specified player and character
     *
     * @param PlayerID ID of the player the specified character belongs to
     * @param CharacterID ID of the character for which to delete the specified progression
     * @param ProgressionKey Key of the progression to delete for the specified player and character
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Character Progressions")
    static UPARAM(DisplayName = "RequestId") FString DeleteProgressionForCharacter(int PlayerID, int CharacterID, const FString& ProgressionKey, const FLootLockerServerDeleteCharacterProgressionResponseBP& OnCompletedRequest);

    //==================================================
    // Instance Progressions
    //==================================================

     /**
     * Get a list of progressions for the specified instance
     * The list will contain the first 20 items, if you want to get more items or list items from somewhere else than the beginning; use GetPaginatedProgressionsForInstance
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP);

     /**
     * Get a list of progressions for the specified instance
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param Count The number of progressions to get. Must be a value between 1 and 100
     * @param After The id of the progression from where to start getting progressions (non inclusive). Set to "" to start from the first item
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetPaginatedProgressionForAssetInstance(int PlayerId, int AssetInstanceId, int32 Count, const FString& After, const FLootLockerServerInstanceProgressionListResponseBP& OnCompletedRequestBP);

     /**
     * Get a specific progression for the specified instance
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param ProgressionKey Key of the progression to get
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static UPARAM(DisplayName = "RequestId") FString GetProgressionByKeyForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionResponseBP& OnCompletedRequestBP);

    /**
    * Add points to the specified progression for the specified instance
    *
    * @param AssetInstanceId ID of the instance the specified progression belongs to
    * @param ProgressionKey Key of the progression to add points to for the specified instance
    * @param Amount The number of points to add to the specified progression (only positive integers allowed)
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static UPARAM(DisplayName = "RequestId") FString AddPointsToProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);
    
    /**
    * Subtract points from the specified progression for the specified instance
    *
    * @param AssetInstanceId ID of the instance the specified progression belongs to
    * @param ProgressionKey Key of the progression to subtract points from for the specified instance
    * @param Amount The number of points to subtract from the specified progression (only positive integers allowed)
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static UPARAM(DisplayName = "RequestId") FString SubtractPointsFromProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, int32 Amount, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
     * Reset the specified progression for the specified instance
     *
     * @param AssetInstanceId ID of the instance the specified progression belongs to
     * @param ProgressionKey Key of the progression to reset for the specified instance
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static UPARAM(DisplayName = "RequestId") FString ResetProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerSingleInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
    * Delete the specified progression for the specified instance
    *
    * @param AssetInstanceId ID of the instance the specified progression belongs to
    * @param ProgressionKey Key of the progression to delete for the specified instance
    * @param OnCompletedRequest Delegate for handling the server response
    * 
    * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Instance Progressions")
    static UPARAM(DisplayName = "RequestId") FString DeleteProgressionForAssetInstance(int PlayerId, int AssetInstanceId, const FString& ProgressionKey, const FLootLockerServerDeleteInstanceProgressionResponseBP& OnCompletedRequestBP);

    //==================================================
    // Currencies
    //==================================================

    /**
     * Get a list of available currencies for the game
     *
     * @param OnCompletedRequest Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Currency")
    static UPARAM(DisplayName = "RequestId") FString ListCurrencies(const FLootLockerServerListCurrenciesResponseBP& OnCompletedRequest);

    //==================================================
    // Catalogs
    //==================================================

    /**
     List catalog items (entries with prices) for the catalog identified by the given key.

     Use Count and After for cursor-based pagination. Pass After = "" and Count = 0 to get the
     first page with the default page size.

     @param CatalogKey The unique key of the catalog to list items for
     @param Count Optional: number of items to return per page (0 = server default, typically 50)
     @param After Optional: cursor from a previous response's Pagination.Next_cursor to get the next page; pass empty string for the first page
     @param OnCompletedRequestBP Delegate for handling the server response

     @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Catalogs", meta = (AdvancedDisplay = "Count,After", Count = 0, After = ""))
    static UPARAM(DisplayName = "RequestId") FString ListCatalogItemsByKey(const FString& CatalogKey, int Count, const FString& After, const FLootLockerServerListCatalogPricesResponseBP& OnCompletedRequestBP);

    //==================================================
    // Balances
    //==================================================

    /**
     * Get a list of balances in a specified wallet
     *
     * @param WalletID Unique ID of the wallet to get balances for
     * @param OnComplete Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static UPARAM(DisplayName = "RequestId") FString ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseBP& OnComplete);

    /**
     * Get information about a specified wallet
     *
     * @param WalletID Unique ID of the wallet to get information for
     * @param OnComplete Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static UPARAM(DisplayName = "RequestId") FString GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseBP& OnComplete);

    /**
     * Get information about a wallet for a specified holder
     *
     * @param HolderULID ULID of the holder of the wallet you want to get information for
     * @param HolderType The type of the holder to get the wallet for
     * @param OnComplete Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static UPARAM(DisplayName = "RequestId") FString GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseBP& OnComplete);

    /**
     * Credit (increase) the specified amount of the provided currency to the provided wallet
     *
     * @param WalletID Unique ID of the wallet to credit the given amount of the given currency to
     * @param CurrencyID Unique ID of the currency to credit
     * @param Amount The amount of the given currency to credit to the given wallet
     * @param OnComplete Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static UPARAM(DisplayName = "RequestId") FString CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseBP& OnComplete);

    /**
     * Debit (decrease) the specified amount of the provided currency to the provided wallet
     *
     * @param WalletID Unique ID of the wallet to debit the given amount of the given currency from
     * @param CurrencyID Unique ID of the currency to debit
     * @param Amount The amount of the given currency to debit from the given wallet
     * @param OnComplete Delegate for handling the server response
     * 
     * @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Balance")
    static UPARAM(DisplayName = "RequestId") FString DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseBP& OnComplete);

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
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Page,PerPage,IgnoreFiles", Page = -1, PerPage = -1, IgnoreFiles = false))
    static UPARAM(DisplayName = "RequestId") FString ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete);

    /**
    List the requested page of Metadata for the specified source that has all of the provided tags and paginate according to the supplied pagination settings (if you don't specify pagination settings then default pagination will be used)

    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata
    @param Tags The tags that the requested metadata should have, only metadata matching *all of* the given tags will be returned
    @param Page Optional: Used together with PerPage to apply pagination to this request. Page designates which "page" of items to fetch
    @param PerPage Optional: Used together with Page to apply pagination to this request.PerPage designates how many items are considered a "page"
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Page,PerPage,Tags,IgnoreFiles", Page = -1, PerPage = -1, IgnoreFiles = false))
    static UPARAM(DisplayName = "RequestId") FString ListMetadataWithTags(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnComplete);

    /**
    Get Metadata for the specified source with the given key

    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata
    @param Key The key of the metadata to fetch, use this to fetch metadata for a specific key for the specified source.
    @param OnComplete delegate for handling the server response
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "IgnoreFiles", IgnoreFiles = false))
    static UPARAM(DisplayName = "RequestId") FString GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerServerGetMetadataResponseBP& OnComplete);

    /**
    Get Metadata for the specified keys on the specified sources

    @param SourcesAndKeysToGet The combination of sources to get keys for, and the keys to get for those sources
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "IgnoreFiles", IgnoreFiles = false))
    static UPARAM(DisplayName = "RequestId") FString GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerServerGetMultisourceMetadataResponseBP& OnComplete);

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
     
     @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata", meta = (ExpandEnumAsExecs = "MetadataTypeSwitch", AdvancedDisplay = "OutEntry"))
    static UPARAM(DisplayName = "RequestId") FString ParseLootLockerServerMetadataEntry(const FLootLockerServerMetadataEntry& Entry,
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
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Metadata")
    static UPARAM(DisplayName = "RequestId") FString SetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerServerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerServerSetMetadataResponseBP& OnComplete);

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
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    */
    UFUNCTION(BlueprintPure, Category = "LootLockerServer Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static UPARAM(DisplayName = "RequestId") FString MakeMetadataActionJson(ELootLockerServerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access, bool& Succeeded, FLootLockerServerSetMetadataAction& ConstructedEntry);

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


    //==================================================
    // Notifications
    //==================================================

    /*
    Send a custom notification using the notification system to the specified player.

    @param Content The content to send along with this notification
    @param NotificationType The "type" of this notification. Use this to identify your notifications and segment them from each other. You can set this to any value as long as it follows pattern ^[-_a-z0-9]+\\.[-_a-z0-9]+\\.[-_a-z0-9]+$.
    @param Priority What priority to set for this notification
    @param RecipientPlayerUlid The ulid of the player that should receive this notification
    @param Properties An array of key value pairs to send with this notification. The player can read these key value pairs in the context dictionary.
    @param OnComplete delegate for handling the server response
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
	*/
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Notifications", CustomThunk, meta=(CustomStructureParam="Content", AutoCreateRefTerm="Properties"))
    static UPARAM(DisplayName = "RequestId") FString SendNotificationToPlayer(const int& Content, const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequest);
    DECLARE_FUNCTION(execSendNotificationToPlayer);

    /*
    Send a custom notification using the notification system to the specified player.

    @param NotificationType The "type" of this notification. Use this to identify your notifications and segment them from each other. You can set this to any value as long as it follows pattern ^[-_a-z0-9]+\\.[-_a-z0-9]+\\.[-_a-z0-9]+$.
    @param Priority What priority to set for this notification
    @param RecipientPlayerUlid The ulid of the player that should receive this notification
    @param Properties An array of key value pairs to send with this notification. The player can read these key value pairs in the context dictionary.
    @param OnComplete delegate for handling the server response
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | Notifications", meta = (AutoCreateRefTerm = "Properties"))
    static UPARAM(DisplayName = "RequestId") FString SendNotificationToPlayerWithoutContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequest);
};
