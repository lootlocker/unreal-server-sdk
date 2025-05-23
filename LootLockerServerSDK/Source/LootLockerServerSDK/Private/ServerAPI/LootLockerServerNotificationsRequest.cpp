#include "ServerAPI/LootLockerServerNotificationsRequest.h"

#include "LootLockerServerHttpClient.h"

const FString ULootLockerServerNotificationsRequest::NotificationTypeValidationPatternString = "^[-_a-z0-9]+\\.[-_a-z0-9]+\\.[-_a-z0-9]+$";

ULootLockerServerNotificationsRequest::ULootLockerServerNotificationsRequest()
{
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithoutContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueNull>(),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
		);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithBoolContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, bool Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueBoolean>(Content),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithIntContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, int Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueNumber>(Content),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithLargeIntContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, long long Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP & OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate & OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueNumber>(Content),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithDoubleContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, double Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP & OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate & OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueNumber>(Content),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithFloatContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, float Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP & OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate & OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueNumber>(Content),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithStringContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const FString& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP & OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate & OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueString>(Content),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithJsonContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TSharedPtr<FJsonValue>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP & OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate & OnCompletedRequest)
{
	SendNotificationToPlayer(
		Content,
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}


void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithBoolArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<bool>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP & OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate & OnCompletedRequest)
{
	TArray<TSharedPtr<FJsonValue>> ArrayContent;
	for (const bool& cont : Content)
	{
		ArrayContent.Add(MakeShared<FJsonValueBoolean>(cont));
	}
	SendNotificationToPlayer(
		MakeShared<FJsonValueArray>(ArrayContent),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithIntArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<int>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP & OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate & OnCompletedRequest)
{
	TArray<TSharedPtr<FJsonValue>> ArrayContent;
	for (const int& cont : Content)
	{
		ArrayContent.Add(MakeShared<FJsonValueNumber>(cont));
	}
	SendNotificationToPlayer(
		MakeShared<FJsonValueArray>(ArrayContent),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithLargeIntArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<long long>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	TArray<TSharedPtr<FJsonValue>> ArrayContent;
	for (const long long& cont : Content)
	{
		ArrayContent.Add(MakeShared<FJsonValueNumber>(cont));
	}
	SendNotificationToPlayer(
		MakeShared<FJsonValueArray>(ArrayContent),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithDoubleArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<double>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	TArray<TSharedPtr<FJsonValue>> ArrayContent;
	for (const double& cont : Content)
	{
		ArrayContent.Add(MakeShared<FJsonValueNumber>(cont));
	}
	SendNotificationToPlayer(
		MakeShared<FJsonValueArray>(ArrayContent),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithFloatArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<float>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	TArray<TSharedPtr<FJsonValue>> ArrayContent;
	for (const float& cont : Content)
	{
		ArrayContent.Add(MakeShared<FJsonValueNumber>(cont));
	}
	SendNotificationToPlayer(
		MakeShared<FJsonValueArray>(ArrayContent),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithStringArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FString>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	TArray<TSharedPtr<FJsonValue>> ArrayContent;
	for (const FString& cont : Content)
	{
		ArrayContent.Add(MakeShared<FJsonValueString>(*cont));
	}
	SendNotificationToPlayer(
		MakeShared<FJsonValueArray>(ArrayContent),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}

void ULootLockerServerNotificationsRequest::SendNotificationToPlayerWithJsonArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<TSharedPtr<FJsonValue>>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	SendNotificationToPlayer(
		MakeShared<FJsonValueArray>(Content),
		FLootLockerServerSendNotificationsToPlayerBaseRequest{ NotificationType, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerNotificationPriority"), static_cast<int32>(Priority)).ToLower(), RecipientPlayerUlid, Properties },
		OnCompletedRequestBP,
		OnCompletedRequest
	);
}



void ULootLockerServerNotificationsRequest::SendNotificationToPlayer(
	const TSharedPtr<FJsonValue>& Content,
	const FLootLockerServerSendNotificationsToPlayerBaseRequest& Request,
	const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP,
	const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest)
{
	if (!FRegexMatcher(FRegexPattern(*NotificationTypeValidationPatternString), *Request.Notification_type).FindNext())
	{
		FLootLockerServerSendNotificationsResponse ErrorResponse = LootLockerServerResponseFactory::Error<FLootLockerServerSendNotificationsResponse>("Notification type '" + Request.Notification_type + "' did not match pattern " + NotificationTypeValidationPatternString, LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT);
		OnCompletedRequestBP.ExecuteIfBound(ErrorResponse);
		OnCompletedRequest.ExecuteIfBound(ErrorResponse);
		return;
	}

	if (Request.Recipient.IsEmpty())
	{
		FLootLockerServerSendNotificationsResponse ErrorResponse = LootLockerServerResponseFactory::Error<FLootLockerServerSendNotificationsResponse>("Recipient player ULID not provided", LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT);
		OnCompletedRequestBP.ExecuteIfBound(ErrorResponse);
		OnCompletedRequest.ExecuteIfBound(ErrorResponse);
		return;		
	}

	if (!Content.IsValid())
	{
		FLootLockerServerSendNotificationsResponse ErrorResponse = LootLockerServerResponseFactory::Error<FLootLockerServerSendNotificationsResponse>("Invalid Content supplied", LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT);
		OnCompletedRequestBP.ExecuteIfBound(ErrorResponse);
		OnCompletedRequest.ExecuteIfBound(ErrorResponse);
		return;		
	}

	TSharedPtr<FJsonObject> SerializedRequest = FJsonObjectConverter::UStructToJsonObject(Request);
	SerializedRequest->SetField("content", Content);
	if (!SerializedRequest.IsValid())
	{
		FLootLockerServerSendNotificationsResponse ErrorResponse = LootLockerServerResponseFactory::Error<FLootLockerServerSendNotificationsResponse>("Failed to serialize request", LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT);
		OnCompletedRequestBP.ExecuteIfBound(ErrorResponse);
		OnCompletedRequest.ExecuteIfBound(ErrorResponse);
		return;
	}

	ULootLockerServerHttpClient::SendRawRequest<FLootLockerServerSendNotificationsResponse>(LootLockerServerUtilities::FStringFromJsonObject(SerializedRequest), ULootLockerServerEndpoints::SendNotification, {}, {}, OnCompletedRequestBP, OnCompletedRequest);
}
