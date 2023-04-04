// Copyright (c) 2021 LootLocker

#include "LootLockerServerUtilities.h"

namespace LootLockerServerUtilities
{
    FString AppendParametersToUrl(FString Url, const TMultiMap<FString, FString>& QueryParams)
    {
        if (QueryParams.Num() != 0)
        {
            FString Delimiter = "?";
            for (const TPair<FString, FString>& Pair : QueryParams)
            {
                Url = Url + Delimiter + Pair.Key + "=" + Pair.Value;
                Delimiter = "&";
            }
        }
        return Url;
    }

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString)
    {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);
        return JsonObject;
    }
}
