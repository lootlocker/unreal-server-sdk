// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerProgressionGenericTypes.h"
#include "../LootLockerServerResponse.h"

#include "LootLockerServerGameProgressionRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerGameProgression
{
    GENERATED_BODY()
	/*
	 The id of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id = "";
	/*
	 The key of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key = "";
	/*
	 The name of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
	/*
	 Whether this progression is active
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Active = false;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerGameProgressionListResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 The current pagination data of the requested data
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FLootLockerServerKeyBasedPagination Pagination;
	/*
	 List of game progressions according to the current pagination settings
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerGameProgression> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerSingleGameProgressionResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
	/*
	 The id of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id = "";
	/*
	 The key of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key = "";
	/*
	 The name of the progression
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Name = "";
	/*
	 Whether this progression is active
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    bool Active = false;
};

USTRUCT(BlueprintType)
struct FLootLockerServerProgressionTiersResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
	/*
	 The current pagination data of the requested data
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerIndexBasedPagination Pagination;
	/*
	 A list of the tiers that are in this progression according to the current pagination settings
	*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerProgressionTier> Items;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for listing game progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGameProgressionListResponseBP, FLootLockerServerGameProgressionListResponse, Response);
/*
 Blueprint response delegate for receiving a single game progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSingleGameProgressionResponseBP, FLootLockerServerSingleGameProgressionResponse, Response);
/*
 Blueprint response delegate for receiving the tiers of a single game progression
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerProgressionTiersResponseBP, FLootLockerServerProgressionTiersResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/*
 C++ response delegate for listing game progression
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGameProgressionListResponseDelegate, FLootLockerServerGameProgressionListResponse);
/*
 C++ response delegate for receiving a single game progression
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSingleGameProgressionResponseDelegate, FLootLockerServerSingleGameProgressionResponse);
/*
 C++ response delegate for receiving the tiers of a single game progression
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerProgressionTiersResponseDelegate, FLootLockerServerProgressionTiersResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerGameProgressionRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerGameProgressionRequest();	

	static void GetProgressions(const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerGameProgressionListResponseBP(), const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerGameProgressionListResponseDelegate());
	static void GetPaginatedProgressions(int32 Count, const FString& After, const FLootLockerServerGameProgressionListResponseBP& OnCompletedRequestBP = FLootLockerServerGameProgressionListResponseBP(), const FLootLockerServerGameProgressionListResponseDelegate& OnCompletedRequest = FLootLockerServerGameProgressionListResponseDelegate());
	static void GetProgressionByKey(const FString& ProgressionKey, const FLootLockerServerSingleGameProgressionResponseBP& OnCompletedRequestBP = FLootLockerServerSingleGameProgressionResponseBP(), const FLootLockerServerSingleGameProgressionResponseDelegate& OnCompletedRequest = FLootLockerServerSingleGameProgressionResponseDelegate());
	static void GetTiersForProgression(const FString& ProgressionKey, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequestBP = FLootLockerServerProgressionTiersResponseBP(), const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest = FLootLockerServerProgressionTiersResponseDelegate());
	static void GetPaginatedTiersForProgression(const FString& ProgressionKey, int32 Count, int32 After, const FLootLockerServerProgressionTiersResponseBP& OnCompletedRequestBP = FLootLockerServerProgressionTiersResponseBP(), const FLootLockerServerProgressionTiersResponseDelegate& OnCompletedRequest = FLootLockerServerProgressionTiersResponseDelegate());
};
