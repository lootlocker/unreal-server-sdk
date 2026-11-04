// Copyright (c) 2021 LootLocker

#include "Utils/LootLockerServerUtilities.h"

#include "GenericPlatform/GenericPlatformHttp.h"
#include "Runtime/Launch/Resources/Version.h"

namespace LootLockerServerUtilities
{
    FString AppendParametersToUrl(FString Url, const TMultiMap<FString, FString>& QueryParams)
    {
        if (QueryParams.Num() != 0)
        {
            FString Delimiter = "?";
            for (const TPair<FString, FString>& Pair : QueryParams)
            {
                Url = Url + Delimiter + FGenericPlatformHttp::UrlEncode(Pair.Key) + "=" + FGenericPlatformHttp::UrlEncode(Pair.Value);
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

    static void RedactSignedDownloadUrlsInValue(const TSharedPtr<FJsonValue>& Value, bool& bRedacted);

    static void RedactSignedDownloadUrlsInObject(const TSharedPtr<FJsonObject>& Object, bool& bRedacted)
    {
        if (!Object.IsValid())
        {
            return;
        }

        // Recurse into children first, over a copy so redacting this object cannot invalidate iteration.
        TArray<TSharedPtr<FJsonValue>> ChildValues;
        ChildValues.Reserve(Object->Values.Num());
        for (const auto& Field : Object->Values)
        {
            ChildValues.Add(Field.Value);
        }
        for (const TSharedPtr<FJsonValue>& Child : ChildValues)
        {
            RedactSignedDownloadUrlsInValue(Child, bRedacted);
        }

        // Only redact "url" where "url_expires_at" or the player file marker
        // "requires_download_link" is present. This leaves ordinary URLs in other responses intact.
        FString Url;
        const bool bCarriesSignedDownloadUrl = Object->HasField(TEXT("url_expires_at")) || Object->HasField(TEXT("requires_download_link"));
        if (bCarriesSignedDownloadUrl && Object->TryGetStringField(TEXT("url"), Url) && !Url.IsEmpty())
        {
            Object->SetStringField(TEXT("url"), TEXT("[REDACTED]"));
            bRedacted = true;
        }
    }

    static void RedactSignedDownloadUrlsInValue(const TSharedPtr<FJsonValue>& Value, bool& bRedacted)
    {
        if (!Value.IsValid())
        {
            return;
        }

        const TSharedPtr<FJsonObject>* ObjectValue = nullptr;
        if (Value->TryGetObject(ObjectValue) && ObjectValue != nullptr && ObjectValue->IsValid())
        {
            RedactSignedDownloadUrlsInObject(*ObjectValue, bRedacted);
            return;
        }

        const TArray<TSharedPtr<FJsonValue>>* ArrayValue = nullptr;
        if (Value->TryGetArray(ArrayValue) && ArrayValue != nullptr)
        {
            for (const TSharedPtr<FJsonValue>& Element : *ArrayValue)
            {
                RedactSignedDownloadUrlsInValue(Element, bRedacted);
            }
        }
    }

    FString RedactSignedDownloadUrlsForLogging(const FString& JsonBody)
    {
        if (JsonBody.IsEmpty())
        {
            return JsonBody;
        }

        const TSharedPtr<FJsonObject> JsonObject = JsonObjectFromFString(JsonBody);
        if (!JsonObject.IsValid())
        {
            return JsonBody;
        }

        bool bRedacted = false;
        RedactSignedDownloadUrlsInObject(JsonObject, bRedacted);
        return bRedacted ? FStringFromJsonObject(JsonObject) : JsonBody;
    }
}

FString ULootLockerServerEnumUtils::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuter(), Enum, true);
    if (!EnumPtr)
        return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

    return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();
}
