#pragma once

/// @addtogroup Notifications
/// @{

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
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for sending notifications
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSendNotificationsResponseDelegate, FLootLockerServerSendNotificationsResponse);

/**
 *
 */
/// @}

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerNotificationsRequest : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerServerNotificationsRequest();
	static FString SendNotificationToPlayerWithoutContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithBoolContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, bool Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithIntContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, int Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithLargeIntContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, long long Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithDoubleContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, double Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithFloatContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, float Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithStringContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const FString& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithJsonContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TSharedPtr<FJsonValue>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);

	static FString SendNotificationToPlayerWithBoolArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<bool>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithIntArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<int>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithLargeIntArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<long long>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithDoubleArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<double>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithFloatArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<float>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithStringArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<FString>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);
	static FString SendNotificationToPlayerWithJsonArrayContent(const FString& NotificationType, ELootLockerServerNotificationPriority Priority, const FString& RecipientPlayerUlid, const TArray<TSharedPtr<FJsonValue>>& Content, const TArray<FLootLockerServerNotificationProperty>& Properties, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);

private:
	static FString SendNotificationToPlayer(const TSharedPtr<FJsonValue>& Content, const FLootLockerServerSendNotificationsToPlayerBaseRequest& Request, const FLootLockerServerSendNotificationsResponseDelegate& OnCompletedRequest);

	static const FString NotificationTypeValidationPatternString;
};
