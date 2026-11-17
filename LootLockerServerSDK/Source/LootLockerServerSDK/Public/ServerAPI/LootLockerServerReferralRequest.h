#pragma once

#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerReferralRequest.generated.h"

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
     The legacy integer id of the game this referral belongs to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    int32 Game_id = 0;
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
     The state of the referral: claimed (pending the qualifying action), qualified (rewarded) or void (voided)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Status = "";
    /**
     When the referral was claimed
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Claimed_at = "";
    /**
     When the referral qualified. Empty while it is still pending
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Qualified_at = "";
    /**
     When the referral row was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Created_at = "";
    /**
     When the referral row was last updated. Empty if it never has been
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
    FString Updated_at = "";
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
