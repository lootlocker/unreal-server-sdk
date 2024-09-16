// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
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
    OnDouble = 2 UMETA(ToolTip = "Triggered when the parsed entry is of type Double (decimal number). The Double Value field will be populated"),
    OnNumber = 3 UMETA(ToolTip = "Triggered when the parsed entry is a number but not a regular integer or double (could for example be too big to fit in either of those types, or the decimal precision is higher than can be solved with either of the types). The NumberString value field will be populated"),
    OnBool = 4 UMETA(ToolTip = "Triggered when the parsed entry is of type Bool. The Bool Value field will be populated"),
    OnJson = 5 UMETA(ToolTip = "Triggered when the parsed entry is of type Json. The JsonString Value field will be populated with the string representation of the json, convert to a JSON object or straight to a USTRUCT of your design"),
    OnBase64 = 6 UMETA(ToolTip = "Triggered when the parsed entry is of type Base64. The Base64 Value field will be populated"),
    OnError = 7 UMETA(ToolTip = "Triggered when the entry could not be parsed. The ErrorMessage Value field will be populated"),
};


//==================================================
// Data Type Definitions
//==================================================

/*
 Access settings for a metadata entry
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerMetadataAccessSettings
{
    GENERATED_BODY()

    /*
    The level of access that should be allowed from the Game API (the game clients)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataAccessTypes GameAccess = ELootLockerServerMetadataAccessTypes::None;
    /*
    The level of access that should be allowed from the Server API (the game server, if one exists)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    ELootLockerServerMetadataAccessTypes ServerAccess = ELootLockerServerMetadataAccessTypes::ReadAndWrite;
};

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
    ELootLockerServerMetadataTypes Type;
    /*
     List of tags applied to this metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FString> Tags;
    /*
     The access level set for this metadata entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FLootLockerServerMetadataAccessSettings AccessLevel;

    /*
     Get the value as a String. Returns true if value could be parsed in which case Output contains the string value untouched, returns false if parsing failed.
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsString(FString& Output) const;
    /*
     Get the value as a double. Returns true if value could be parsed in which case Output contains the double, returns false if parsing failed which can happen if the value is not numeric, the conversion under or overflows, or the string value precision is larger than can be dealt within a double.
     */
    LOOTLOCKERSERVERSDK_API bool TryGetValueAsDouble(double& Output) const;
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
     */
    void _INTERNAL_SetJsonRepresentation(const FJsonObject& obj);
private:
    FJsonObject EntryAsJson;
};

//==================================================
// Request Definitions
//==================================================

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
    
     */
    int __INTERNAL_GetEntryIndexByKey(const FString Key) const;
    /*
    
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
};