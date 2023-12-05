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

			const int PlayerId = 3245521; // PlayerIdentifier: TEXT("unreal_unit_test_user")
			// client login is needed for client calls below!
			//test_util::StartGuestSession(PlayerId);

			int FileId = 0;
			const FString FileName = "test-file.txt";

			// Upload file
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerSinglePlayerFileResponse, FLootLockerServerSinglePlayerFileResponseDelegate>();

				TArray<uint8> OutBuffer;
				int32 BufferSize = StringToBytes("testfilecontent", OutBuffer.GetData(), OutBuffer.Num());				
				ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(PlayerId, OutBuffer, FileName, "test", true, FLootLockerServerSinglePlayerFileResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("UploadRawDataToPlayerFile Ok", Response.Success);
				TestTrue("UploadRawDataToPlayerFile FileName Ok", FileName.Equals(Response.Name));
				TestTrue("UploadRawDataToPlayerFile FileSize Ok", Response.Size == BufferSize);

				FileId = Response.Id;

				delete(Promise);
			}

			// List files
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerPlayerFileListResponse, FLootLockerServerPlayerFileListResponseDelegate>();

				ULootLockerServerPlayerFileRequest::ListFilesForPlayer(PlayerId, FLootLockerServerPlayerFileListResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("ListFilesForPlayer Ok", Response.Success);
				TestTrue("ListFilesForPlayer ItemNum Ok", Response.Items.Num() > 0);
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

