// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerServerConfig.h"

#include "LootLockerServerEndpoints.generated.h"

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
struct FLootLockerServerEndPoint
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    FString endpoint;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLockerServer")
    ELootLockerServerHTTPMethod requestMethod;

	FString GetRequestMethodString()
    {
        return GetDefault<ULootLockerServerConfig>()->GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(requestMethod));
    }
};

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerEndpoints : public UObject
{
    GENERATED_BODY()
public:
    //Auth
    static FLootLockerServerEndPoint StartSessionEndpoint;
    static FLootLockerServerEndPoint MaintainingSessionEndpoint;

private:
    static FString GameBaseUrl;

    static FLootLockerServerEndPoint InitEndpoint(const FString& Endpoint, ELootLockerServerHTTPMethod Method);
};
