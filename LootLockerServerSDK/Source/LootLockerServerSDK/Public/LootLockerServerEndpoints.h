// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerServerConfig.h"
#include "Utils/LootLockerServerUtilities.h"

#include "LootLockerServerEndpoints.generated.h"

UENUM(BlueprintType)
enum class ELootLockerServerHTTPMethod : uint8
{
    LL_GET = 0         UMETA(DisplayName = "GET"),
    LL_POST = 1        UMETA(DisplayName = "POST"),
    LL_DELETE = 2      UMETA(DisplayName = "DELETE"),
    LL_PUT = 3         UMETA(DisplayName = "PUT"),
    LL_HEAD = 4        UMETA(DisplayName = "HEAD"),
    LL_CREATE = 5      UMETA(DisplayName = "CREATE"),
    LL_OPTIONS = 6     UMETA(DisplayName = "OPTIONS"),
    LL_PATCH = 7       UMETA(DisplayName = "PATCH"),
    LL_UPLOAD = 8      UMETA(DisplayName = "UPLOAD")
};

/**
 * Maps ELootLockerServerHTTPMethod to the verb sent in the HTTP request line.
 *
 * The mapping is written out explicitly rather than read back from the enum's DisplayName
 * metadata: UEnum::GetDisplayNameTextByValue() only honours UMETA(DisplayName=...) when
 * WITH_EDITOR is set (WITH_METADATA is WITH_EDITORONLY_DATA, so the metadata is stripped at
 * cook time) and silently falls back to the C++ enumerator name in a packaged build.
 *
 * Keep this switch exhaustive; it has no default so that adding a member to the enum produces
 * a -Wswitch build error rather than a silently wrong verb.
 */
namespace LootLockerServerHttpMethodUtils
{
    inline FString GetVerbString(ELootLockerServerHTTPMethod Method)
    {
        switch (Method)
        {
        case ELootLockerServerHTTPMethod::LL_GET:     return TEXT("GET");
        case ELootLockerServerHTTPMethod::LL_POST:    return TEXT("POST");
        case ELootLockerServerHTTPMethod::LL_DELETE:  return TEXT("DELETE");
        case ELootLockerServerHTTPMethod::LL_PUT:     return TEXT("PUT");
        case ELootLockerServerHTTPMethod::LL_HEAD:    return TEXT("HEAD");
        case ELootLockerServerHTTPMethod::LL_CREATE:  return TEXT("CREATE");
        case ELootLockerServerHTTPMethod::LL_OPTIONS: return TEXT("OPTIONS");
        case ELootLockerServerHTTPMethod::LL_PATCH:   return TEXT("PATCH");
        case ELootLockerServerHTTPMethod::LL_UPLOAD:  return TEXT("UPLOAD");
        }
        return TEXT("");
    }
}

