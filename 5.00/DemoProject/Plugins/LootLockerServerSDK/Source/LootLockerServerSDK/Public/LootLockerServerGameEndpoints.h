// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerServerConfig.h"

#include "LootLockerServerGameEndpoints.generated.h"

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerGameEndpoints : public UObject
{
    GENERATED_BODY()
public:
    //Auth
    static FLootLockerServerEndPoints StartSessionEndpoint;
    static FLootLockerServerEndPoints MaintainingSessionEndpoint;
    //Assets
    static FLootLockerServerEndPoints GetAssetsToGameEndpoint;
    //Player Inventory
    static FLootLockerServerEndPoints GetPlayerInventoryEndpoint;
    static FLootLockerServerEndPoints AddAssetsToPlayerInventoryEndpoint;
    static FLootLockerServerEndPoints AlterPlayerInventoryEndpoint;
    static FLootLockerServerEndPoints GetPlayerLoadoutEndpoint;
    static FLootLockerServerEndPoints EquipAssetToPlayerLoadoutEndpoint;
    static FLootLockerServerEndPoints UnEquipAssetToPlayerLoadoutEndpoint;
    //Player persistent storage
    static FLootLockerServerEndPoints GetPersistentStorageEndpoint;
    static FLootLockerServerEndPoints UpdatePersistentStorageEndpoint;
    //Player files
    static FLootLockerServerEndPoints ListFilesForPlayerEndpoint;
    static FLootLockerServerEndPoints GetFileByIdForPlayerEndpoint;
    static FLootLockerServerEndPoints UploadFileForPlayerEndpoint;
    static FLootLockerServerEndPoints DeleteFileForPlayerEndpoint;
    //Characters & Heroes
    static FLootLockerServerEndPoints GetPlayerCharactersEndpoint;
    static FLootLockerServerEndPoints GetInventorytoCharacterEndpoint;
    static FLootLockerServerEndPoints GetCharacterLoadoutEndpoint;
    static FLootLockerServerEndPoints EquipAssetforCharacterLoadoutEndpoint;
    static FLootLockerServerEndPoints UnequipAssetforCharacterLoadoutEndpoint;
    static FLootLockerServerEndPoints GetPlayerHeroesEndpoint;
    static FLootLockerServerEndPoints GetInventorytoHeroEndpoint;
    static FLootLockerServerEndPoints GetHeroLoadoutEndpoint;
    static FLootLockerServerEndPoints EquipAssetforHeroLoadoutEndpoint;
    static FLootLockerServerEndPoints UnequipAssetforHeroLoadoutEndpoint;
    //Trigger
    static FLootLockerServerEndPoints InvokeTriggeronBehalfofPlayerEndpoint;
    //Leaderboard
    static FLootLockerServerEndPoints CreateLeaderboardEndpoint;
    static FLootLockerServerEndPoints UpdateLeaderboardEndpoint;
    static FLootLockerServerEndPoints DeleteLeaderboardEndpoint;
    static FLootLockerServerEndPoints SubmitScoreEndpoint;

    //DropTables
    static FLootLockerServerEndPoints ComputeAndLockDropTableEndpoint;
    static FLootLockerServerEndPoints PickDropsFromDropTableEndpoint;

private:
    static FString GameBaseUrl;

    static FLootLockerServerEndPoints InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method);
};
