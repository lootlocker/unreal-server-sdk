// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"

#include "LootLockerServerPlayerRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Possible player creation platforms
 */
UENUM(BlueprintType, Category = "LootLockerServer")
enum class ELootLockerServerCreatePlayerPlatforms : uint8
{
	Steam = 0, // Corresponds to string "steam"
	PlayStation = 1, // Corresponds to string "psn"
	Apple = 2, // Corresponds to string "apple_sign_in"
	AppleGameCenter = 3, // Corresponds to string "apple_game_center"
	Google = 4, // Corresponds to string "google_sign_in"
	GooglePlayGames = 5, // Corresponds to string "google_play_games"
	Xbox = 6, // Corresponds to string "xbox_one"
	NintendoSwitch = 7, // Corresponds to string "nintendo_switch"
	AmazonLuna = 8, // Corresponds to string "amazon_luna"
	WhiteLabelLogin = 9, // Corresponds to string "white_label_login"
	Guest = 10, // Corresponds to string "guest"
	EpicGames = 11, // Corresponds to string "epic_games"
	Meta = 12, // Corresponds to string "meta"
	Discord = 13 // Corresponds to string "discord"
};

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
	 The ULID of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Ulid;
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

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerInfoFromToken
{
	GENERATED_BODY()
	/*
	 The ID (ulid) of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Id = "";
	/*
	 The legacy id of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Legacy_id = 0;
	/*
	 The token corresponding to this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Token = "";	
};

//==================================================
// Request Definitions
//==================================================

UENUM(BlueprintType)
enum class ELootLockerServerPlayerNameLookupIdType : uint8
{
	Player_id = 0,
   	Player_public_uid = 1,
	Player_guest_login_id = 2,
	Steam_id = 3,
	Psn_id = 4,
	Xbox_id = 5,
	Player_ulid = 6,
	Player_name = 7
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

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerInfoFromGameSessionTokenRequest
{
	GENERATED_BODY()
	/*
	 The tokens you wish to look up
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FString> Tokens;
};

USTRUCT(BlueprintType)
struct FLootLockerServerCreatePlayerRequest
{
	GENERATED_BODY()
	/*
	 The platform you want to create the player on
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Platform = "";
	/*
	 The unique identifier for the player on the platform
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Player_identifier = "";
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

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 A list of tokens that could not be looked up
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FString> Failed_tokens;
	/*
	 A list of players that were successfully looked up with ids and the token corresponding to the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerInfoFromToken> Player_info_list;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerServerCreatePlayerResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 The numeric player id
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Player_id = 0;
	/*
	 The player ulid (LootLocker's unique identifier for the player)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Player_ulid = "";
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for looking up player names
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerPlayerNameLookupResponseBP, FLootLockerServerPlayerNameLookupResponse, Response);
/*
 Blueprint response delegate for looking up players by their game session tokens
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP, FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse, Response);
/*
 Blueprint response delegate for creating a player
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerCreatePlayerResponseBP, FLootLockerServerCreatePlayerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for looking up player names
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerNameLookupResponseDelegate, FLootLockerServerPlayerNameLookupResponse);
/*
 C++ response delegate for looking up players by their game session tokens
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate, FLootLockerServerGetPlayerInfoFromGameSessionTokenResponse);
/*
 C++ response delegate for creating a player
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerCreatePlayerResponseDelegate, FLootLockerServerCreatePlayerResponse);

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
	static void GetPlayerInfoFromGameSessionToken(TArray<FString> GameSessionTokensToLookUp, const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP& OnCompletedRequestBP = FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseBP(), const FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate& OnCompletedRequest = FLootLockerServerGetPlayerInfoFromGameSessionTokenResponseDelegate());
	static void CreatePlayer(ELootLockerServerCreatePlayerPlatforms Platform, const FString& PlatformPlayerIdentifier, const FLootLockerServerCreatePlayerResponseBP& OnCompletedRequestBP = FLootLockerServerCreatePlayerResponseBP(), const FLootLockerServerCreatePlayerResponseDelegate& OnCompletedRequest = FLootLockerServerCreatePlayerResponseDelegate());
};