USTRUCT(BlueprintType)
struct FLootLockerServerEndPoint
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString endpoint = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    ELootLockerServerHTTPMethod requestMethod = ELootLockerServerHTTPMethod::LL_GET;

	FString GetRequestMethodString() const
    {
        return LootLockerServerHttpMethodUtils::GetVerbString(requestMethod);
    }
};

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerEndpoints : public UObject
{
    GENERATED_BODY()
public:
    // Auth
    static FLootLockerServerEndPoint StartSession;
    static FLootLockerServerEndPoint MaintainingSession;

    // Leaderboards
    static FLootLockerServerEndPoint ListLeaderboards;
    static FLootLockerServerEndPoint GetLeaderboard;
    static FLootLockerServerEndPoint CreateLeaderboard;
    static FLootLockerServerEndPoint UpdateLeaderboard;
    static FLootLockerServerEndPoint DeleteLeaderboard;
    static FLootLockerServerEndPoint SubmitScore;
    static FLootLockerServerEndPoint IncrementScore;
    static FLootLockerServerEndPoint GetAllMemberRanks;
    static FLootLockerServerEndPoint GetScoresFromLeaderboard;
    static FLootLockerServerEndPoint ListLeaderboardArchive;
    static FLootLockerServerEndPoint GetLeaderboardArchive;
    static FLootLockerServerEndPoint GetLeaderboardSchedule;
    static FLootLockerServerEndPoint CreateLeaderboardSchedule;
    static FLootLockerServerEndPoint DeleteLeaderboardSchedule;
    static FLootLockerServerEndPoint RequestManualLeaderboardReset;
    static FLootLockerServerEndPoint ListManualLeaderboardResets;
    static FLootLockerServerEndPoint GetManualLeaderboardReset;
    static FLootLockerServerEndPoint CancelManualLeaderboardReset;

    // Assets
    static FLootLockerServerEndPoint GetAssets;
    static FLootLockerServerEndPoint ListAssets;
    static FLootLockerServerEndPoint ListContexts;

    // Asset Instances
    static FLootLockerServerEndPoint GetAssetInstanceKeyValuePairs;
    static FLootLockerServerEndPoint GetAssetInstanceKeyValuePairById;
    static FLootLockerServerEndPoint AddKeyValuePairToAssetInstance;
    static FLootLockerServerEndPoint UpdateKeyValuePairs;
    static FLootLockerServerEndPoint UpdateKeyValuePairById;
    static FLootLockerServerEndPoint DeleteKeyValuePairById;

    //Asset Instance Progressions
    static FLootLockerServerEndPoint GetAllInstanceProgressions;
    static FLootLockerServerEndPoint GetSingleInstanceProgression;
    static FLootLockerServerEndPoint AddPointsToInstanceProgression;
    static FLootLockerServerEndPoint SubtractPointsFromInstanceProgression;
    static FLootLockerServerEndPoint ResetInstanceProgression;
    static FLootLockerServerEndPoint DeleteInstanceProgression;

    // Drop Tables
    static FLootLockerServerEndPoint ComputeAndLockDropTable;
    static FLootLockerServerEndPoint PickDropsFromDropTable;

    // Friends
    static FLootLockerServerEndPoint ListFriends;

    // Player Operations
    static FLootLockerServerEndPoint CreatePlayer;
    
    // Player Lookup
    static FLootLockerServerEndPoint GetPlayerInfoFromGameSessionToken;
    static FLootLockerServerEndPoint LookupMultiplePlayerNamesUsingIDs;

    // Connected Accounts
    static FLootLockerServerEndPoint ListConnectedAccounts;

    // Player Inventory
    static FLootLockerServerEndPoint GetPlayerInventory;
    static FLootLockerServerEndPoint GetUniversalInventory;
    static FLootLockerServerEndPoint AddAssetToPlayerInventory;
    static FLootLockerServerEndPoint AlterPlayerInventory;
    static FLootLockerServerEndPoint GetPlayerLoadout;
    static FLootLockerServerEndPoint EquipAssetToPlayerLoadout;
    static FLootLockerServerEndPoint UnEquipAssetFromPlayerLoadout;

    // Player Persistent Storage
    static FLootLockerServerEndPoint GetPlayerPersistentStorage;
    static FLootLockerServerEndPoint GetMultiplePlayersPublicPersistentStorageValues;
    static FLootLockerServerEndPoint UpdatePlayerPersistentStorage;
    static FLootLockerServerEndPoint DeletePlayerPersistentStorage;
    static FLootLockerServerEndPoint ListPlayerFiles;
    static FLootLockerServerEndPoint GetPlayerFileById;
    static FLootLockerServerEndPoint DeletePlayerFile;
    static FLootLockerServerEndPoint UploadPlayerFile;
    static FLootLockerServerEndPoint UpdatePlayerFile;
    static FLootLockerServerEndPoint ListPlayerFileRevisions;
    static FLootLockerServerEndPoint GetPlayerFileRevision;
    static FLootLockerServerEndPoint PromotePlayerFileRevision;
    static FLootLockerServerEndPoint GetPlayerFileByKey;
    static FLootLockerServerEndPoint ListPlayerFileRevisionsByKey;
    static FLootLockerServerEndPoint GetPlayerFileRevisionByKey;
    static FLootLockerServerEndPoint PromotePlayerFileRevisionByKey;
    static FLootLockerServerEndPoint DeletePlayerFileByKey;

    // Triggers
    static FLootLockerServerEndPoint InvokeTriggerForPlayer;

    // Characters
    static FLootLockerServerEndPoint GetPlayerCharacters;
    static FLootLockerServerEndPoint GetCharacterInventory;
    static FLootLockerServerEndPoint GetCharacterLoadout;
    static FLootLockerServerEndPoint EquipAssetToCharacterLoadout;
    static FLootLockerServerEndPoint UnequipAssetFromCharacterLoadout;

    // Heroes
    static FLootLockerServerEndPoint GetPlayerHeroes;
    static FLootLockerServerEndPoint GetHeroInventory;
    static FLootLockerServerEndPoint GetHeroLoadout;
    static FLootLockerServerEndPoint EquipAssetToHeroLoadout;
    static FLootLockerServerEndPoint UnequipAssetFromHeroLoadout;
    
    // Purchases
    static FLootLockerServerEndPoint CheckPurchaseStatus;

    // Game Progressions
    static FLootLockerServerEndPoint GetAllProgressions;
    static FLootLockerServerEndPoint GetProgression;
    static FLootLockerServerEndPoint GetProgressionTiers;

    // Player Progressions
    static FLootLockerServerEndPoint GetProgressionsForPlayer;
    static FLootLockerServerEndPoint GetProgressionsByKeyForPlayer;
    static FLootLockerServerEndPoint AddPointsToProgressionForPlayer;
    static FLootLockerServerEndPoint SubtractPointsFromProgressionForPlayer;
    static FLootLockerServerEndPoint ResetProgressionForPlayer;
    static FLootLockerServerEndPoint DeleteProgressionForPlayer;

    // Character Progressions
    static FLootLockerServerEndPoint GetProgressionsForCharacter;
    static FLootLockerServerEndPoint GetProgressionsByKeyForCharacter;
    static FLootLockerServerEndPoint AddPointsToProgressionForCharacter;
    static FLootLockerServerEndPoint SubtractPointsFromProgressionForCharacter;
    static FLootLockerServerEndPoint ResetProgressionForCharacter;
    static FLootLockerServerEndPoint DeleteProgressionForCharacter;

    // Currencies
    static FLootLockerServerEndPoint ListCurrencies;

    // Catalogs
    static FLootLockerServerEndPoint ListCatalogItemsByKey;
    static FLootLockerServerEndPoint ListCatalogItemsById;

    // Balances
    static FLootLockerServerEndPoint ListBalancesInWallet;
    static FLootLockerServerEndPoint GetWalletByWalletId;
    static FLootLockerServerEndPoint GetWalletByHolderId;
    static FLootLockerServerEndPoint CreditBalanceToWallet;
    static FLootLockerServerEndPoint DebitBalanceToWallet;
    static FLootLockerServerEndPoint CreateWallet;

    // Metadata
    static FLootLockerServerEndPoint ListMetadata;
    static FLootLockerServerEndPoint MetadataActions;
    static FLootLockerServerEndPoint GetMultisourceMetadata;

    // Token Exchange
    static FLootLockerServerEndPoint TokenExchange;

    // Notifications
    static FLootLockerServerEndPoint SendNotification;

    // Items
    static FLootLockerServerEndPoint ListPlayerInventoryItems;
    static FLootLockerServerEndPoint GetPlayerInventoryItem;
    static FLootLockerServerEndPoint DeletePlayerInventoryItem;
    static FLootLockerServerEndPoint GrantItemToPlayerInventory;
    static FLootLockerServerEndPoint SplitPlayerInventoryItemStack;
    static FLootLockerServerEndPoint MergePlayerInventoryItemStacks;

private:
    static FString GameBaseUrl;
    static FString ServerApiUrlSuffix;
    static FString ClientApiUrlSuffix;
    static FLootLockerServerEndPoint InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method, const FString& BaseUrlSuffix = ServerApiUrlSuffix);
};
