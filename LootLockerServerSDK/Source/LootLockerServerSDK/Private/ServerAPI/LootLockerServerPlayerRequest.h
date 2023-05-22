// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerSDK/Private/LootLockerServerResponse.h"

#include "LootLockerServerPlayerRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerName
{
	GENERATED_BODY()
	/*
	 The ID of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Player_id = 0;
	/*
	 The Public UID of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Player_public_uid = "";
	/*
	 The name of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name = "";
	/*
	 The platform that the player was last active on
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Last_active_platform = "";
	/*
	 Optional: The id of the player on said platform
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Platform_player_id = "";
	
};

//==================================================
// Request Definitions
//==================================================

UENUM(BlueprintType)
enum class ELootLockerServerPlayerNameLookupIdType : uint8
{
	Player_id = 0,
   	Player_public_uid = 1,
	Player_login_guest_id = 2,
	Steam_id = 3,
	Psn_id = 4,
	Xbox_id = 5
};

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerNameLookupPair
{
	GENERATED_BODY()
	/*
	 The type of id that you want to look up
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	ELootLockerServerPlayerNameLookupIdType IdType = ELootLockerServerPlayerNameLookupIdType::Player_id;
	/*
	 The id you want to look up
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Id = "";
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerNameLookupResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 The name data found for the requested player's
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerName> Players;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for looking up player names
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerNameLookupResponseBP, FLootLockerServerPlayerNameLookupResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for looking up player names
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerNameLookupResponseDelegate, FLootLockerServerPlayerNameLookupResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPlayerRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerPlayerRequest();	

	static void LookupPlayerNames(TArray<FLootLockerServerPlayerNameLookupPair> IdsToLookUp, const FLootLockerServerPlayerNameLookupResponseBP& OnCompletedRequestBP = FLootLockerServerPlayerNameLookupResponseBP(), const FLootLockerServerPlayerNameLookupResponseDelegate& OnCompletedRequest = FLootLockerServerPlayerNameLookupResponseDelegate());
};
