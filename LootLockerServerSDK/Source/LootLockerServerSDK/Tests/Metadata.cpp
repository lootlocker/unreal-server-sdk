// Copyright (c) 2021 LootLocker

#include <future>

#include "Misc/AutomationTest.h"
#include "Runtime/Launch/Resources/Version.h"
#include "ServerAPI/LootLockerServerMetadataRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_Metadata, "LootLockerServer.Metadata", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_Metadata)

void FTestLootLockerServer_Metadata::Define()
{
	Describe("Server_Metadata", [this]()
	{
		LatentIt("SetAndGetPlayerMetadata", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			FString PlayerUlid;
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

				ULootLockerServerPlayerRequest::CreatePlayer(
					ELootLockerServerCreatePlayerPlatforms::Guest, FGuid::NewGuid().ToString(), Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("CreatePlayer succeeded", Response.Success);
				if (!Response.Success)
				{
					TestDone.Execute();
					return;
				}
				PlayerUlid = Response.Player_ulid;
			}

			const FString MetadataKey = TEXT("ci_metadata_key");
			const FString MetadataValue = TEXT("ci_metadata_value");

			// Write
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSetMetadataResponse, FLootLockerServerSetMetadataResponseDelegate>();

				FLootLockerServerSetMetadataAction Action;
				Action.Action = ELootLockerServerMetadataActions::Upsert;
				Action.Entry = FLootLockerServerMetadataEntry::MakeStringEntry(
					MetadataKey, TArray<FString>(), TArray<FString>(), MetadataValue);

				TArray<FLootLockerServerSetMetadataAction> Actions;
				Actions.Add(Action);

				ULootLockerServerMetadataRequest::SetMetadata(
					ELootLockerServerMetadataSources::player, PlayerUlid, Actions, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("SetMetadata succeeded", Response.Success);
				if (Response.Success)
				{
					TestEqual("SetMetadata reported no errors", Response.Errors.Num(), 0);
				}
			}

			// Read back
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerGetMetadataResponse, FLootLockerServerGetMetadataResponseDelegate>();

				ULootLockerServerMetadataRequest::GetMetadata(
					ELootLockerServerMetadataSources::player, PlayerUlid, MetadataKey, false, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("GetMetadata succeeded", Response.Success);
				if (Response.Success)
				{
					TestEqual("GetMetadata returned the stored key", Response.Entry.Key, MetadataKey);

					FString ReadValue;
					TestTrue("GetMetadata value parses as a string", Response.Entry.TryGetValueAsString(ReadValue));
					TestEqual("GetMetadata returned the stored value", ReadValue, MetadataValue);
				}
			}

			TestDone.Execute();
		});

		LatentIt("ListMetadata_IncludesWrittenEntry", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			FString PlayerUlid;
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

				ULootLockerServerPlayerRequest::CreatePlayer(
					ELootLockerServerCreatePlayerPlatforms::Guest, FGuid::NewGuid().ToString(), Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("CreatePlayer succeeded", Response.Success);
				if (!Response.Success)
				{
					TestDone.Execute();
					return;
				}
				PlayerUlid = Response.Player_ulid;
			}

			const FString MetadataKey = TEXT("ci_metadata_list_key");

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSetMetadataResponse, FLootLockerServerSetMetadataResponseDelegate>();

				FLootLockerServerSetMetadataAction Action;
				Action.Action = ELootLockerServerMetadataActions::Upsert;
				Action.Entry = FLootLockerServerMetadataEntry::MakeIntegerEntry(
					MetadataKey, TArray<FString>{ TEXT("ci") }, TArray<FString>(), 42);

				TArray<FLootLockerServerSetMetadataAction> Actions;
				Actions.Add(Action);

				ULootLockerServerMetadataRequest::SetMetadata(
					ELootLockerServerMetadataSources::player, PlayerUlid, Actions, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				if (!Response.Success)
				{
					AddError(TEXT("Metadata setup failed"));
					TestDone.Execute();
					return;
				}
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerListMetadataResponse, FLootLockerServerListMetadataResponseDelegate>();

				ULootLockerServerMetadataRequest::ListMetadata(
					ELootLockerServerMetadataSources::player, PlayerUlid, 1, 100, TEXT(""), TArray<FString>(), false, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("ListMetadata succeeded", Response.Success);
				if (Response.Success)
				{
					const bool bFound = Response.Entries.ContainsByPredicate(
						[MetadataKey](const FLootLockerServerMetadataEntry& Entry) { return Entry.Key == MetadataKey; });
					TestTrue("Listed metadata includes the written entry", bFound);
				}
			}

			TestDone.Execute();
		});
	});
}
#endif
