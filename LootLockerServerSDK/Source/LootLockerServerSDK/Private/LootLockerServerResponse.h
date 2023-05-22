// Copyright (c) 2021 LootLocker

#pragma once
#include "LootLockerServerResponse.generated.h"

/*
 An empty type to use as empty request bodies
 */
USTRUCT(BlueprintType)
struct FLootLockerServerEmptyRequest
{
    GENERATED_BODY()
};

/*
 The base response for all LootLocker Server responses
 */
USTRUCT(BlueprintType)
struct FLootLockerServerResponse
{
	GENERATED_BODY()
    /*
     True if the request succeeded
     */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	bool Success = false;
	/*
	 The status code of the response
	 https://ref.lootlocker.com/server-api/#response-and-error-codes
	 */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	int ServerCallStatusCode = 0;
    /*
     The full response body as a string
     */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString FullTextFromServer = "";
	/*
	 A parsed error message, will be empty if the request succeeded
	 https://ref.lootlocker.com/server-api/#response-and-error-codes
	 */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Error = "";
    /*
     An authenticated session token
     */
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Token = "";
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for a generic LootLocker Response
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerResponseCallbackBP, FLootLockerServerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for a generic LootLocker Response
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerResponseCallback, FLootLockerServerResponse);

//==================================================
// Definition of pagination data structures https://ref.lootlocker.com/server-api/#pagination
//==================================================

/*
 Pagination data for key based pagination
 This is used for methods that have a "count" and an "after" parameter. The "after" parameter is the "next_cursor" value from the previous response, which means "where in the larger list should I start?".
 */
USTRUCT(BlueprintType)
struct FLootLockerServerKeyBasedPagination
{
    GENERATED_BODY()
    /*
     The total number of items in the list this pagination refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int Total = 0;
    /*
     The key to use for the "after" parameter in the next request
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString Next_Cursor = "";
    /*
     The key used for the "after" parameter in the previous request
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString Previous_Cursor = "";
};

/*
 Pagination data for index based pagination
 This is used for methods that have a "count" and an "after" parameter. The "after" parameter is the "next_cursor" value from the previous response, which means "where in the larger list should I start?".
 */
USTRUCT(BlueprintType)
struct FLootLockerServerIndexBasedPagination
{
    GENERATED_BODY()
    /*
     The total number of items in the list this pagination refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int32 Total = 0;
    /*
     The index to use for the "after" parameter in the next request
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int32 Next_Cursor = 0;
    /*
     The index used for the "after" parameter in the previous request
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int32 Previous_Cursor = 0;
};
