// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"
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
    FString Public_uid;
    /*
    The name of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
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
    FString Member_id;
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
    FString Metadata;
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
    FString Leaderboard_key;
    /*
     The entry of the player in this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardEntry Rank;
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
     For player leaderboards this will be the Public_UID, for generic leaderboards you can send in any string and that will be the identifier. We recommend using the player's Public_UID or Name.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_id;
    /*
    The Score to submit for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score;
    /*
    The Metadata to submit for this entry in the leaderboard.
    If the leaderboard does not support metadata this property will be ignored.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardBaseRequest
{
    GENERATED_BODY()
    /*
    The unique key of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    /*
    The name of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /*
    The sort order of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardDirection Direction_method;
    /*
    Allow the game api to write to this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Enable_game_api_writes;
    /*
    Always overwrite existing scores for members on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Overwrite_score_on_submit;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardRequest : public FLootLockerServerLeaderboardBaseRequest
{
    GENERATED_BODY()
    /*
    The type of leaderboard to create
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardType Type;
    /*
    Enable metadata on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Has_metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdateLeaderboardRequest : public FLootLockerServerLeaderboardBaseRequest
{
	GENERATED_BODY()
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
    int ID;
    /*
    The ID of the game this leaderboard is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Game_id;
    /*
    The unique key of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    /*
    The name of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    /*
    The type of leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardType Type;
    /*
    The sort order of the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardDirection Direction_method;
    /*
    Is the game api allowed to write to this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Enable_game_api_writes;
    /*
    Do new submits overwrite existing scores for members on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Overwrite_score_on_submit;
    /*
    Is metadata enabled on this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Has_metadata;
    /*
    The creation time of this leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    /*
    The last time this leaderboard was updated
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at;
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
     For player leaderboards this will be the Public_UID, for generic leaderboards this will be the member_id you submitted
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_id;
    /*
    The rank for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Rank;
    /*
    The Score for this entry in the leaderboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score;
    /*
    The Metadata for this entry in the leaderboard.
    If the leaderboard does not support metadata this property will be empty.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata;
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

//==================================================
// Blueprint Delegate Definitions
//==================================================

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

//==================================================
// C++ Delegate Definitions
//==================================================

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

//==================================================
// Interface Definition
//==================================================
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerLeaderboardRequest : public UObject
{
    GENERATED_BODY()
public:
    static void CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerCreateLeaderboardResponseBP(), const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerCreateLeaderboardResponseDelegate());
    static void UpdateLeaderboard(const FString& LeaderboardKey, const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequest, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerUpdateLeaderboardResponseBP(), const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerUpdateLeaderboardResponseDelegate());
    static void DeleteLeaderboard(const FString& LeaderboardKey, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerDeleteLeaderboardResponseBP(), const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerDeleteLeaderboardResponseDelegate());
    static void SubmitScore(const FString& LeaderboardKey, const FLootLockerServerLeaderboardSubmitScoreRequest& SubmitScoreRequest, const FLootLockerServerLeaderboardSubmitScoreResponseBP& OnCompletedRequestBP = FLootLockerServerLeaderboardSubmitScoreResponseBP(), const FLootLockerServerLeaderboardSubmitScoreResponseDelegate& OnCompletedRequest = FLootLockerServerLeaderboardSubmitScoreResponseDelegate());
    static void GetAllMemberRanks(const FString& MemberID, const int Count, const int After, const FLootLockerServerGetAllMemberRanksResponseBP& OnCompletedRequestBP = FLootLockerServerGetAllMemberRanksResponseBP(), const FLootLockerServerGetAllMemberRanksResponseDelegate& OnCompletedRequest = FLootLockerServerGetAllMemberRanksResponseDelegate());
    static void GetScoresFromLeaderboard(FString LeaderboardKey, int Count, int After, const FLootLockerServerGetScoresFromLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerGetScoresFromLeaderboardResponseBP(), const FLootLockerServerGetScoresFromLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerGetScoresFromLeaderboardResponseDelegate());

public:
    ULootLockerServerLeaderboardRequest();
};
