// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerMetadataRequest.generated.h"

//==================================================
// Enum Definitions
//==================================================

/*
 Possible metadata sources
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerMetadataSources : uint8
{
    reward = 0,
    leaderboard = 1,
    catalog_item = 2,
    progression = 3,
    currency = 4,
    player = 5,
    asset = 6,
};

/*
 Possible metadata types
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerMetadataTypes : uint8
{
    String = 0,
    Number = 1,
    Bool = 2,
    Json = 3,
    Base64 = 4,
};

/*
 Possible metadata actions
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerMetadataActions : uint8
{
    Create = 0,
    Update = 1,
    Delete = 2
};

/*
 Possible metadata access types
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerMetadataAccessTypes : uint8
{
    None = 0,
    Read = 1,
    Write = 2,
    ReadAndWrite = 3
};

/*
 Possible metadata parser output types
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerMetadataParserOutputTypes : uint8
{
    OnString = 0 UMETA(ToolTip="Triggered when the parsed entry is of type String. The String Value field will be populated"),
    OnInteger = 1 UMETA(ToolTip = "Triggered when the parsed entry is of type Integer (non decimal number). The Integer Value field will be populated"),
    OnFloat = 2 UMETA(ToolTip = "Triggered when the parsed entry is of type Float (decimal number). The Float Value field will be populated"),
    OnNumber = 3 UMETA(ToolTip = "Triggered when the parsed entry is a number but not a regular integer or float (could for example be too big to fit in either of those types, or the decimal precision is higher than can be solved with either of the types). The NumberString value field will be populated"),
    OnBool = 4 UMETA(ToolTip = "Triggered when the parsed entry is of type Bool. The Bool Value field will be populated"),
    OnJson = 5 UMETA(ToolTip = "Triggered when the parsed entry is of type Json. The JsonString Value field will be populated with the string representation of the json, convert to a JSON object or straight to a USTRUCT of your design"),
    OnBase64 = 6 UMETA(ToolTip = "Triggered when the parsed entry is of type Base64. The Base64 Value field will be populated"),
    OnError = 7 UMETA(ToolTip = "Triggered when the entry could not be parsed. The ErrorMessage Value field will be populated"),
};


//==================================================
// Data Type Definitions
//==================================================

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerMetadataBase64Value
{
    GENERATED_BODY()
    /*
     The type of content that the base64 string encodes. Could be for example "image/jpeg" if it is a base64 encoded jpeg, or "application/x-redacted" if loading of files has been disabled
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Content_type;
    /*
     The encoded content in the form of a Base64 String. If this is unexpectedly empty, check if Content_type is set to "application/x-redacted". If it is, then the request for metadata was made with the ignoreFiles parameter set to true
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Content;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerMetadataEntry
{
    GENERATED_BODY()
    /*
     The metadata key
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    /*
     The type of value this metadata contains. Use this to parse the value.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataTypes Type = ELootLockerServerMetadataTypes::String;
    /*
     List of tags applied to this metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> Tags;
    /*
     The access level set for this metadata entry. Valid values are game_api.read and game_api.write, though no values are required.
     Note that different sources can allow or disallow a subset of these values.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> Access;
    /*
     Get the value as a String. Returns true if value could be parsed in which case Output contains the string value untouched, returns false if parsing failed.
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsString(FString& Output) const;
    /*
     Get the value as a float. Returns true if value could be parsed in which case Output contains the float, returns false if parsing failed which can happen if the value is not numeric, the conversion under or overflows, or the string value precision is larger than can be dealt within a float.
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsFloat(float& Output) const;
    /*
     Get the value as an integer. TReturns true if value could be parsed in which case Output contains the int, returns false if parsing failed which can happen if
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsInteger(int& Output) const;
    /*
     Get the value as a boolean. Returns true if value could be parsed in which case Output contains the bool, returns false if parsing failed which can happen if the string is not a convertible to a boolean (those are for example "0", "1", "true", "False", "yes", "NO", etc).
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsBool(bool& Output) const;
    /*
     Get the value as an unparsed json value. Returns true if value could be found in which case Output contains the JsonValue, returns false if the value field was not present.
     */
    LOOTLOCKERSERVERSDK_API bool TryGetRawValue(TSharedPtr<FJsonValue>& Output) const;
    /*
     Get the value in a json string format. Returns true if the value was present and could be serialized, returns false otherwise
     */
    LOOTLOCKERSERVERSDK_API bool TryGetSerializedValue(FString& Output) const;
    /*
     Get the value as an unparsed json value. Returns true if value could be found in which case Output contains the JsonValue, returns false if the value field was not present.
     */
    template<typename T>
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsUStruct(T& Output) const;
    /*
     Get the value as a Json Object. Returns true if value could be parsed in which case Output contains the Json Object, returns false if parsing failed which can happen if the value is not a valid json object string.
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsJsonObject(TSharedPtr<FJsonObject>& Output) const;
    /*
     Get the value as a Json Array. Returns true if value could be parsed in which case Output contains the Json Array, returns false if parsing failed which can happen if the value is not a valid json array string
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const;
    /*
     Get the value as a LootLockerServerMetadataBase64Value object. Returns true if value could be parsed in which case Output contains the FLootLockerServerMetadataBase64Value, returns false if parsing failed.
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsBase64(FLootLockerServerMetadataBase64Value& Output) const;

    /*
     Set the value as a String.
     */
    LOOTLOCKERSERVERSDK_API void SetValueAsString(const FString& Value);
    /*
     Set the value as a float.
     */
    LOOTLOCKERSERVERSDK_API void SetValueAsFloat(const float& Value);
    /*
     Set the value as an integer.
     */
    LOOTLOCKERSERVERSDK_API void SetValueAsInteger(const int& Value);
    /*
     Set the value as a bool.
     */
    LOOTLOCKERSERVERSDK_API void SetValueAsBool(const bool& Value);
    /*
     Set the value as a JsonValue.
     */
    LOOTLOCKERSERVERSDK_API void SetRawValue(const TSharedPtr<FJsonValue>& Value);
    /*
     Set the value as the provided UStruct object. Returns true if value could be serialized.
     */
    template<typename T>
    LOOTLOCKERSERVERSDK_API bool SetValueAsUStruct(const T& Value);
    /*
     Set the value as a Json Object.
     */
    LOOTLOCKERSERVERSDK_API void SetValueAsJsonObject(const FJsonObject& Value);
    /*
     Set the value as a Json Array.
     */
    LOOTLOCKERSERVERSDK_API void SetValueAsJsonArray(const TArray<TSharedPtr<FJsonValue>>& Value);
    /*
     Set the value as a Base64 object.
     */
    LOOTLOCKERSERVERSDK_API void SetValueAsBase64(const FLootLockerServerMetadataBase64Value& Value);

    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a String Value
     */
	static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeStringEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FString& Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a Float Value
     */
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeFloatEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const float& Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with an Integer Value
     */
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeIntegerEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const int Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a Bool Value
     */
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeBoolEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const bool Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a JsonValue Value
     */
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeJsonValueEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const ELootLockerServerMetadataTypes Type, const TSharedPtr<FJsonValue> Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a UStruct Value
     */
    template<typename T>
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeUStructEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const T& Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a JsonObject Value
     */
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeJsonObjectEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FJsonObject& Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a JsonArray Value
     */
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeJsonArrayEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const TArray<TSharedPtr<FJsonValue>>& Value);
    /*
     Factory method that makes an FLootLockerServerMetadataEntry with a Base64 Value
     */
    static LOOTLOCKERSERVERSDK_API FLootLockerServerMetadataEntry MakeBase64Entry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FLootLockerServerMetadataBase64Value& Value);

    /*
     For internal use only
     */
    void _INTERNAL_SetJsonRepresentation(const FJsonObject& obj);
