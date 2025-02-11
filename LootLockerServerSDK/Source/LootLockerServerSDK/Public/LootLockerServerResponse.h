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

USTRUCT(BlueprintType)
struct FLootLockerServerErrorData
{
    GENERATED_BODY()
    // A descriptive code identifying the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Code;
    // A link to further documentation on the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Doc_url;
    // A unique identifier of the request to use in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Request_id;
    // A unique identifier for tracing the request through LootLocker systems, use this in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Trace_id;
    /// <summary>
    /// If the request was rate limited (status code 429) or the servers were temporarily unavailable (status code 503) you can use this value to determine how many seconds to wait before retrying
    /// </summary>
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int Retry_after_seconds = -1;
    // A free text description of the problem and potential suggestions for fixing it
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Message;
};

/*
 The base response for all LootLocker Server responses
 */
USTRUCT(BlueprintType)
struct FLootLockerServerResponse
{
	GENERATED_BODY()
    
	// True if the request succeeded
    UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
    bool Success = false;
    // HTTP Status code from the request to LootLockers backend 
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int StatusCode = 0;
    // Raw text/http body from the server response
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString FullTextFromServer;
    // If this request was not a success, this structure holds all the information needed to identify the problem
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerErrorData ErrorData;


    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer", meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated, please use 'StatusCode' instead"))
    int ServerCallStatusCode = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer", meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated, replaced by the ErrorData.Message property"))
    FString Error;
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

USTRUCT(BlueprintType)
struct FLootLockerServerExtendedPaginationError
{
    GENERATED_BODY()
    /*
     * Which field in the pagination that this error relates to
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Field;
    /*
     * The error message in question
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Message;
};

USTRUCT(BlueprintType)
struct FLootLockerServerExtendedIndexBasedPagination
{
    GENERATED_BODY()
    /*
     * How many entries in total exists in the paginated list
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Total = 0;
    /*
     * How many entries (counting from the beginning of the paginated list) from the first entry that the current page starts at
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Offset = 0;
    /*
     * Number of entries on each page
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Per_page = 0;
    /*
     * The page index to use for fetching the last page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Last_page = 0;
    /*
     * The page index used for fetching this page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Current_page = 0;
    /*
     * The page index to use for fetching the page of entries immediately succeeding this page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Next_page;
    /*
     * The page index to use for fetching the page of entries immediately preceding this page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Prev_page;
    /*
     * List of pagination errors (if any). These are errors specifically related to the pagination of the entry set.
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerExtendedPaginationError> Errors;
};

/**
 * Static defines of the different predefined error status codes that can occur in responses
 */
struct LootLockerServerStaticRequestErrorStatusCodes
{
    static const int LL_ERROR_UNDOCUMENTED = 0;
    static const int LL_ERROR_INVALID_HTTP = -1;
    static const int LL_ERROR_INVALID_INPUT = -2;
    static const int LL_ERROR_PARSE_ERROR = -3;
};

class LootLockerServerResponseFactory
{
public:
    // Construct a standardized error response
    template<typename T>
    static T Error(FString ErrorMessage, int StatusCode = 0)
    {
        T ErrorResponse;
        ErrorResponse.Success = false;
        ErrorResponse.StatusCode = ErrorResponse.ServerCallStatusCode = StatusCode;
        ErrorResponse.FullTextFromServer = "{ \"message\": \"" + ErrorMessage + "\"}";
        ErrorResponse.ErrorData.Message = ErrorMessage;
        ErrorResponse.Error = ErrorMessage;
        return ErrorResponse;
    }
};
