// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerLeaderboardRequest.generated.h"

//==================================================
// Enum Definitions
//==================================================
UENUM(BlueprintType)
enum class ELootLockerServerLeaderboardType : uint8
{
    /*
     Meant for LootLocker player leaderboards.
     When submitting scores you must use player_id, but when retrieving data LootLocker will automatically attach player data such as name and other public data on that player.
     */
    player = 0         UMETA(DisplayName = "Player"),
    /*
     Use this if you want do not want the extended player details from the player type leaderboard.
     This type allows you to create leaderboards not meant for players (guild/clan for example), or if your player data is not stored in LootLocker.
     */
    generic = 1        UMETA(DisplayName = "Generic"),
};

/*
 Which direction should the leaderboard be sorted in
 */
UENUM(BlueprintType)
enum class ELootLockerServerLeaderboardDirection : uint8
{
    /*
     Sort from lowest to highest, meaning the lowest number is highest on the leaderboard
     */
    ascending = 0         UMETA(DisplayName = "Ascending"),
    /*
     Sort from highest to lowest, meaning the highest number is highest on the leaderboard
     */
    descending = 1        UMETA(DisplayName = "Descending"),
};

/*
 Which kind of reward this leaderboard contains
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerServerLeaderboardRewardEntityKind : uint8
{
    Asset = 0,
    Currency = 1,
    Progression_Points = 2,
    Progression_Reset = 3,
    Group = 4,
};

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardPlayer
{
    GENERATED_BODY()
    /*
     The ID of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int ID = 0;
    /*
    The public UID of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Public_uid = "";
    /*
    The name of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardEntry
{
    GENERATED_BODY()
    /*
     The Identifying member ID for this entry in the leaderboard.
     For player leaderboards this will be the Player ID, for generic leaderboards this will be the member_id you submitted
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_id = "";
    /*
    The rank for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Rank = 0;
    /*
    The score for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score = 0;
    /*
    Player information for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardPlayer Player;
    /*
    The metadata for this entry in the leaderboard.
    This will be empty if the leaderboard does not support metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardEntryWithLeaderboardData
{
    GENERATED_BODY()
    /*
    The ID of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Leaderboard_id = 0;
    /*
    The unique key for this leaderboard, used 
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Leaderboard_key = "";
    /*
     * The ulid of this leaderboard
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Ulid = "";
    /*
     The entry of the player in this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardEntry Rank;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAssetRewardDetails
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString thumbnail;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString variation_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString rental_option_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int legacy_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString id;

};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardAssetReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerAssetRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString asset_rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString reward_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString asset_ulid;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCurrencyRewardDetails
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString code;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString amount;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardCurrencyReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString amount;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerCurrencyRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString reward_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString currency_id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerProgressionResetRewardDetails
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardProgressionResetReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString progression_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerProgressionResetRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString reward_id;

};

USTRUCT(BlueprintType)
struct FLootLockerServerProgressionPointRewardDetails
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int amount = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString id;
};


USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardProgressionPointsReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerProgressionPointRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int amount = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString progression_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString reward_id;

};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardRewardArgs
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int max = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int min = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString direction;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardDetailPredicates
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardRewardArgs args;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardSchedule
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString cron_expression;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString next_run;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString last_run;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> schedule;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardGroupRewardAssociation
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardRewardEntityKind kind = ELootLockerServerLeaderboardRewardEntityKind::Asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardCurrencyReward currency;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardProgressionResetReward progression_reset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardProgressionPointsReward progression_points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardAssetReward asset;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardGroupRewardMetadata
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString value;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardGroupReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString description;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboardGroupRewardMetadata> metadata;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboardGroupRewardAssociation> associations;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString reward_id;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardRewardEntityKind reward_kind = ELootLockerServerLeaderboardRewardEntityKind::Asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboardDetailPredicates> predicates;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardCurrencyReward currency;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardProgressionResetReward progression_reset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardProgressionPointsReward progression_points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardAssetReward asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardGroupReward group;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString reward_id;

};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboard
{
    GENERATED_BODY()
    /*
    The ID of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int ID = 0;
    /*
    The ID of the game this leaderboard is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Game_id = 0;
    /*
    The unique key of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key = "";
    /*
     * The ulid of this leaderboard
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Ulid = "";
    /*
    The name of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
    /*
    The type of leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardType Type = ELootLockerServerLeaderboardType::player;
    /*
    The sort order of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardDirection Direction_method = ELootLockerServerLeaderboardDirection::ascending;
    /*
    Is the game api allowed to write to this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Enable_game_api_writes = false;
    /*
    Do new submits overwrite existing scores for members on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Overwrite_score_on_submit = false;
    /*
    Is metadata enabled on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Has_metadata = false;
    /*
    The creation time of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at = "";
    /*
    The last time this leaderboard was updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at = "";
    /*
     * Schedule of the Leaderboard.
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardSchedule Schedule;
    /*
     * A List of rewards tied to the Leaderboard.
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboardReward> Rewards;
};

//==================================================
// Request Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardSubmitScoreRequest
{
    GENERATED_BODY()
    /*
     The Identifying member ID for this entry in the leaderboard.
     For player leaderboards this will be the PlayerID, for generic leaderboards you can send in any string and that will be the identifier. We recommend using the player's Public_UID or Name.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_id = "";
    /*
    The Score to submit for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score = 0;
    /*
    The Metadata to submit for this entry in the leaderboard.
    If the leaderboard does not support metadata this property will be ignored.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardBaseRequest
{
    GENERATED_BODY()
    // Constructor
public:
    FLootLockerServerLeaderboardBaseRequest(const FString& InKey,
        const FString& InName,
        ELootLockerServerLeaderboardDirection InDirectionMethod,
        bool InEnableGameApiWrites,
        bool InOverwriteScoreOnSubmit)
        : Key(InKey),
        Name(InName),
        Direction_method(InDirectionMethod),
        Enable_game_api_writes(InEnableGameApiWrites),
        Overwrite_score_on_submit(InOverwriteScoreOnSubmit)
    {
    }

    FLootLockerServerLeaderboardBaseRequest()
    {
	}
    /*
    The unique key of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key = "";
    /*
    The name of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
    /*
    The sort order of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardDirection Direction_method = ELootLockerServerLeaderboardDirection::ascending;
    /*
    Allow the game api to write to this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Enable_game_api_writes = false;
    /*
    Always overwrite existing scores for members on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Overwrite_score_on_submit = false;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardRequest : public FLootLockerServerLeaderboardBaseRequest
{

    GENERATED_BODY()
    // Constructor
public:
    FLootLockerServerCreateLeaderboardRequest(const FString& InKey,
        const FString& InName,
        ELootLockerServerLeaderboardDirection InDirectionMethod,
        bool InEnableGameApiWrites,
        bool InOverwriteScoreOnSubmit)
        : FLootLockerServerLeaderboardBaseRequest(InKey, InName, InDirectionMethod, InEnableGameApiWrites, InOverwriteScoreOnSubmit)
    {
    }

    FLootLockerServerCreateLeaderboardRequest()
    {
	}
    
    /*
    The type of leaderboard to create
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardType Type = ELootLockerServerLeaderboardType::player;
    /*
    Enable metadata on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Has_metadata = false;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdateLeaderboardRequest : public FLootLockerServerLeaderboardBaseRequest
{
	GENERATED_BODY()
public:
    FLootLockerServerUpdateLeaderboardRequest(const FString& InKey,
        const FString& InName,
        ELootLockerServerLeaderboardDirection InDirectionMethod,
        bool InEnableGameApiWrites,
        bool InOverwriteScoreOnSubmit)
        : FLootLockerServerLeaderboardBaseRequest(InKey, InName, InDirectionMethod, InEnableGameApiWrites, InOverwriteScoreOnSubmit)
    {
    }

    FLootLockerServerUpdateLeaderboardRequest()
    {
    }
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardScheduleRequest
{
	GENERATED_BODY()
public:
    /*
    The cron expression to use for setting up the schedule. These expressions follow the traditional cron spec. 
    See crontab.guru for a good resource in exploring cron expressions.
    Additionally, we do support non-standard descriptors as follows:
        - @hourly: every hour at minute 00.
        - @daily: everyday, at midnight UTC.
        - @weekly: on Sunday, at midnight UTC.
        - @monthly: on the first day of the month, at midnight UTC.
        - @yearly: on the first day of the year, at midnight UTC.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Cron_expression = "";
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardBaseResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
    The ID of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int ID = 0;
    /*
    The ID of the game this leaderboard is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Game_id = 0;
    /*
    The unique key of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key = "";
    /*
    The name of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
    /*
    The type of leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardType Type = ELootLockerServerLeaderboardType::player;
    /*
    The sort order of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardDirection Direction_method = ELootLockerServerLeaderboardDirection::ascending;
    /*
    Is the game api allowed to write to this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Enable_game_api_writes = false;
    /*
    Do new submits overwrite existing scores for members on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Overwrite_score_on_submit = false;
    /*
    Is metadata enabled on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Has_metadata = false;
    /*
    The creation time of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at = "";
    /*
    The last time this leaderboard was updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetLeaderboardResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     * Data for the leaderboard
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboard Leaderboard;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardResponse : public FLootLockerServerLeaderboardBaseResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdateLeaderboardResponse : public FLootLockerServerLeaderboardBaseResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardSubmitScoreResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     The Identifying member ID for this entry in the leaderboard.
     For player leaderboards this will be the PlayerID, for generic leaderboards this will be the member_id you submitted
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_id = "";
    /*
    The rank for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Rank = 0;
    /*
    The Score for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score = 0;
    /*
    The Metadata for this entry in the leaderboard.
    If the leaderboard does not support metadata this property will be empty.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetAllMemberRanksResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
    Pagination data for the response, use this to make subsequent requests
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerIndexBasedPagination Pagination;
    /*
    Entries for the requested member from the leaderboards they have entries in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboardEntryWithLeaderboardData> Leaderboards;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetScoresFromLeaderboardResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
    Pagination data for the response, use this to make subsequent requests
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerIndexBasedPagination Pagination;
    /*
    List of entries in the requested leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboardEntry> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetLeaderboardScheduleResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString cron_expression;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString next_run;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString last_run;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> schedule;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

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

//==================================================
// C++ Delegate Definitions
//==================================================


/*
 C++ response delegate for getting leaderboard information
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetLeaderboardResponseDelegate, FLootLockerServerGetLeaderboardResponse);
/*
 C++ response delegate for leaderboard creation
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerCreateLeaderboardResponseDelegate, FLootLockerServerCreateLeaderboardResponse);
/*
 C++ response delegate for leaderboard updates
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerUpdateLeaderboardResponseDelegate, FLootLockerServerUpdateLeaderboardResponse);
/*
 C++ response delegate for leaderboard deletion
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardResponseDelegate, FLootLockerServerResponse);
/*
 C++ response delegate for leaderboard score submission
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerLeaderboardSubmitScoreResponseDelegate, FLootLockerServerLeaderboardSubmitScoreResponse);
/*
 C++ response delegate for getting all member ranks
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetAllMemberRanksResponseDelegate, FLootLockerServerGetAllMemberRanksResponse);
/*
 C++ response delegate for getting scores from a leaderboard
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetScoresFromLeaderboardResponseDelegate, FLootLockerServerGetScoresFromLeaderboardResponse);
/*
 C++ response delegate for getting the schedule for a leaderboard
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetLeaderboardScheduleResponseDelegate, FLootLockerServerGetLeaderboardScheduleResponse);
/*
 C++ response delegate for leaderboard schedule deletion
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardScheduleResponseDelegate, FLootLockerServerResponse);

//==================================================
// Interface Definition
//==================================================
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerLeaderboardRequest : public UObject
{
    GENERATED_BODY()
public:
    static void GetLeaderboard(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerGetLeaderboardResponseBP(), const FLootLockerServerGetLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerGetLeaderboardResponseDelegate());
    static void CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerCreateLeaderboardResponseBP(), const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerCreateLeaderboardResponseDelegate());
    static void UpdateLeaderboard(const FString& LeaderboardKey, const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequest, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerUpdateLeaderboardResponseBP(), const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerUpdateLeaderboardResponseDelegate());
    static void DeleteLeaderboard(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerDeleteLeaderboardResponseBP(), const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerDeleteLeaderboardResponseDelegate());
    static void SubmitScore(const FString& LeaderboardKey, const FLootLockerServerLeaderboardSubmitScoreRequest& SubmitScoreRequest, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequestBP = FLootLockerServerLeaderboardSubmitScoreResponseBP(), const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest = FLootLockerServerLeaderboardSubmitScoreResponseDelegate());
    static void GetAllMemberRanks(const FString& MemberID, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequestBP = FLootLockerServerGetAllMemberRanksResponseBP(), const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest = FLootLockerServerGetAllMemberRanksResponseDelegate());
    static void GetPaginatedAllMemberRanks(const FString& MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequestBP = FLootLockerServerGetAllMemberRanksResponseBP(), const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest = FLootLockerServerGetAllMemberRanksResponseDelegate());
    static void GetScoresFromLeaderboard(FString LeaderboardKey, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerGetScoresFromLeaderboardResponseBP(), const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerGetScoresFromLeaderboardResponseDelegate());
    static void GetPaginatedScoresFromLeaderboard(FString LeaderboardKey, int Count, int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerGetScoresFromLeaderboardResponseBP(), const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerGetScoresFromLeaderboardResponseDelegate());

    static void GetLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequestBP = FLootLockerServerGetLeaderboardScheduleResponseBP(), const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest = FLootLockerServerGetLeaderboardScheduleResponseDelegate());
    static void CreateLeaderboardSchedule(const FString& LeaderboardKey, const FString& CronExpression, const FLootLockerServerGetLeaderboardScheduleResponseBP& OnCompletedRequestBP = FLootLockerServerGetLeaderboardScheduleResponseBP(), const FLootLockerServerGetLeaderboardScheduleResponseDelegate& OnCompletedRequest = FLootLockerServerGetLeaderboardScheduleResponseDelegate());
    static void DeleteLeaderboardSchedule(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardScheduleResponseBP& OnCompletedRequestBP = FLootLockerServerDeleteLeaderboardScheduleResponseBP(), const FLootLockerServerDeleteLeaderboardScheduleResponseDelegate& OnCompletedRequest = FLootLockerServerDeleteLeaderboardScheduleResponseDelegate());

public:
    ULootLockerServerLeaderboardRequest();
};
