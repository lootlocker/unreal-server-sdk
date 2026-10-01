// Copyright (c) 2021 LootLocker

#include <future>

#include "Misc/AutomationTest.h"
#include "Runtime/Launch/Resources/Version.h"
#include "ServerAPI/LootLockerServerLeaderboardRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_Leaderboards, "LootLockerServer.Leaderboards", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_Leaderboards)

void FTestLootLockerServer_Leaderboards::Define()
{
	Describe("Server_Leaderboards", [this]()
	{
		LatentIt("CreateAndDeleteLeaderboard", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			const FString Key = TEXT("ci_lb_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreateLeaderboardResponse, FLootLockerServerCreateLeaderboardResponseDelegate>();

				FLootLockerServerCreateLeaderboardRequest Request(Key, TEXT("CI Leaderboard"),
					ELootLockerServerLeaderboardDirection::descending, true, true);

				ULootLockerServerLeaderboardRequest::CreateLeaderboard(Request, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("CreateLeaderboard succeeded", Response.Success);
				if (Response.Success)
				{
					TestEqual("Created leaderboard has the requested key", Response.Key, Key);
					TestTrue("Created leaderboard has an id", Response.ID > 0);
				}
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerResponse, FLootLockerServerDeleteLeaderboardResponseDelegate>();

				ULootLockerServerLeaderboardRequest::DeleteLeaderboard(Key, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("DeleteLeaderboard succeeded", Response.Success);
			}

			TestDone.Execute();
		});

		LatentIt("GetLeaderboard_ReturnsCreatedLeaderboard", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			const FString Key = TEXT("ci_lb_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreateLeaderboardResponse, FLootLockerServerCreateLeaderboardResponseDelegate>();

				FLootLockerServerCreateLeaderboardRequest Request(Key, TEXT("CI Leaderboard Get"),
					ELootLockerServerLeaderboardDirection::descending, true, true);

				ULootLockerServerLeaderboardRequest::CreateLeaderboard(Request, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				if (!Response.Success)
				{
					AddError(TEXT("Leaderboard setup failed"));
					TestDone.Execute();
					return;
				}
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerGetLeaderboardResponse, FLootLockerServerGetLeaderboardResponseDelegate>();

				ULootLockerServerLeaderboardRequest::GetLeaderboard(Key, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("GetLeaderboard succeeded", Response.Success);
				if (Response.Success)
				{
					TestEqual("Fetched leaderboard has the requested key", Response.Leaderboard.Key, Key);
					TestEqual("Direction method round-trips", Response.Leaderboard.Direction_method, ELootLockerServerLeaderboardDirection::descending);
				}
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerResponse, FLootLockerServerDeleteLeaderboardResponseDelegate>();

				ULootLockerServerLeaderboardRequest::DeleteLeaderboard(Key, Delegate);
				test_util::WaitAndGet(Promise);
			}

			TestDone.Execute();
		});

		LatentIt("ListLeaderboards_IncludesCreatedLeaderboard", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			const FString Key = TEXT("ci_lb_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreateLeaderboardResponse, FLootLockerServerCreateLeaderboardResponseDelegate>();

				FLootLockerServerCreateLeaderboardRequest Request(Key, TEXT("CI Leaderboard List"),
					ELootLockerServerLeaderboardDirection::ascending, true, true);

				ULootLockerServerLeaderboardRequest::CreateLeaderboard(Request, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				if (!Response.Success)
				{
					AddError(TEXT("Leaderboard setup failed"));
					TestDone.Execute();
					return;
				}
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerListLeaderboardsResponse, FLootLockerServerListLeaderboardsResponseDelegate>();

				ULootLockerServerLeaderboardRequest::ListLeaderboards(100, 0, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("ListLeaderboards succeeded", Response.Success);
				if (Response.Success)
				{
					const bool bFound = Response.Items.ContainsByPredicate(
						[Key](const FLootLockerServerLeaderboard& Item) { return Item.Key == Key; });
					TestTrue("Listed leaderboards include the created one", bFound);
				}
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerResponse, FLootLockerServerDeleteLeaderboardResponseDelegate>();

				ULootLockerServerLeaderboardRequest::DeleteLeaderboard(Key, Delegate);
				test_util::WaitAndGet(Promise);
			}

			TestDone.Execute();
		});

		LatentIt("SubmitScore_IsReflectedInMemberRanks", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			const FString Key = TEXT("ci_lb_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreateLeaderboardResponse, FLootLockerServerCreateLeaderboardResponseDelegate>();

				FLootLockerServerCreateLeaderboardRequest Request(Key, TEXT("CI Leaderboard Scores"),
					ELootLockerServerLeaderboardDirection::descending, true, true);

				ULootLockerServerLeaderboardRequest::CreateLeaderboard(Request, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				if (!Response.Success)
				{
					AddError(TEXT("Leaderboard setup failed"));
					TestDone.Execute();
					return;
				}
			}

			FString PlayerUlid;
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerCreatePlayerResponse, FLootLockerServerCreatePlayerResponseDelegate>();

				ULootLockerServerPlayerRequest::CreatePlayer(
					ELootLockerServerCreatePlayerPlatforms::Guest, FGuid::NewGuid().ToString(), Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				if (!Response.Success)
				{
					AddError(TEXT("Player setup failed"));
					TestDone.Execute();
					return;
				}
				PlayerUlid = Response.Player_ulid;
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerLeaderboardSubmitScoreResponse, FLootLockerServerLeaderboardSubmitScoreResponseDelegate>();

				FLootLockerServerLeaderboardSubmitScoreRequest Request;
				Request.Member_id = PlayerUlid;
				Request.Score = 1000;

				ULootLockerServerLeaderboardRequest::SubmitScore(Key, Request, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("SubmitScore succeeded", Response.Success);
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerGetAllMemberRanksResponse, FLootLockerServerGetAllMemberRanksResponseDelegate>();

				ULootLockerServerLeaderboardRequest::GetAllMemberRanks(PlayerUlid, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("GetAllMemberRanks succeeded", Response.Success);
				if (Response.Success)
				{
					const bool bFound = Response.Leaderboards.ContainsByPredicate(
						[Key](const FLootLockerServerLeaderboardEntryWithLeaderboardData& Entry) { return Entry.Leaderboard_key == Key; });
					TestTrue("Member ranks include the leaderboard the score was submitted to", bFound);
				}
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerResponse, FLootLockerServerDeleteLeaderboardResponseDelegate>();

				ULootLockerServerLeaderboardRequest::DeleteLeaderboard(Key, Delegate);
				test_util::WaitAndGet(Promise);
			}

			TestDone.Execute();
		});
	});
}
#endif
