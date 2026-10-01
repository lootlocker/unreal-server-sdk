#include <future>

#include "Misc/AutomationTest.h"
#include "Runtime/Launch/Resources/Version.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "ServerAPI/LootLockerServerPlayerFileRequest.h"
#include "ServerAPI/LootLockerServerPlayerRequest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(FTestLootLockerServer_PlayerFiles, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_PlayerFiles)

void FTestLootLockerServer_PlayerFiles::Define()
{
	Describe("Server_PlayerFiles", [this]()
	{
		LatentIt("When Server PlayerFiles", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
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

			int FileId = -1;
			const FString FileName = "test-file.txt";
			const FString FileContent = "testfilecontent";

			// List files
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerPlayerFileListResponse, FLootLockerServerPlayerFileListResponseDelegate>();

				ULootLockerServerPlayerFileRequest::ListFilesForPlayer(PlayerId, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("ListFilesForPlayer Ok", Response.Success);

				for (auto File : Response.Items)
				{
					if (File.Name == FileName)
					{
						FileId = File.Id;
						break;
					}
				}
			}

			// Upload file
			if (FileId == -1)
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSinglePlayerFileResponse, FLootLockerServerSinglePlayerFileResponseDelegate>();

				TArray<uint8> OutBuffer;
				OutBuffer.SetNumUninitialized(FileContent.Len());

 				int32 BufferSize = StringToBytes(FileContent, OutBuffer.GetData(), OutBuffer.Num());				
				ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(PlayerId, OutBuffer, FileName, "test", true, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("UploadRawDataToPlayerFile Ok", Response.Success);
				if (Response.Success)
				{
					TestTrue("UploadRawDataToPlayerFile FileName Ok", FileName.Equals(Response.Name));
					TestTrue("UploadRawDataToPlayerFile FileSize Ok", Response.Size == BufferSize);
					FileId = Response.Id;
				}
			}


			// Get File
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSinglePlayerFileResponse, FLootLockerServerSinglePlayerFileResponseDelegate>();

				ULootLockerServerPlayerFileRequest::GetFileForPlayerByID(PlayerId, FileId, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("GetFileForPlayerByID Ok", Response.Success);
				if (Response.Success)
				{
					TestTrue("GetFileForPlayerByID FileName Ok", FileName.Equals(Response.Name));
				}
			}

			// Update File
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSinglePlayerFileResponse, FLootLockerServerSinglePlayerFileResponseDelegate>();
				
				const FString NewFileContent = "newtestfilecontent";
				
				TArray<uint8> OutBuffer;
				OutBuffer.SetNumUninitialized(NewFileContent.Len());
				
 				int32 BufferSize = StringToBytes(NewFileContent, OutBuffer.GetData(), OutBuffer.Num());				
				ULootLockerServerPlayerFileRequest::UpdatePlayerFileWithRawData(PlayerId, FileId, OutBuffer, FileName, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("UpdatePlayerFileWithRawData Ok", Response.Success);
				if (Response.Success)
				{
					TestTrue("UpdatePlayerFileWithRawData FileName Ok", FileName.Equals(Response.Name));
					TestTrue("UpdatePlayerFileWithRawData FileSize Ok", Response.Size == BufferSize);
				}
			}

			// Delete File
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerServerPlayerFileDeleteResponse, FLootLockerServerPlayerFileDeleteResponseDelegate>();

				ULootLockerServerPlayerFileRequest::DeleteFileForPlayerByID(PlayerId, FileId, Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("DeleteFileForPlayerByID ok", Response.Success);
			}

			TestDone.Execute();
		});
	});
}
#endif

