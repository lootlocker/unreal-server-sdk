#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerReferralRequest.generated.h"

//==================================================
// Enum Definitions
//==================================================

/**
 * The state of a referral relation.
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerReferralStatus : uint8
{
	claimed = 0,
	qualified = 1,
	Void = 2,
};

//==================================================
// Data Type Definitions
//==================================================

/**
 * One referral relation as the server sees it: the program it was made under, both players, and its state.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerReferral
{
	GENERATED_BODY()
	/**
	 The referral ULID
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Id = "";
	/**
	 The ULID of the referral program the referral was made under
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Program_id = "";
	/**
	 The ULID of the player who invited
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Referrer_player_id = "";
	/**
	 The ULID of the player who was invited
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Referee_player_id = "";
	/**
	 The ULID of the cross-game identity the referral is deduplicated on
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Referee_identity_id = "";
	/**
	 The referral code that was redeemed, which is the referrer's public UID
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Code = "";
	/**
	 The state of the referral
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	ELootLockerServerReferralStatus Status = ELootLockerServerReferralStatus::claimed;
	/**
	 When the referral was claimed
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FDateTime Claimed_at = FDateTime(0);
	/**
	 When the referral qualified. Only meaningful when HasQualifiedAt is true
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FDateTime Qualified_at = FDateTime(0);
	/**
	 True when the referral has qualified and Qualified_at holds the time. False while it is still pending
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool HasQualifiedAt = false;
	/**
	 When the referral row was created
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FDateTime Created_at = FDateTime(0);
	/**
	 When the referral row was last updated. Only meaningful when HasUpdatedAt is true
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FDateTime Updated_at = FDateTime(0);
	/**
	 True when the referral row has been updated and Updated_at holds the time
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool HasUpdatedAt = false;
};

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing the referrals that the assert qualified and rewarded. Empty when the player had no
 * pending game_asserted referral.
 */
USTRUCT(BlueprintType, Category = "LootLockerServer")
struct FLootLockerServerAssertReferralResponse : public FLootLockerServerResponse
{
    GENERATED_BODY()
    /**
     The referrals that were qualified by this assert
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    TArray<FLootLockerServerReferral> Referrals;

    /**
     Populate the convenience structures that FJsonObjectConverter cannot derive on its own, notably the
     status enum and the nullable qualified_at and updated_at timestamps.
     */
    void PopulateConvenienceStructures();
};

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for asserting a player's referral qualification
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerAssertReferralResponseDelegate, FLootLockerServerAssertReferralResponse);

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerReferralRequest : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerServerReferralRequest();

    /**
     Report that a player met the qualifying action of their game_asserted referral program(s). The
     referral is rewarded when this succeeds, so only call it once the game has authoritatively observed
     the qualifying action.

     @param PlayerULID The ULID of the player to assert
     @param OnCompletedRequest Delegate for handling the server response
     @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
     */
    static FString AssertPlayerReferralQualification(const FString& PlayerULID, const FLootLockerServerAssertReferralResponseDelegate& OnCompletedRequest);
};
