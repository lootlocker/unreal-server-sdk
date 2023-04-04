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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Success;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ServerCallStatusCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FullTextFromServer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Error;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerResponseCallbackBP, FLootLockerServerResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerServerResponseCallback, FLootLockerServerResponse);
