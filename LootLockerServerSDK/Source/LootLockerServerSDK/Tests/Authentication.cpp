#include <future>

#include "Runtime/Launch/Resources/Version.h"
#include "Misc/AutomationTest.h"
#include "ServerAPI/LootLockerServerAuthRequest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_Authentication, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_Authentication)

void FTestLootLockerServer_Authentication::Define()
{
	Describe("Server_Authentication", [this]()
	{
		LatentIt("When Start/End server session", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{			
			// start session
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerAuthenticationResponse, FLootLockerServerAuthResponseDelegate>();
		
				ULootLockerServerAuthRequest::StartSession(FLootLockerServerAuthResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("StartSession success", Response.Success);
				TestFalse("StartSession session token not empty", Response.Token.IsEmpty());
				delete(Promise);
			}
			// maintain session
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerResponse, FLootLockerServerMaintainSessionResponseDelegate>();
		
				ULootLockerServerAuthRequest::MaintainSession(FLootLockerServerMaintainSessionResponseBP(), Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("MaintainSession success", Response.Success);
				delete(Promise);
			}
			TestDone.Execute();
		});
	});
}
#endif