private:
    static FLootLockerServerMetadataEntry MakeEntryExceptValue(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const ELootLockerServerMetadataTypes Type);

    FJsonObject EntryAsJson;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerSetMetadataErrorEntry
{
    GENERATED_BODY()
    /*
     The metadata key that the set operation error refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Key;
    /*
     The type of value that the set operation was for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataTypes Type = ELootLockerServerMetadataTypes::String;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerSetMetadataError
{
    GENERATED_BODY()
    /*
     The type of action that this set metadata operation was
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataActions Action = ELootLockerServerMetadataActions::Create;
    /*
     The type of value that the set operation was for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerSetMetadataErrorEntry Entry;
    /*
     The error message describing why this metadata set operation failed
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Error;
};

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerMetadataSourceAndKeys
{
    GENERATED_BODY()
    /*
     The type of source that the source id refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataSources Source = ELootLockerServerMetadataSources::leaderboard;
    /*
     The id of the specific source that the set operation was taken on
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Id;
    /*
     A list of keys existing on the specified source
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> Keys;
};

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerMetadataSourceAndEntries
{
    GENERATED_BODY()
    /*
     The type of source that the source id refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataSources Source = ELootLockerServerMetadataSources::leaderboard;
    /*
     The id of the specific source that the set operation was taken on
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Source_id;
    /*
     List of entries for this source
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerMetadataEntry> Entries;
    /*

     */
    int __INTERNAL_GetEntryIndexByKey(const FString& Key) const;
    /*

     */
    void __INTERNAL_GenerateKeyMap();
private:
    TMap<FString, int> KeyToEntryIndex = TMap<FString, int>();
};

