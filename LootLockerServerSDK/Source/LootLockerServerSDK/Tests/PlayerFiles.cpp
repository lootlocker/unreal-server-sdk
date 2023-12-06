#include <future>

#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "../Public/ServerAPI/LootLockerServerAuthRequest.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_PlayerFiles, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_PlayerFiles)

void FTestLootLockerServer_PlayerFiles::Define()
{
	Describe("Server_PlayerFiles", [this]()
	{
		LatentIt("When Server PlayerFiles", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			ULootLockerServerAuthRequest::StartSession();

			const int PlayerId = 3245521;

			int FileId = -1;
			const FString FileName = "test-file.txt";
			const FString FileContent = "testfilecontent";
						
			// List files
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerPlayerFileListResponse, FLootLockerServerPlayerFileListResponseDelegate>();

				ULootLockerServerPlayerFileRequest::ListFilesForPlayer(PlayerId, FLootLockerServerPlayerFileListResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("ListFilesForPlayer Ok", Response.Success);

				for (auto File : Response.Items)
				{
					if (File.Name == FileName)
					{
						FileId = File.Id;
						break;
					}
				}
				delete(Promise);
			}

			// Upload file
			if (FileId == -1)
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSinglePlayerFileResponse, FLootLockerServerSinglePlayerFileResponseDelegate>();

				TArray<uint8> OutBuffer;
				OutBuffer.SetNumUninitialized(FileContent.Len());

 				int32 BufferSize = StringToBytes(FileContent, OutBuffer.GetData(), OutBuffer.Num());				
				ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(PlayerId, OutBuffer, FileName, "test", true, FLootLockerServerSinglePlayerFileResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("UploadRawDataToPlayerFile Ok", Response.Success);
				TestTrue("UploadRawDataToPlayerFile FileName Ok", FileName.Equals(Response.Name));
				TestTrue("UploadRawDataToPlayerFile FileSize Ok", Response.Size == BufferSize);

				FileId = Response.Id;

				delete(Promise);
			}


			// Get File
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSinglePlayerFileResponse, FLootLockerServerSinglePlayerFileResponseDelegate>();

				ULootLockerServerPlayerFileRequest::GetFileForPlayerByID(PlayerId, FileId, FLootLockerServerSinglePlayerFileResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("GetFileForPlayerByID Ok", Response.Success);
				TestTrue("GetFileForPlayerByID FileName Ok", FileName.Equals(Response.Name));

				delete(Promise);
			}

			// Update File
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSinglePlayerFileResponse, FLootLockerServerSinglePlayerFileResponseDelegate>();
				
				const FString NewFileContent = "newtestfilecontent";
				
				TArray<uint8> OutBuffer;
				OutBuffer.SetNumUninitialized(NewFileContent.Len());
				
 				int32 BufferSize = StringToBytes(NewFileContent, OutBuffer.GetData(), OutBuffer.Num());				
				ULootLockerServerPlayerFileRequest::UpdatePlayerFileWithRawData(PlayerId, FileId, OutBuffer, FileName, FLootLockerServerSinglePlayerFileResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("GetFileForPlayerByID Ok", Response.Success);
				TestTrue("GetFileForPlayerByID FileName Ok", FileName.Equals(Response.Name));
				TestTrue("UploadRawDataToPlayerFile FileSize Ok", Response.Size == BufferSize);

				delete(Promise);
			}

			// Delete File
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerServerPlayerFileDeleteResponse, FLootLockerServerPlayerFileDeleteResponseDelegate>();

				ULootLockerServerPlayerFileRequest::DeleteFileForPlayerByID(PlayerId, FileId, FLootLockerServerPlayerFileDeleteResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("DeleteFileForPlayerByID ok", Response.Success);

				delete(Promise);
			}

			TestDone.Execute();
		});
	});
}
#endif

