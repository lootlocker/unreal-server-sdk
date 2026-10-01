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
		
				ULootLockerServerAuthRequest::StartSession(Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("StartSession success", Response.Success);
				TestFalse("StartSession session token not empty", Response.Token.IsEmpty());
			}
			// maintain session
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerMaintainSessionResponse, FLootLockerServerMaintainSessionResponseDelegate>();
		
				ULootLockerServerAuthRequest::MaintainSession(Delegate);

				const auto Response = test_util::WaitAndGet(Promise);
				TestTrue("MaintainSession success", Response.Success);
			}
			TestDone.Execute();
		});
	});
}
#endif

