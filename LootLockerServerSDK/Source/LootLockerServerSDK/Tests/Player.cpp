// Copyright (c) 2021 LootLocker

#include <future>

#include "Misc/AutomationTest.h"
#include "Runtime/Launch/Resources/Version.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_Player, "LootLockerServer.Player", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_Player)

void FTestLootLockerServer_Player::Define()
{
	Describe("Server_Player", [this]()
	{
		LatentIt("CreatePlayer_ReturnsIdentifiers", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			const FString PlatformIdentifier = FGuid::NewGuid().ToString();

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

			ULootLockerServerPlayerRequest::CreatePlayer(
				ELootLockerServerCreatePlayerPlatforms::Guest, PlatformIdentifier, Delegate);

			const auto Response = test_util::WaitAndGet(Promise);
			TestTrue("CreatePlayer succeeded", Response.Success);
			if (Response.Success)
			{
				TestTrue("CreatePlayer returned a player id", Response.Player_id > 0);
				TestFalse("CreatePlayer returned a player ulid", Response.Player_ulid.IsEmpty());
			}

			TestDone.Execute();
		});

		LatentIt("CreatePlayer_IsIdempotentForSameIdentifier", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			const FString PlatformIdentifier = FGuid::NewGuid().ToString();

			int32 FirstPlayerId = 0;
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

				ULootLockerServerPlayerRequest::CreatePlayer(
					ELootLockerServerCreatePlayerPlatforms::Guest, PlatformIdentifier, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("First CreatePlayer succeeded", Response.Success);
				if (!Response.Success)
				{
					TestDone.Execute();
					return;
				}
				FirstPlayerId = Response.Player_id;
			}

			// The endpoint upserts: re-using a platform identifier must resolve to the same player.
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

				ULootLockerServerPlayerRequest::CreatePlayer(
					ELootLockerServerCreatePlayerPlatforms::Guest, PlatformIdentifier, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("Second CreatePlayer succeeded", Response.Success);
				if (Response.Success)
				{
					TestEqual("Same platform identifier resolves to the same player", Response.Player_id, FirstPlayerId);
				}
			}

			TestDone.Execute();
		});

		LatentIt("LookupPlayerNames_ReturnsRequestedPlayers", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			int32 PlayerId = 0;
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
				PlayerId = Response.Player_id;
				PlayerUlid = Response.Player_ulid;
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerPlayerNameLookupResponse, FLootLockerServerPlayerNameLookupResponseDelegate>();

			TArray<FLootLockerServerPlayerNameLookupPair> Lookups;
			FLootLockerServerPlayerNameLookupPair Pair;
			Pair.IdType = ELootLockerServerPlayerNameLookupIdType::Player_id;
			Pair.Id = FString::FromInt(PlayerId);
			Lookups.Add(Pair);

			ULootLockerServerPlayerRequest::LookupPlayerNames(Lookups, Delegate);

			const auto Response = test_util::WaitAndGet(Promise);
			TestTrue("LookupPlayerNames succeeded", Response.Success);
			if (Response.Success)
			{
				TestTrue("At least one player name returned", Response.Players.Num() > 0);
			}

			TestDone.Execute();
		});
	});
}
#endif
