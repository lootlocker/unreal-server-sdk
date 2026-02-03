// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerFileRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerPlayerFileRequest::ULootLockerServerPlayerFileRequest()
{
}

FString ULootLockerServerPlayerFileRequest::ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerFiles, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerFileResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerFileById, { PlayerID, FileID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileDeleteResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeletePlayerFile, { PlayerID, FileID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));

    return ULootLockerServerHttpClient::UploadFile<FLootLockerServerSinglePlayerFileResponse>(FilePath, AdditionalFields, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));

    return ULootLockerServerHttpClient::UploadRawFile<FLootLockerServerSinglePlayerFileResponse>(RawData, FileName, AdditionalFields, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::UploadFile<FLootLockerServerSinglePlayerFileResponse>(FilePath, TMap<FString, FString>(), ULootLockerServerEndpoints::UpdatePlayerFile, { PlayerID, FileID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    return ULootLockerServerHttpClient::UploadRawFile<FLootLockerServerSinglePlayerFileResponse>(RawData, FileName, TMap<FString, FString>(), ULootLockerServerEndpoints::UpdatePlayerFile, { PlayerID, FileID }, {}, OnCompletedRequest);
}
