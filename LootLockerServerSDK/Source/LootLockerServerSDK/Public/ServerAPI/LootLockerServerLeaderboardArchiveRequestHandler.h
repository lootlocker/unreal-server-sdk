// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"

#include "LootLockerServerLeaderboardArchiveRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardArchivePlayer
{
	GENERATED_BODY()
	// The name of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString name;
	// The Public UID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString public_uid;
	// The ID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int32 id = 0;
	// The ULID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString player_ulid;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardArchiveDetails 
{
	GENERATED_BODY()
	// The Player on the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FLootLockerServerLeaderboardArchivePlayer player;
	// Metadata if any was supplied.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString metadata;
	// The Player's member ID on the Archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString member_id;
	// The Player's rank on the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int32 rank = 0;
	// The Player's Score on the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int score = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardArchive
{
	GENERATED_BODY()
	// The date when the archived Leaderboard was modified.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString last_modified;
	// The type of content (application/json).
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString content_type;
	// The Key which is used to identify a json body of an old Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString key;
	// Length of the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int32 content_length = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardArchiveDetailsResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	// A list of players and details from the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerLeaderboardArchiveDetails> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerLeaderboardArchiveResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	// A List of past Leaderboards.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerLeaderboardArchive> archives;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerLeaderboardArchiveResponseBP, FLootLockerServerLeaderboardArchiveResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerLeaderboardArchiveDetailReponseBP, FLootLockerServerLeaderboardArchiveDetailsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerServerLeaderboardArchiveResponseDelegate, FLootLockerServerLeaderboardArchiveResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerLeaderboardArchiveDetailResponseDelegate, FLootLockerServerLeaderboardArchiveDetailsResponse);


UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerLeaderboardArchiveRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	static void ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerServerLeaderboardArchiveResponseBP& OnCompletedRequestBP = FLootLockerServerLeaderboardArchiveResponseBP(), const FLootLockerServerLeaderboardArchiveResponseDelegate& OnCompletedRequest = FLootLockerServerLeaderboardArchiveResponseDelegate());
	static void GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerServerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP = FLootLockerServerLeaderboardArchiveDetailReponseBP(), const FLootLockerServerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest = FLootLockerServerLeaderboardArchiveDetailResponseDelegate());
public:
	ULootLockerServerLeaderboardArchiveRequestHandler();
};