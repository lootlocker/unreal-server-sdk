// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerServerConfig.h"

#include "LootLockerServerEndpoints.generated.h"

UENUM(BlueprintType)
enum class ELootLockerServerHTTPMethod : uint8
{
    GET = 0         UMETA(DisplayName = "GET"),
    POST = 1        UMETA(DisplayName = "POST"),
    DELETE = 2      UMETA(DisplayName = "DELETE"),
    PUT = 3         UMETA(DisplayName = "PUT"),
    HEAD = 4        UMETA(DisplayName = "HEAD"),
    CREATE = 5      UMETA(DisplayName = "CREATE"),
    OPTIONS = 6     UMETA(DisplayName = "OPTIONS"),
    PATCH = 7       UMETA(DisplayName = "PATCH"),
    UPLOAD = 8      UMETA(DisplayName = "UPLOAD")
};

USTRUCT(BlueprintType)
struct FLootLockerServerEndPoint
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString endpoint = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    ELootLockerServerHTTPMethod requestMethod = ELootLockerServerHTTPMethod::GET;

	FString GetRequestMethodString() const
    {
        return GetDefault<ULootLockerServerConfig>()->GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(requestMethod));
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
    static FLootLockerServerEndPoint CreateLeaderboard;
    static FLootLockerServerEndPoint UpdateLeaderboard;
    static FLootLockerServerEndPoint DeleteLeaderboard;
    static FLootLockerServerEndPoint SubmitScore;
    static FLootLockerServerEndPoint GetAllMemberRanks;
    static FLootLockerServerEndPoint GetScoresFromLeaderboard;

    // Assets
    static FLootLockerServerEndPoint GetAssets;

    // Asset Instances
    static FLootLockerServerEndPoint GetAssetInstanceKeyValuePairs;
    static FLootLockerServerEndPoint GetAssetInstanceKeyValuePairById;
    static FLootLockerServerEndPoint AddKeyValuePairToAssetInstance;
    static FLootLockerServerEndPoint UpdateKeyValuePairs;
    static FLootLockerServerEndPoint UpdateKeyValuePairById;
    static FLootLockerServerEndPoint DeleteKeyValuePairById;

    // Drop Tables
    static FLootLockerServerEndPoint ComputeAndLockDropTable;
    static FLootLockerServerEndPoint PickDropsFromDropTable;

    // Player Lookup
    static FLootLockerServerEndPoint LookupMultiplePlayerNamesUsingIDs;

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

private:
    static FString GameBaseUrl;

    static FLootLockerServerEndPoint InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method);
};
