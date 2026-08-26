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

FString ULootLockerServerPlayerFileRequest::UploadFileForPlayer(int PlayerID, FString FilePath, FString Purpose, bool IsPublic, FString Key, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));
	if (!Key.IsEmpty())
	{
		AdditionalFields.Add(TEXT("key"), *Key);
	}

    return ULootLockerServerHttpClient::UploadFile<FLootLockerServerSinglePlayerFileResponse>(FilePath, AdditionalFields, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::UploadRawDataToPlayerFile(int PlayerID, TArray<uint8> RawData, const FString& FileName, FString Purpose, bool IsPublic, FString Key, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest) 
{
	TMap<FString, FString> AdditionalFields;
	AdditionalFields.Add(TEXT("purpose"), *Purpose);
	AdditionalFields.Add(TEXT("public"), IsPublic? TEXT("true") : TEXT("false"));
	if (!Key.IsEmpty())
	{
		AdditionalFields.Add(TEXT("key"), *Key);
	}

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

FString ULootLockerServerPlayerFileRequest::ListFileRevisionsForPlayer(int PlayerID, int FileID, const FLootLockerServerPlayerFileRevisionsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileRevisionsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerFileRevisions, { PlayerID, FileID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::GetFileRevisionForPlayerByID(int PlayerID, int FileID, const FString& RevisionID, const FLootLockerServerPlayerFileContentResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileContentResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerFileRevision, { PlayerID, FileID, RevisionID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::PromoteFileRevisionForPlayer(int PlayerID, int FileID, const FString& RevisionID, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileDeleteResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::PromotePlayerFileRevision, { PlayerID, FileID, RevisionID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::GetFileByKeyForPlayer(int PlayerID, const FString& Key, const FLootLockerServerSinglePlayerFileResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSinglePlayerFileResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerFileByKey, { PlayerID, Key }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::ListFileRevisionsByKeyForPlayer(int PlayerID, const FString& Key, const FLootLockerServerPlayerFileRevisionsListResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileRevisionsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerFileRevisionsByKey, { PlayerID, Key }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::GetFileRevisionByKeyForPlayer(int PlayerID, const FString& Key, const FString& RevisionID, const FLootLockerServerPlayerFileContentResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileContentResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerFileRevisionByKey, { PlayerID, Key, RevisionID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::PromoteFileRevisionByKeyForPlayer(int PlayerID, const FString& Key, const FString& RevisionID, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileDeleteResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::PromotePlayerFileRevisionByKey, { PlayerID, Key, RevisionID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerFileRequest::DeleteFileByKeyForPlayer(int PlayerID, const FString& Key, const FLootLockerServerPlayerFileDeleteResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerPlayerFileDeleteResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeletePlayerFileByKey, { PlayerID, Key }, {}, OnCompletedRequest);
}
