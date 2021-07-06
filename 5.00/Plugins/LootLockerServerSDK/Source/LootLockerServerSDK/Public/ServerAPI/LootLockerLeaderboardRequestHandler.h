// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerLeaderboardRequestHandler.generated.h"


UENUM(BlueprintType)
enum class ELootLockerLeaderboardType : uint8
{
    player = 0         UMETA(DisplayName = "Player"),
    generic = 1        UMETA(DisplayName = "Generic"),
};

UENUM(BlueprintType)
enum class ELootLockerLeaderboardDirection : uint8
{
    ascending = 0         UMETA(DisplayName = "Ascending"),
    descending = 1        UMETA(DisplayName = "Descending"),
};


USTRUCT(BlueprintType)
struct FLootLockerCreateLeaderboardResponse : public FLootLockerServerResponse
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
struct FLootLockerUpdateLeaderboardResponse : public FLootLockerServerResponse
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
struct FLootLockerDeleteLeaderboardResponse : public FLootLockerServerResponse
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
struct FLootLockerSubmitScoreResponse : public FLootLockerServerResponse
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
struct FLootLockerSubmitScoreRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
};

USTRUCT(BlueprintType)
struct FLootLockerCreateLeaderboardRequest
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
struct FLootLockerDeleteLeaderboardRequest
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
struct FLootLockerUpdateLeaderboardRequest
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCreateLeaderboardResponseBP, FLootLockerCreateLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerUpdateLeaderboardResponseBP, FLootLockerUpdateLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDeleteLeaderboardResponseBP, FLootLockerDeleteLeaderboardResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSubmitScoreResponseBP, FLootLockerSubmitScoreResponse, Response);

DECLARE_DELEGATE_OneParam(FLootLockerCreateLeaderboardResponseDelegate, FLootLockerCreateLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerUpdateLeaderboardResponseDelegate, FLootLockerUpdateLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDeleteLeaderboardResponseDelegate, FLootLockerDeleteLeaderboardResponse);
DECLARE_DELEGATE_OneParam(FLootLockerSubmitScoreResponseDelegate, FLootLockerSubmitScoreResponse);

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerLeaderboardRequestHandler : public UObject
{
	GENERATED_BODY()
public:
    static void CreateLeaderboard(const FLootLockerCreateLeaderboardRequest& CreateLeaderboardRequest, const FLootLockerCreateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerCreateLeaderboardResponseBP(), const FLootLockerCreateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerCreateLeaderboardResponseDelegate());
    static void UpdateLeaderboard(const FLootLockerUpdateLeaderboardRequest& UpdateLeaderboardRequests, int LeaderboardId, const FLootLockerUpdateLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerUpdateLeaderboardResponseBP(), const FLootLockerUpdateLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerUpdateLeaderboardResponseDelegate());
    static void DeleteLeaderboard(int LeaderboardId, const FLootLockerDeleteLeaderboardResponseBP& OnCompletedRequestBP = FLootLockerDeleteLeaderboardResponseBP(), const FLootLockerDeleteLeaderboardResponseDelegate& OnCompletedRequest = FLootLockerDeleteLeaderboardResponseDelegate());
    static void SubmitScore(const FLootLockerSubmitScoreRequest& SubmitScoreRequests, int LeaderboardId, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP = FLootLockerSubmitScoreResponseBP(), const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest = FLootLockerSubmitScoreResponseDelegate());


public:
    ULootLockerLeaderboardRequestHandler();
    static ULootLockerServerHttpClient* HttpClient;

};
