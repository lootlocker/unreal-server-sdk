// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerStorageRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerSDK/Private/LootLockerServerEndpoints.h"
#include "Utils/LootLockerServerUtilities.h"

ULootLockerServerStorageRequest::ULootLockerServerStorageRequest()
{
}

void ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(TArray<int> PlayerIDs,	const FLootLockerServerGetPersistentStorageForPlayersResponseBP& OnCompleteRequestBP, const FLootLockerServerGetPersistentStorageForPlayersResponseDelegate& OnCompleteResponse)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPersistentStorageForPlayersResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::GetPlayerPersistentStorage, {}, { {"player_ids", LootLockerServerUtilities::IntArrayToCommaSeparatedString(PlayerIDs) } }, OnCompleteRequestBP, OnCompleteResponse);
}

void ULootLockerServerStorageRequest::GetPublicPersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompleteRequestBP, const FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate& OnCompleteResponse)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPublicPersistentStorageForPlayersAndKeysResponse>(FLootLockerServerPlayerPersistentStorageGetPublicStorageForPlayersAndKeysRequest{ PlayerIDs , Keys}, ULootLockerServerEndpoints::GetMultiplePlayersPublicPersistentStorageValues, {}, {}, OnCompleteRequestBP, OnCompleteResponse);
}

void ULootLockerServerStorageRequest::UpdatePersistentStorageForPlayersAndKeys(TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP& OnCompleteRequestBP, const FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate& OnCompleteResponse)
{
	TArray<FLootLockerServerPlayerPersistentStorageUpdateEntryOrdered> UpdateEntriesWithOrder;
	int i = 0;
	for (const FLootLockerServerPlayerPersistentStorageEntry_NamedSets& EntryToUpdate : StorageEntriesToUpdate)
	{
		i++;
		TArray<FLootLockerServerPlayerPersistentStorageKeyValueSetWithOrder> UpdateSets;
		for (const auto& StorageKeyValueSet : EntryToUpdate.Sets)
		{
			UpdateSets.Add(FLootLockerServerPlayerPersistentStorageKeyValueSetWithOrder{ StorageKeyValueSet.Key, StorageKeyValueSet.Value, StorageKeyValueSet.Is_public, i++ });

		}
		UpdateEntriesWithOrder.Add(FLootLockerServerPlayerPersistentStorageUpdateEntryOrdered{ EntryToUpdate.Player_id, UpdateSets });
	}
	
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse>(FLootLockerServerPlayerPersistentStorageUpdateRequest{ UpdateEntriesWithOrder }, ULootLockerServerEndpoints::UpdatePlayerPersistentStorage, {}, {}, OnCompleteRequestBP, OnCompleteResponse);
}

void ULootLockerServerStorageRequest::DeletePersistentStorageForPlayersAndKeys(TArray<int> PlayerIDs, TArray<FString> Keys, const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP& OnCompleteRequestBP,	const FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate& OnCompleteResponse)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::DeletePlayerPersistentStorage, {}, { {"player_ids", LootLockerServerUtilities::IntArrayToCommaSeparatedString(PlayerIDs)},{"keys", LootLockerServerUtilities::FStringArrayToCommaSeparatedString(Keys)}}, OnCompleteRequestBP, OnCompleteResponse);
}
