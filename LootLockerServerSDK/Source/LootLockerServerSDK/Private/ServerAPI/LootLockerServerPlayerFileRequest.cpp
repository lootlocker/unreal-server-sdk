// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerFileRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerPlayerFileRequest::ULootLockerServerPlayerFileRequest()
{
}

void ULootLockerServerPlayerFileRequest::ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerFiles, { PlayerID }, {}, FLootLockerServerPlayerFileListResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerFileResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerFileById, { PlayerID, FileID }, {}, FLootLockerServerSinglePlayerFileResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileDeleteResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeletePlayerFile, { PlayerID, FileID }, {}, FLootLockerServerPlayerFileDeleteResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));

    ULootLockerServerHttpClient::UploadFile<FLootLockerServerSinglePlayerFileResponse>(FilePath, AdditionalFields, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID }, {}, FLootLockerServerSinglePlayerFileResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));

    ULootLockerServerHttpClient::UploadRawFile<FLootLockerServerSinglePlayerFileResponse>(RawData, FileName, AdditionalFields, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID }, {}, FLootLockerServerSinglePlayerFileResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::UploadFile<FLootLockerServerSinglePlayerFileResponse>(FilePath, TMap<FString, FString>(), ULootLockerServerEndpoints::UpdatePlayerFile, { PlayerID, FileID }, {}, FLootLockerServerSinglePlayerFileResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::UploadRawFile<FLootLockerServerSinglePlayerFileResponse>(RawData, FileName, TMap<FString, FString>(), ULootLockerServerEndpoints::UpdatePlayerFile, { PlayerID, FileID }, {}, FLootLockerServerSinglePlayerFileResponseBP(), OnCompletedRequest);
}
