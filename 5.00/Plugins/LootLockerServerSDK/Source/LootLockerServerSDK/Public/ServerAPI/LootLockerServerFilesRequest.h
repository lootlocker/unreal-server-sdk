// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "LootLockerServerAssetRequest.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerHttpClient.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerServerFilesRequest.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFile {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 size;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString expires_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at;
};

USTRUCT(BlueprintType)
struct FLootLockerServerListFilesForPlayerResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPlayerFile> items;
};

USTRUCT(BlueprintType)
struct FLootLockerServerGetFileByIdForPlayerResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerPlayerFile item;
};

USTRUCT(BlueprintType)
struct FLootLockerServerUploadFileForPlayerResponse : public FLootLockerServerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerServerPlayerFile item;
};

USTRUCT(BlueprintType)
struct FLootLockerServerDeleteFileForPlayerResponse : public FLootLockerServerResponse {
	GENERATED_BODY()
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FListFilesForPlayerResponseBP, FLootLockerServerListFilesForPlayerResponse, ListFilesForPlayerResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetFileByIdForPlayerResponseBP, FLootLockerServerGetFileByIdForPlayerResponse, GetFileByIdForPlayerResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FUploadFileForPlayerResponseBP, FLootLockerServerUploadFileForPlayerResponse, UploadFileForPlayerResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDeleteFileForPlayerResponseBP, FLootLockerServerDeleteFileForPlayerResponse, DeleteFileForPlayerResponse);
DECLARE_DELEGATE_OneParam(FListFilesForPlayerResponse, FLootLockerServerListFilesForPlayerResponse);
DECLARE_DELEGATE_OneParam(FGetFileByIdForPlayerResponse, FLootLockerServerGetFileByIdForPlayerResponse);
DECLARE_DELEGATE_OneParam(FUploadFileForPlayerResponse, FLootLockerServerUploadFileForPlayerResponse);
DECLARE_DELEGATE_OneParam(FDeleteFileForPlayerResponse, FLootLockerServerDeleteFileForPlayerResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerFilesRequest : public UObject
{
	GENERATED_BODY()

public:	
	ULootLockerServerFilesRequest();

	static void ListFilesForPlayer(int PlayerId, const FListFilesForPlayerResponseBP& OnCompletedRequestBP = FListFilesForPlayerResponseBP(), const FListFilesForPlayerResponse& OnCompletedRequest = FListFilesForPlayerResponse());

	static void GetFileByIdForPlayer(int PlayerId, int FileId, const FGetFileByIdForPlayerResponseBP& OnCompletedRequestBP = FGetFileByIdForPlayerResponseBP(), const FGetFileByIdForPlayerResponse& OnCompletedRequest = FGetFileByIdForPlayerResponse());

	static void UploadFileForPlayer(int PlayerId, const FString &FilePath, const FString& Purpose, const FUploadFileForPlayerResponseBP& OnCompletedRequestBP = FUploadFileForPlayerResponseBP(), const FUploadFileForPlayerResponse& OnCompletedRequest = FUploadFileForPlayerResponse());

	static void DeleteFileForPlayer(int PlayerId, int FileId, const FDeleteFileForPlayerResponseBP& OnCompletedRequestBP = FDeleteFileForPlayerResponseBP(), const FDeleteFileForPlayerResponse& OnCompletedRequest = FDeleteFileForPlayerResponse());

protected:
	static ULootLockerServerHttpClient* HttpClient;
};
