#include <future>

#include "Misc/AutomationTest.h"
#include "Runtime/Launch/Resources/Version.h"
#include "ServerAPI/LootLockerServerStorageRequest.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(FTestLootLockerServer_PersistentStorage, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerServerTestGame Game;
END_DEFINE_SPEC(FTestLootLockerServer_PersistentStorage)

void FTestLootLockerServer_PersistentStorage::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		if (!test_util::SetupTestGame(Game, TEXT("PersistentStorage")))
		{
			AddError(TEXT("Game setup failed"));
		}
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		Done.Execute();
	});

	Describe("Server_PersistentStorage", [this]()
	{
		LatentIt("When Server PersistentStorage", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { TestDone.Execute(); return; }

			int PlayerId = 0;
			FString PlayerUlid;
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

				ULootLockerServerPlayerRequest::CreatePlayer(ELootLockerServerCreatePlayerPlatforms::Guest, FGuid::NewGuid().ToString(), Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("CreatePlayer Ok", Response.Success);
				if (!Response.Success)
				{
					TestDone.Execute();
					return;
				}
				PlayerId = Response.Player_id;
				PlayerUlid = Response.Player_ulid;
			}

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

				ULootLockerServerStorageRequest::UpdatePersistentStorageForPlayersAndKeys(StorageEntriesToUpdate, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
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
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerGetPersistentStorageForPlayersResponse, FLootLockerServerGetPersistentStorageForPlayersResponseDelegate>();

				ULootLockerServerStorageRequest::GetPersistentStorageForPlayers(TArray<int>{ PlayerId }, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("Server_GetPlayerPersistentStorage success", Response.Success);

				if (Response.Success)
				{
					TestEqual("Server_GetPlayerPersistentStorage items returned", Response.Items.Num(), 1u);
					TestEqual("Server_GetPlayerPersistentStorage player items returned", Response.Items[0].Player_id, PlayerId);
				}
			}
		
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponse, FLootLockerServerDeletePersistentStorageForPlayersAndKeysResponseDelegate>();

				TArray<int> PlayerIDs = { PlayerId };				
				TArray<FString> Keys = { TestItem.Key };

				ULootLockerServerStorageRequest::DeletePersistentStorageForPlayersAndKeys(PlayerIDs, Keys, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("DeleteItemFromPersistentStorage success", Response.Success);
			}

			TestDone.Execute();
		});
	});
}
#endif

