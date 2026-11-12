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
     * Player file responses carry a short-lived signed URL in "url". That URL is a bearer
     * credential: anyone holding it can download the file until it expires, so it must never reach
     * logs or the log UI. An object is treated as carrying a signed download URL when it has
     * "url_expires_at" or the player file marker "requires_download_link". The marker is needed
     * because the file revision payload carries a signed "url" without an expiry field. Scoping on
     * those markers leaves ordinary URLs in other responses intact.
     */
    FString RedactSignedDownloadUrlsForLogging(const FString& JsonBody);

    /**
     * Whether a request to this endpoint can return a signed download URL.
     *
     * Only the player-file endpoints mint signed URLs, so every other response can skip the
     * redaction entirely. This is a single substring check on the request URL, which keeps the
     * cost off the path every request walks.
     */
    static bool CanReturnSignedDownloadUrl(const FString& RequestUrl)
    {
        return RequestUrl.Contains(TEXT("files"));
    }
}