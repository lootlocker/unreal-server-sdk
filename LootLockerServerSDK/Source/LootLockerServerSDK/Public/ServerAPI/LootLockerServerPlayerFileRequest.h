// Copyright (c) 2021 LootLocker

#pragma once

/// @addtogroup PlayerFiles
/// @{

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "LootLockerServerResponse.h"

#include "LootLockerServerPlayerFileRequest.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
*
*/
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFile
{
	GENERATED_BODY()
	/*
	 The file ID
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Id = 0;
	/*
	 The revision ID denoting which version of the file this is. The last 5 revisions are kept
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Revision_id = "";
	/*
	 The name of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name = "";
	/*
	 The size of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Size = 0;
	/*
	 The purpose of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Purpose = "";
	/*
	 Whether this file is readable for other players
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool Public = false;
	/*
	 The URL from where you can download the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url = "";
	/*
	 A timestamp for when the url expires (stops being usable)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url_expires_at = "";
	/*
	 A timestamp showing when the file was first created
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Created_at = "";	
};

//==================================================
// Request Definitions
//==================================================

// N/A

//==================================================
// Response Definitions
//==================================================

/**
*
*/
USTRUCT(BlueprintType)
struct FLootLockerServerSinglePlayerFileResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/*
	 The file ID
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Id = 0;
	/*
	 The revision ID denoting which version of the file this is. The last 5 revisions are kept
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Revision_id = "";
	/*
	 The name of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name = "";
	/*
	 The size of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Size = 0;
	/*
	 The purpose of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Purpose = "";
	/*
	 Whether this file is readable for other players
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool Public = false;
	/*
	 The URL from where you can download the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url = "";
	/*
	 A timestamp for when the url expires (stops being usable)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url_expires_at = "";
	/*
	 A timestamp showing when the file was first created
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Created_at = "";
};

/**
*
*/
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFileListResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()

	/*
	 A list of the requested files
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerFile> Items;
};

/**
* Response class for deleting a file, will be empty unless there's an error
*/
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFileDeleteResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
};

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for listing player files
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerFileListResponseDelegate, FLootLockerServerPlayerFileListResponse);
/*
 C++ response delegate for a single returned file
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerSinglePlayerFileResponseDelegate, FLootLockerServerSinglePlayerFileResponse);
/*
 C++ response delegate for a single returned file
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerFileDeleteResponseDelegate, FLootLockerServerPlayerFileDeleteResponse);

/**
 * 
 */
/// @}

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerPlayerFileRequest : public UObject
{
	GENERATED_BODY()
	public:	
	ULootLockerServerPlayerFileRequest();	

	static FString ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseDelegate& OnCompletedRequest);
	static FString GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest);
	static FString UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
};
