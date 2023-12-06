#include <future>

#include "LootLockerServerForBlueprints.h"
#include "Misc/AutomationTest.h"
#include "ServerAPI/LootLockerServerStorageRequest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_PersistentStorage, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_PersistentStorage)

void FTestLootLockerServer_PersistentStorage::Define()
{
	Describe("Server_PersistentStorage", [this]()
	{
		LatentIt("When Server PersistentStorage", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			ULootLockerServerAuthRequest::StartSession();

			const int PlayerId = 3245521;

			FLootLockerServerPlayerPersistentStorageKeyValueSet TestItem;
			TestItem.Key = "test_key";
			TestItem.Value = "test_value";

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponse, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseDelegate>();

				TArray<FLootLockerServerPlayerPersistentStorageKeyValueSet> Items;
				Items.Add(TestItem);

				FLootLockerServerPlayerPersistentStorageEntry_NamedSets NamedSet;
				NamedSet.Player_id = PlayerId;
				NamedSet.Sets.Add(TestItem);

				TArray<FLootLockerServerPlayerPersistentStorageEntry_NamedSets> StorageEntriesToUpdate;
				StorageEntriesToUpdate.Add(NamedSet);

				ULootLockerServerStorageRequest::UpdatePersistentStorageForPlayersAndKeys(StorageEntriesToUpdate, FLootLockerServerUpdatePersistentStorageForPlayersAndKeysResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Server_AddItemsToPersistentStorage success", Response.Success);

				if (Response.Success)
				{
					TestEqual("Server_AddItemsToPersistentStorage items returned", Response.Items.Num(), 1u);
					TestEqual("Server_AddItemsToPersistentStorage player items returned", Response.Items[0].Player_id, PlayerId);
					TestEqual("Server_AddItemsToPersistentStorage player items count is 1", Response.Items[0].Items.Num(), 1);
					TestTrue("Server_AddItemsToPersistentStorage player items ok", Response.Items[0].Items.ContainsByPredicate([key = TestItem.Key](FLootLockerServerPlayerPersistentStorageKeyValueSet& target)
					{
						return key == target.Key;
					}));
				}
				delete(Promise);
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerGetPersistentStorageForPlayersResponse, FLootLockerServerGetPersistentStorageForPlayersResponseDelegate>();

				ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(TArray<int>{ PlayerId }, FLootLockerServerGetPersistentStorageForPlayersResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Server_GetPlayerPersistentStorage success", Response.Success);

				if (Response.Success)
				{
					TestEqual("Server_GetPlayerPersistentStorage items returned", Response.Items.Num(), 1u);
					TestEqual("Server_GetPlayerPersistentStorage player items returned", Response.Items[0].Player_id, PlayerId);
				}
				delete(Promise);
			}
		
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate>();

				TArray<int> PlayerIDs = { PlayerId };				
				TArray<FString> Keys = { TestItem.Key };

				ULootLockerServerStorageRequest::DeletePersistentStorageForPlayersAndKeys(PlayerIDs, Keys, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("DeleteItemFromPersistentStorage success", Response.Success);
				delete(Promise);
			}

			TestDone.Execute();
		});
	});
}
#endif

