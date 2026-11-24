#include "ServerAPI/LootLockerServerReferralRequest.h"

#include "LootLockerServerHttpClient.h"
#include "LootLockerServerLogger.h"
#include "Utils/LootLockerServerUtilities.h"

namespace
{
    // FJsonObjectConverter skips a JSON null entirely, leaving the struct member at its default. That makes
    // an absent value indistinguishable from a real one, so these flags record which keys actually carried a
    // value. Non-null values are converted by FJsonObjectConverter itself.
    bool HasNonNullField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName)
    {
        if (!JsonObject.IsValid())
        {
            return false;
        }

        const TSharedPtr<FJsonValue> Value = JsonObject->TryGetField(FieldName);
        return Value.IsValid() && Value->Type != EJson::Null;
    }
}

void FLootLockerServerAssertReferralResponse::PopulateConvenienceStructures()
{
    if (FullTextFromServer.IsEmpty())
    {
        return;
    }

    const TSharedPtr<FJsonObject> ResponseAsJson = LootLockerServerUtilities::JsonObjectFromFString(FullTextFromServer);
    if (!ResponseAsJson.IsValid())
    {
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* ReferralsJson = nullptr;
    if (!ResponseAsJson->TryGetArrayField(TEXT("referrals"), ReferralsJson) || ReferralsJson == nullptr)
    {
        return;
    }

    if (ReferralsJson->Num() != Referrals.Num())
    {
        FLootLockerServerLogger::Log("Failed to properly parse referrals", ELootLockerServerLogLevel::Warning);
        return;
    }

    for (int32 Index = 0; Index < Referrals.Num(); ++Index)
    {
        const TSharedPtr<FJsonObject>* ReferralJson = nullptr;
        if (!(*ReferralsJson)[Index].IsValid() || !(*ReferralsJson)[Index]->TryGetObject(ReferralJson) || ReferralJson == nullptr)
        {
            continue;
        }

        Referrals[Index].HasQualifiedAt = HasNonNullField(*ReferralJson, TEXT("qualified_at"));
        Referrals[Index].HasUpdatedAt = HasNonNullField(*ReferralJson, TEXT("updated_at"));
    }
}

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

    using FResponseInspector = ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerAssertReferralResponse>::FLootLockerServerResponseInspectorCallback;

    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAssertReferralResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::AssertPlayerReferralQualification, { PlayerULID }, {}, OnCompletedRequest, FResponseInspector::CreateLambda([](FLootLockerServerAssertReferralResponse& Response)
        {
            if (Response.Success)
            {
                Response.PopulateConvenienceStructures();
            }
        }));
}
