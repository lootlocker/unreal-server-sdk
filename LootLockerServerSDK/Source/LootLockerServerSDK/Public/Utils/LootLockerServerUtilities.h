// Copyright (c) 2021 LootLocker

#pragma once

#include "JsonObjectConverter.h"
#include "LootLockerServerUtilities.generated.h"

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerEnumUtils : public UObject
{
    GENERATED_BODY()
public:
    static FString GetEnum(const TCHAR* Enum, int32 EnumValue);
};

namespace LootLockerServerUtilities
{
    FString AppendParametersToUrl(FString Url, const TMultiMap<FString, FString>& QueryParams);

    FString IntArrayToCommaSeparatedString(TArray<int> IntArray);

    FString FStringArrayToCommaSeparatedString(TArray<FString> FStringArray);

    FString FStringFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject);

    FString FStringFromJsonArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray);

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString);

    bool JsonArrayFromFString(const FString& JsonString, TArray<TSharedPtr<FJsonValue>>& JsonArrayOutput);

    /**
     * Redacts signed download URLs from a JSON body before it is logged.
     *
     * Player file responses carry a short-lived signed URL in "url" next to "url_expires_at".
     * That URL is a bearer credential: anyone holding it can download the file until it expires,
     * so it must never reach logs or the log UI. Only objects that carry "url_expires_at" are
     * redacted, which leaves ordinary (non-signed) URLs in other responses intact.
     */
    FString RedactSignedDownloadUrlsForLogging(const FString& JsonBody);
}