// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.generated.h"

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerHttpClient : public UObject
{
	GENERATED_BODY()
    
public:
    ULootLockerServerHttpClient();
    void SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FServerResponseCallback& onCompleteRequest, bool useHeader = false);
    void UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString> AdditionalFields, const FServerResponseCallback& onCompleteRequest, bool useHeader = false, bool useAdmin = false);
public:
    bool ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful);
};



