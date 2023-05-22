// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerFileRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerPlayerFileRequest::ULootLockerServerPlayerFileRequest()
{
}

void ULootLockerServerPlayerFileRequest::ListFilesForPlayer(int PlayerID, const FLootLockerServerPlayerFileListResponseBP& OnCompletedRequestBP, const FLootLockerServerPlayerFileListResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileListResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerFiles, { PlayerID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::GetFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerFileResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerFileById, { PlayerID, FileID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::DeleteFileForPlayerByID(int PlayerID, int FileID, const FLootLockerServerPlayerFileDeleteResponseBP& OnCompletedRequestBP, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileDeleteResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeletePlayerFile, { PlayerID, FileID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));

    ULootLockerServerHttpClient::UploadFile<FLootLockerServerSinglePlayerFileResponse>(FilePath, AdditionalFields, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));

    ULootLockerServerHttpClient::UploadRawFile<FLootLockerServerSinglePlayerFileResponse>(RawData, FileName, AdditionalFields, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UpdateFileForPlayer(int PlayerID, int FileID, FString FilePath, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::UploadFile<FLootLockerServerSinglePlayerFileResponse>(FilePath, TMap<FString, FString>(), ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID, FileID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPlayerFileRequest::UpdatePlayerFileWithRawData(int PlayerID, int FileID, TArray<uint8> RawData, const FString& FileName, const FLootLockerServerSinglePlayerFileResponseBP& OnCompletedRequestBP, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::UploadRawFile<FLootLockerServerSinglePlayerFileResponse>(RawData, FileName, TMap<FString, FString>(), ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID, FileID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}
