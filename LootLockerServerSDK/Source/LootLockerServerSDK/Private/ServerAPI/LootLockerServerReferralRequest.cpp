#include "ServerAPI/LootLockerServerReferralRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerReferralRequest::ULootLockerServerReferralRequest()
{
}

FString ULootLockerServerReferralRequest::AssertPlayerReferralQualification(const FString& PlayerULID, const FLootLockerServerAssertReferralResponseDelegate& OnCompletedRequest)
{
    if (PlayerULID.IsEmpty())
    {
        OnCompletedRequest.ExecuteIfBound(LootLockerServerResponseFactory::Error<FLootLockerServerAssertReferralResponse>("Player ULID not provided", LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT));
        return FString();
    }

    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssertReferralResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::AssertPlayerReferralQualification, { PlayerULID }, {}, OnCompletedRequest);
}
