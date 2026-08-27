// Copyright (c) 2021 LootLocker

#pragma once

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
	/**
	 The file ID
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Id = 0;
	/**
	 The revision ID denoting which version of the file this is. The last 5 revisions are kept
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Revision_id = "";
	/**
	 The name of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name = "";
	/**
	 The optional key for upsert operations
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key = "";
	/**
	 The size of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Size = 0;
	/**
	 The purpose of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Purpose = "";
	/**
	 Whether this file is readable for other players
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool Public = false;
	/**
	 The URL from where you can download the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url = "";
	/**
	 A timestamp for when the url expires (stops being usable)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url_expires_at = "";
	/**
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
	/**
	 The file ID
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Id = 0;
	/**
	 The revision ID denoting which version of the file this is. The last 5 revisions are kept
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Revision_id = "";
	/**
	 The name of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name = "";
	/**
	 The optional key for upsert operations
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key = "";
	/**
	 The size of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Size = 0;
	/**
	 The purpose of the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Purpose = "";
	/**
	 Whether this file is readable for other players
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	bool Public = false;
	/**
	 The URL from where you can download the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url = "";
	/**
	 A timestamp for when the url expires (stops being usable)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url_expires_at = "";
	/**
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

	/**
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

/**
* Response class for a single file revision
*/
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFileContentResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/**
	 The ULID of this revision
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Id = "";
	/**
	 The signed URL to download this revision
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Url = "";
	/**
	 The file size in bytes
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Size = 0;
	/**
	 When this revision was created
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Created_at = "";
};

/**
* Metadata about a player file, returned as part of the revisions response
*/
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFileMetadata
{
	GENERATED_BODY()
	/**
	 When the file was created
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Created_at = "";
	/**
	 The file name
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Name = "";
	/**
	 The optional key for upsert operations
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Key = "";
	/**
	 The purpose or category tag for this file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Purpose = "";
	/**
	 The unique identifier of this player file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	int Id = 0;
};

/**
* Response class for listing file revisions
*/
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFileRevisionsResponse : public FLootLockerServerResponse
{
	GENERATED_BODY()
	/**
	 The list of revisions
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	TArray<FLootLockerServerPlayerFileContentResponse> Revisions;
	/**
	 Metadata about the file
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FLootLockerServerPlayerFileMetadata File;
	/**
	 The ULID of the current (active) revision
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")
	FString Current_revision_id = "";
};

/**
* Response class for promoting a file revision, will be empty unless there's an error
*/
USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFilePromoteResponse : public FLootLockerServerResponse
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
 C++ response delegate for deleting a file, will be empty unless there's an error
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerFileDeleteResponseDelegate, FLootLockerServerPlayerFileDeleteResponse);
/*
 C++ response delegate for listing file revisions
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerFileRevisionsListResponseDelegate, FLootLockerServerPlayerFileRevisionsResponse);
/*
 C++ response delegate for a single file revision
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerFileContentResponseDelegate, FLootLockerServerPlayerFileContentResponse);
/*
 C++ response delegate for a promote file revision response
 */
DECLARE_DELEGATE_OneParam(FLootLockerServerPlayerFilePromoteResponseDelegate, FLootLockerServerPlayerFilePromoteResponse);

/**
 * 
 */

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
	static FString UploadFileForPlayerByKey(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, FString Key, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString UploadRawDataToPlayerFileByKey(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, FString Key, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString ListFileRevisionsForPlayer(int PlayerID, int FileID, const FLootLockerServerPlayerFileRevisionsListResponseDelegate& OnCompletedRequest);
	static FString GetFileRevisionForPlayerByID(int PlayerID, int FileID, const FString& RevisionID, const FLootLockerServerPlayerFileContentResponseDelegate& OnCompletedRequest);
	static FString PromoteFileRevisionForPlayer(int PlayerID, int FileID, const FString& RevisionID, const FLootLockerServerPlayerFilePromoteResponseDelegate& OnCompletedRequest);
	static FString GetFileByKeyForPlayer(int PlayerID, const FString& Key, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest);
	static FString ListFileRevisionsByKeyForPlayer(int PlayerID, const FString& Key, const FLootLockerServerPlayerFileRevisionsListResponseDelegate& OnCompletedRequest);
	static FString GetFileRevisionByKeyForPlayer(int PlayerID, const FString& Key, const FString& RevisionID, const FLootLockerServerPlayerFileContentResponseDelegate& OnCompletedRequest);
	static FString PromoteFileRevisionByKeyForPlayer(int PlayerID, const FString& Key, const FString& RevisionID, const FLootLockerServerPlayerFilePromoteResponseDelegate& OnCompletedRequest);
	static FString DeleteFileByKeyForPlayer(int PlayerID, const FString& Key, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest);
};
