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

    FString IntArrayToCommaSeparatedString(TArray<int> IntArray)
    {
        FString BuildString;
        for (int i = 0; i < IntArray.Num(); ++i)
        {
            if (i > 0) {
                BuildString.Append(TEXT(","));
            }
            BuildString.Append(FString::FromInt(IntArray[i]));
        }
        return BuildString;
    }

    FString FStringArrayToCommaSeparatedString(TArray<FString> FStringArray)
    {
        FString BuildString;
        for (int i = 0; i < FStringArray.Num(); ++i)
        {
            if (i > 0) {
                BuildString.Append(TEXT(","));
            }
            BuildString.Append(FStringArray[i]);
        }
        return BuildString;
    }

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString)
    {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);
        return JsonObject;
    }
}
