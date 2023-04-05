// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerLeaderboardRequest.generated.h"

UENUM(BlueprintType)
enum class ELootLockerServerLeaderboardType : uint8
{
    player = 0         UMETA(DisplayName = "Player"),
    generic = 1        UMETA(DisplayName = "Generic"),
};

UENUM(BlueprintType)
enum class ELootLockerServerLeaderboardDirection : uint8
{
    ascending = 0         UMETA(DisplayName = "Ascending"),
    descending = 1        UMETA(DisplayName = "Descending"),
};

/*
 * Data types
 */

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardPlayer
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int ID = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Public_Uid;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardMember
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_ID;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Rank = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardPlayer Player;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboard
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Leaderboard_ID = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Leaderboard_Key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerLeaderboardMember Rank;
};

/*
 * Request definitions
 */

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardSubmitScoreRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_ID;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGenericLeaderboardRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardDirection Direction_Method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Enable_Game_Api_Writes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Overwrite_Score_On_Submit;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardRequest : public FLootLockerServerGenericLeaderboardRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardType Type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Has_Metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdateLeaderboardRequest : public FLootLockerServerGenericLeaderboardRequest
{
	GENERATED_BODY()
};

/*
 * Response definitions
 */

USTRUCT(BlueprintType)
struct FLootLockerServerGenericLeaderboardResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int ID;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Game_ID;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardType Type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerLeaderboardDirection Direction_Method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Enable_Game_Api_Writes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Overwrite_Score_On_Submit;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Has_Metadata;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardResponse : public FLootLockerServerGenericLeaderboardResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdateLeaderboardResponse : public FLootLockerServerGenericLeaderboardResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardSubmitScoreResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Member_ID;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Rank;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetAllMemberRanksResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerIndexBasedPagination Pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboard> Leaderboards;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetScoresFromLeaderboardResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerIndexBasedPagination Pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerLeaderboardMember> Items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreateLeaderboardResponseBP, FLootLockerServerCreateLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUpdateLeaderboardResponseBP, FLootLockerServerUpdateLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardResponseBP, FLootLockerServerResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerLeaderboardSubmitScoreResponseBP, FLootLockerServerLeaderboardSubmitScoreResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetAllMemberRanksResponseBP, FLootLockerServerGetAllMemberRanksResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetScoresFromLeaderboardResponseBP, FLootLockerServerGetScoresFromLeaderboardResponse, Response);

DECLARE_DELEGATE_OneParam(FLootLockerServerCreateLeaderboardResponseDelegate, FLootLockerServerCreateLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerUpdateLeaderboardResponseDelegate, FLootLockerServerUpdateLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardResponseDelegate, FLootLockerServerResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerLeaderboardSubmitScoreResponseDelegate, FLootLockerServerLeaderboardSubmitScoreResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerGetAllMemberRanksResponseDelegate, FLootLockerServerGetAllMemberRanksResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerGetScoresFromLeaderboardResponseDelegate, FLootLockerServerGetScoresFromLeaderboardResponse);

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
    static ULootLockerServerHttpClient* HttpClient;

};