//==================================================
// Request Definitions
//==================================================

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerSetMetadataAction
{
    GENERATED_BODY()
    /*
     The type of action to take for setting this metadata entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataActions Action = ELootLockerServerMetadataActions::Create;
    /*
     The metadata entry to take the designated action for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerMetadataEntry Entry;
};

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerGetMultisourceMetadataRequest
{
    GENERATED_BODY()
    /*
     The source & key combos to get
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerMetadataSourceAndKeys> Sources;
};

//==================================================
// Response Definitions
//==================================================

/*
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerListMetadataResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     List of metadata entries on this page of metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerMetadataEntry> Entries;
    /*
     Pagination data for this set of metadata entries
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerExtendedIndexBasedPagination Pagination;
    /*
    Internal Use Only
     */
    int __INTERNAL_GetEntryIndexByKey(const FString Key) const;
    /*
    Internal Use Only
     */
    void __INTERNAL_GenerateKeyMap();
private:
    TMap<FString, int> KeyToEntryIndex = TMap<FString, int>();
};

/*
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerGetMetadataResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     The requested metadata entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerMetadataEntry Entry;
};

/*
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerSetMetadataResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     A list of any errors that occurred when executing the provided metadata actions
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerSetMetadataError> Errors;
    /*
     The type of source that the source id refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataSources Source = ELootLockerServerMetadataSources::reward;
    /*
     The id of the specific source that the set operation was taken on
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Source_id;
};

/*
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerGetMultisourceMetadataResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /*
     The requested sources with the requested entries for each source
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerMetadataSourceAndEntries> Metadata;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for listing metadata
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListMetadataResponseBP, FLootLockerServerListMetadataResponse, Response);
/*
 Blueprint response delegate for getting a single metadata entry
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetMetadataResponseBP, FLootLockerServerGetMetadataResponse, Response);
/*
 Blueprint response delegate for setting metadata
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSetMetadataResponseBP, FLootLockerServerSetMetadataResponse, Response);
/*
 Blueprint response delegate for getting multi source metadata
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetMultisourceMetadataResponseBP, FLootLockerServerGetMultisourceMetadataResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for listing metadata
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerListMetadataResponseDelegate, FLootLockerServerListMetadataResponse);
/*
 C++ response delegate for getting a single metadata entry
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetMetadataResponseDelegate, FLootLockerServerGetMetadataResponse);
/*
 Blueprint response delegate for setting metadata
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSetMetadataResponseDelegate, FLootLockerServerSetMetadataResponse);
/*
 Blueprint response delegate for getting multi source metadata
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetMultisourceMetadataResponseDelegate, FLootLockerServerGetMultisourceMetadataResponse);

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerMetadataRequest : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerMetadataRequest();

    static void ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FString& Key, const TArray<FString>& Tags, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnCompleteBP = FLootLockerServerListMetadataResponseBP(), const FLootLockerServerListMetadataResponseDelegate& OnComplete = FLootLockerServerListMetadataResponseDelegate());
    static void GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerServerGetMetadataResponseBP& OnCompleteBP = FLootLockerServerGetMetadataResponseBP(), const FLootLockerServerGetMetadataResponseDelegate& OnComplete = FLootLockerServerGetMetadataResponseDelegate());
    static void SetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerServerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerServerSetMetadataResponseBP& OnCompleteBP = FLootLockerServerSetMetadataResponseBP(), const FLootLockerServerSetMetadataResponseDelegate& OnComplete = FLootLockerServerSetMetadataResponseDelegate());
    static void GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerServerGetMultisourceMetadataResponseBP& OnCompleteBP = FLootLockerServerGetMultisourceMetadataResponseBP(), const FLootLockerServerGetMultisourceMetadataResponseDelegate& OnComplete = FLootLockerServerGetMultisourceMetadataResponseDelegate());
};
