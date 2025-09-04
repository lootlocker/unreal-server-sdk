#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerFriendsRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Details about a particular friend
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerFriend
{
    GENERATED_BODY()
    /**
     * The ulid of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Player_id = "";
    /**
     * The name (if any has been set) of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
    /**
     * The public uid of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Public_uid = "";
    /**
     * The online status of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Online = false;
    /**
     * The creation date of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Accepted_at = "";
    /**
     * The creation date of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at = "";
};

//==================================================
// Request Definitions
//==================================================

// N/A

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerListFriendsResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     * List of friends that the specified player has
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerFriend> Friends;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================

/**
 * Blueprint response delegate for listing currencies
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListFriendsResponseBP, FLootLockerServerListFriendsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for listing currencies
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListFriendsResponseDelegate, FLootLockerServerListFriendsResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerFriendsRequest : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerFriendsRequest();

    static void ListFriends(const FString& PlayerULID, const FLootLockerServerListFriendsResponseBP& OnResponseCompletedBP = FLootLockerServerListFriendsResponseBP(), const FLootLockerServerListFriendsResponseDelegate& OnResponseCompleted = FLootLockerServerListFriendsResponseDelegate());
};
