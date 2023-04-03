// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "JsonObjectConverter.h"
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


USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString direction_method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool enable_game_api_writes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool overwrite_score_on_submit;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdateLeaderboardResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString direction_method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool enable_game_api_writes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool overwrite_score_on_submit;
};

USTRUCT(BlueprintType)
struct FLootLockerServerDeleteLeaderboardResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString direction_method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool enable_game_api_writes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool overwrite_score_on_submit;
};


USTRUCT(BlueprintType)
struct FLootLockerServerSubmitScoreResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rank;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
};

USTRUCT(BlueprintType)
struct FLootLockerServerSubmitScoreRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreateLeaderboardRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString direction_method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool enable_game_api_writes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool overwrite_score_on_submit;
};

USTRUCT(BlueprintType)
struct FLootLockerServerDeleteLeaderboardRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int leaderboardId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int count;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int after;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdateLeaderboardRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString direction_method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool enable_game_api_writes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool overwrite_score_on_submit;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreateLeaderboardResponseBP, FLootLockerServerCreateLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUpdateLeaderboardResponseBP, FLootLockerServerUpdateLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardResponseBP, FLootLockerServerDeleteLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSubmitScoreResponseBP, FLootLockerServerSubmitScoreResponse, Response);

DECLARE_DELEGATE_OneParam(FLootLockerServerCreateLeaderboardResponseDelegate, FLootLockerServerCreateLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerUpdateLeaderboardResponseDelegate, FLootLockerServerUpdateLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerDeleteLeaderboardResponseDelegate, FLootLockerServerDeleteLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerSubmitScoreResponseDelegate, FLootLockerServerSubmitScoreResponse);

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerLeaderboardRequest : public UObject
{
	GENERATED_BODY()
public:
    static void CreateLeaderboard(const FLootLockerServerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerServerCreateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerCreateLeaderboardResponseBP(), const FLootLockerServerCreateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerCreateLeaderboardResponseDelegate());
    static void UpdateLeaderboard(const FLootLockerServerUpdateLeaderboardRequest& UpdateLeaderboardRequests, int LeaderboardId, const FLootLockerServerUpdateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerUpdateLeaderboardResponseBP(), const FLootLockerServerUpdateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerUpdateLeaderboardResponseDelegate());
    static void DeleteLeaderboard(int LeaderboardId, const FLootLockerServerDeleteLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerServerDeleteLeaderboardResponseBP(), const FLootLockerServerDeleteLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerServerDeleteLeaderboardResponseDelegate());
    static void SubmitScore(const FLootLockerServerSubmitScoreRequest& SubmitScoreRequests, int LeaderboardId, const FLootLockerServerSubmitScoreResponseBP& OnCompletedRequestBP = FLootLockerServerSubmitScoreResponseBP(), const FLootLockerServerSubmitScoreResponseDelegate& OnCompletedRequest = FLootLockerServerSubmitScoreResponseDelegate());


public:
    ULootLockerServerLeaderboardRequest();
    static ULootLockerServerHttpClient* HttpClient;

};
