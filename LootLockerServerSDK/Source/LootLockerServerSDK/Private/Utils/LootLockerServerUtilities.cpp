// Copyright (c) 2021 LootLocker

#include "Utils/LootLockerServerUtilities.h"

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
        TSharedPtr<FJsonObject> JsonObject = nullptr;
        const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);
        return JsonObject;
    }

    bool JsonArrayFromFString(const FString& JsonString, TArray<TSharedPtr<FJsonValue>>& JsonArrayOutput)
    {
        TArray<TSharedPtr<FJsonValue>> JsonArray;
        const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        if (!FJsonSerializer::Deserialize(JsonReader, JsonArray))
        {
            return false;
        };
        JsonArrayOutput = JsonArray;
        return true;
    }

    FString FStringFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject)
    {
        FString OutJsonString;
        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutJsonString);

        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter, true);

        return OutJsonString;
    }

    FString FStringFromJsonArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray)
    {
        FString OutJsonString;
        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutJsonString);

        FJsonSerializer::Serialize(JsonArray, JsonWriter, true);

        return OutJsonString;
    }
}

FString ULootLockerServerEnumUtils::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 27
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuter(), Enum, true);
#else
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuterUPackage(), Enum, true);
#endif
    if (!EnumPtr)
        return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

    return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();
}
