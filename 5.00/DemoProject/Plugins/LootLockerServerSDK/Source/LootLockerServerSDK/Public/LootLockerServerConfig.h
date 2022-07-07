// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "LootLockerServerConfig.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLootLockerServer, Log, All);

USTRUCT(BlueprintType)
struct FLootLockerServerResponse
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool success;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ServerCallHasError;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ServerCallStatusCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FullTextFromServer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ServerError;
};

UENUM(BlueprintType)
enum class ELootLockerServerHTTPMethod : uint8
{
	GET = 0         UMETA(DisplayName = "GET"),
    POST = 1        UMETA(DisplayName = "POST"),
    DELETE = 2      UMETA(DisplayName = "DELETE"),
    PUT = 3         UMETA(DisplayName = "PUT"),
    HEAD = 4        UMETA(DisplayName = "HEAD"),
    CREATE = 5      UMETA(DisplayName = "CREATE"),
    OPTIONS = 6     UMETA(DisplayName = "OPTIONS"),
    PATCH = 7       UMETA(DisplayName = "PATCH"),
    UPLOAD = 8      UMETA(DisplayName = "UPLOAD")
};

USTRUCT(BlueprintType)
struct FLootLockerServerEndPoints
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString endpoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ELootLockerServerHTTPMethod requestMethod;
};

DECLARE_DELEGATE_OneParam(FServerResponseCallback, FLootLockerServerResponse);

UCLASS(Config = LootLockerServerSDK)
class LOOTLOCKERSERVERSDK_API ULootLockerServerConfig : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString LootLockerServerKey;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool OnDevelopmentMode;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString GameVersion;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString LootLockerVersion;

	static FString GetEnum(const TCHAR* Enum, int32 EnumValue);
};
