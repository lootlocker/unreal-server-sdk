// Copyright (c) 2021 LootLocker

#pragma once
#include "LootLockerServerResponse.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerEmptyRequest {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerServerResponse
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	bool Success;
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	int ServerCallStatusCode;
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString FullTextFromServer;
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Error;
	UPROPERTY(BlueprintReadWrite, Category = "LootLockerServer")
	FString Token;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerResponseCallbackBP, FLootLockerServerResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerServerResponseCallback, FLootLockerServerResponse);

USTRUCT(BlueprintType)
struct FLootLockerServerKeyBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int Total = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString Next_Cursor = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString Previous_Cursor = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerIndexBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int32 Total = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int32 Next_Cursor = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    int32 Previous_Cursor = 0;
};
