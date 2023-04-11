// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerHttpClient.generated.h"

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerHttpClient : public UObject
{
	GENERATED_BODY()
    
public:
    ULootLockerServerHttpClient();
    void SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FLootLockerServerResponseCallback&
                 onCompleteRequest, TMap<FString, FString> customHeaders = TMap<FString, FString>()) const;
    void UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>
                    AdditionalFields, const FLootLockerServerResponseCallback& onCompleteRequest, TMap<FString, FString> customHeaders =
	                    TMap<FString, FString>()) const;
public:
	static bool ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful, FString RequestMethod, FString Endpoint, FString Data);
};



