#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonValue.h"
#include "LootLockerServerResponse.h"
#include "Internationalization/Regex.h"

#include "LootLockerServerNotificationsRequest.generated.h"

//==================================================
// Enum Definitions
//==================================================

/**
 * Enum of the different available priorities for sending notifications
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerServerNotificationPriority : uint8
{
	low = 0,
	medium = 1,
	high = 2,
};

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerNotificationProperty
{
	GENERATED_BODY()
	/*
	 The key for this property (used to look up the property)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key = "";
	/*
	 The value for this property (corresponding to the key in question)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Value = "";
};

USTRUCT(BlueprintType)
struct FLootLockerServerNotificationNoContentObject
{
	GENERATED_BODY()
};

//==================================================
// Request Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerSendNotificationsToPlayerBaseRequest
{
	GENERATED_BODY()
	/*
	 The type of this notification. Must match pattern ^[a-z_-]+\.[a-z_-]+\.[a-z_-]+$
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Notification_type = "";
	/*
	 The priority of this notification (default: medium)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Priority = "medium";
	/*
	 The ulid of the player that should receive this notification
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Recipient = "";
	/*
	 A list of key value properties for this notification
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerNotificationProperty> Properties;
};


//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerSendNotificationsResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	// Empty Response
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for sending notifications
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerSendNotificationsResponseBP, FLootLockerServerSendNotificationsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for sending notifications
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSendNotificationsResponseDelegate, FLootLockerServerSendNotificationsResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerNotificationsRequest : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerServerNotificationsRequest();
	static void SendNotificationToPlayerWithoutContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithBoolContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, bool Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithIntContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, int Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithLargeIntContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, long long Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithDoubleContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, double Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithFloatContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, float Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithStringContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const FString& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithJsonContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TSharedPtr<FJsonValue>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());

	static void SendNotificationToPlayerWithBoolArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<bool>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithIntArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<int>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithLargeIntArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<long long>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithDoubleArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<double>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithFloatArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<float>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithStringArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FString>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());
	static void SendNotificationToPlayerWithJsonArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<TSharedPtr<FJsonValue>>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());

private:
	static void SendNotificationToPlayer(const TSharedPtr<FJsonValue>& Content, const FLootLockerServerSendNotificationsToPlayerBaseRequest& Request, const FLootLockerServerSendNotificationsResponseBP& OnCompletedRequestBP = FLootLockerServerSendNotificationsResponseBP(), const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest = FLootLockerServerSendNotificationsResponseDelegate());

	static const FString NotificationTypeValidationPatternString;
	static const FRegexPattern NotificationTypeValidationPattern;
};
