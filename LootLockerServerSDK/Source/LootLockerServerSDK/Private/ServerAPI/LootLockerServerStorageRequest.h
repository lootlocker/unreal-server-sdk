// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"

#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"

#include "LootLockerServerStorageRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageKeyValueSet
{
	GENERATED_BODY()
	/*
	 The key for this set, used to access the value
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key = "";
	/*
	 The Value of this set, this is the data you want to store
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Value = "";
	/*
	 Whether this key is public or not. If it is public, other players can read this storage.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool Is_public = false;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageKeyValueSetWithOrder : public FLootLockerServerPlayerPersistentStorageKeyValueSet
{
	GENERATED_BODY()
	/*
	 Used to de-duplicate keys. Can be any sequence of numbers you like. The later keys just need to have a higher number than the early ones. 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Order = 0;
};

/*
 Describes a set of key-value pairs that are stored for a player, the appendix _NamedSets is due to the fact that the server API uses different terms for the same type of objects, in this case it's called a set, but it's the same as a key-value pair.
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageEntry_NamedSets
{
	GENERATED_BODY()
	/*
	 The player ID for which these sets are being stored
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Player_id = 0;
	/*
	 A list of key value pairs that are stored for the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageKeyValueSet> Sets;
};

/*
 Describes a set of key-value pairs that are stored for a player, the appendix _NamedItems is due to the fact that the server API uses different terms for the same type of objects, in this case it's called an item, but it's the same as a key-value pair.
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageEntry_NamedItems
{
	GENERATED_BODY()
	/*
	 The player ID for which these items are being stored
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Player_id = 0;
	/*
	 A list of key value pairs that are stored for the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageKeyValueSet> Items;
};

/*
 Describes a set of key-value pairs that are stored for a player, the appendix _NamedStorage is due to the fact that the server API uses different terms for the same type of objects, in this case it's called a storage, but it's the same as a key-value pair.
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageEntry_NamedStorage
{
	GENERATED_BODY()
	/*
	 The player ID for which this storage applies
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Player_id = 0;
	/*
	 A list of key value pairs that are stored for the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageKeyValueSet> Storage;
};

/*
 Describes a set of key-value pairs that are stored for a player, the appendix _NamedSets is due to the fact that the server API uses different terms for the same type of objects, in this case it's called a set, but it's the same as a key-value pair.
 This overload is due to the fact that the update endpoint requires an "order" flag to keep the list ordered when updating
 */
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageUpdateEntryOrdered
{
	GENERATED_BODY()
	/*
	 The player ID for which this storage applies
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Player_id = 0;
	/*
	 A list of key value pairs that are stored for the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageKeyValueSetWithOrder> Sets;
};

//==================================================
// Request Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageUpdateRequest
{
	GENERATED_BODY()
	/*
	 The payload of the request, a list of persistent storage update items
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageUpdateEntryOrdered> Payload;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerPersistentStorageGetPublicStorageForPlayersAndKeysRequest
{
	GENERATED_BODY()
	/*
	 A list of Player IDs for whom to retrieve the public storage
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<int> Player_ids;
	/*
	 A filter for the keys to retrieve for the requested players. If this is empty, all keys for that player will be retrieved.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FString> Keys;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerGetPersistentStorageForPlayersResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 The persistent storage retrieved for the requested player ids
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedItems> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 The persistent publicly available storage retrieved for the requested player ids and keys
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedStorage> Storages;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 The persistent storage retrieved for the updated player ids
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedItems> Items;
};

/*
 Response for deletion of persistent storage for player(s) and key(s), will be empty on success. If the deletion fails, the response will contain an error message and we recommend doing a subsequent GET request to see what items failed to delete.
 */
USTRUCT(BlueprintType)
struct FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for fetching persistent storage for player(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPersistentStorageForPlayersResponseBP, FLootLockerServerGetPersistentStorageForPlayersResponse, Response);

/*
 Blueprint response delegate for fetching persistent storage for player(s) and key(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse, Response);

/*
 Blueprint response delegate for updating persistent storage for player(s) and key(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse, Response);

/*
 Blueprint response delegate for deleting persistent storage for player(s) and key(s)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for fetching persistent storage for player(s)
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPersistentStorageForPlayersResponseDelegate, FLootLockerServerGetPersistentStorageForPlayersResponse);

/*
 C++ response delegate for fetching persistent storage for player(s) and key(s)
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate, FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse);

/*
 C++ response delegate for updating persistent storage for player(s) and key(s)
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse);

/*
 C++ response delegate for deleting persistent storage for player(s) and key(s)
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerStorageRequest : public UObject
{
	GENERATED_BODY()

	public:	
	ULootLockerServerStorageRequest();
	static void GetPersistentStorageForPlayers(TArray<int> PlayerIDs, const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompleteRequestBP = FLootLockerServerGetPersistentStorageForPlayersResponseBP(), const FLootLockerServerGetPersistentStorageForPlayersResponseDelegate& OnCompleteResponse = FLootLockerServerGetPersistentStorageForPlayersResponseDelegate());
	static void GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompleteRequestBP = FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP(), const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate& OnCompleteResponse = FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate());
	static void UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP& OnCompleteRequestBP = FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP(), const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate& OnCompleteResponse = FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate());
	static void DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP& OnCompleteRequestBP = FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP(), const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate& OnCompleteResponse = FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate());
};
