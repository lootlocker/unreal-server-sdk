// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerFilesRequest.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerGameEndpoints.h"

ULootLockerServerHttpClient* ULootLockerServerFilesRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerFilesRequest::ULootLockerServerFilesRequest()
{
	HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerFilesRequest::ListFilesForPlayer(int PlayerId,
    const FListFilesForPlayerResponseBP& OnCompletedRequestBP, const FServerListFilesForPlayerResponseDelegate& OnCompletedRequest)
{
    const FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse Response)
        {
            FLootLockerServerListFilesForPlayerResponse ResponseStruct;
            if (Response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerListFilesForPlayerResponse>(Response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Listing player files from lootlocker failed"));
            }
            ResponseStruct.FullTextFromServer = Response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FLootLockerServerEndPoints ServerEndpoint = ULootLockerServerGameEndpoints::ListFilesForPlayerEndpoint;
    const FString Endpoint = FString::Format(*(ServerEndpoint.endpoint), { PlayerId });
    const FString RequestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(ServerEndpoint.requestMethod));

    const FString ContentString;
    HttpClient->SendApi(Endpoint, RequestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerFilesRequest::GetFileByIdForPlayer(int PlayerId, int FileId,
    const FGetFileByIdForPlayerResponseBP& OnCompletedRequestBP, const FServerGetFileByIdForPlayerResponseDelegate& OnCompletedRequest)
{
    const FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse Response)
    {
        FLootLockerServerGetFileByIdForPlayerResponse ResponseStruct;
        if (Response.success)
        {
            ResponseStruct.success = true;
            FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerPlayerFile>(Response.FullTextFromServer, &ResponseStruct.item, 0, 0);
        }
        else {
            ResponseStruct.success = false;
            UE_LOG(LogTemp, Error, TEXT("Getting player file from lootlocker failed"));
        }
        ResponseStruct.FullTextFromServer = Response.FullTextFromServer;
        OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
        OnCompletedRequest.ExecuteIfBound(ResponseStruct);
    });

    FLootLockerServerEndPoints ServerEndpoint = ULootLockerServerGameEndpoints::GetFileByIdForPlayerEndpoint;
    const FString Endpoint = FString::Format(*(ServerEndpoint.endpoint), { PlayerId, FileId });
    const FString RequestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(ServerEndpoint.requestMethod));

    const FString ContentString;
    HttpClient->SendApi(Endpoint, RequestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerFilesRequest::UploadFileForPlayer(int PlayerId, const FString& FilePath, const FString& Purpose,
    const FUploadFileForPlayerResponseBP& OnCompletedRequestBP, const FServerUploadFileForPlayerResponseDelegate& OnCompletedRequest)
{
    const FServerResponseCallback SessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse Response)
    {
        FLootLockerServerUploadFileForPlayerResponse ResponseStruct;
        if (Response.success)
        {
            ResponseStruct.success = true;
            FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerPlayerFile>(Response.FullTextFromServer, &ResponseStruct.item, 0, 0);

        }
        else {
            ResponseStruct.success = false;
            UE_LOG(LogTemp, Error, TEXT("Uploading player file to lootlocker failed"));
        }
        ResponseStruct.FullTextFromServer = Response.FullTextFromServer;
        OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
        OnCompletedRequest.ExecuteIfBound(ResponseStruct);
    });

    const FLootLockerServerEndPoints ServerEndpoint = ULootLockerServerGameEndpoints::UploadFileForPlayerEndpoint;
    const FString Endpoint = FString::Format(*(ServerEndpoint.endpoint), { PlayerId });
    const FString RequestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(ServerEndpoint.requestMethod));
    TMap<FString, FString> AdditionalFields;
    if (!Purpose.IsEmpty()) {
        AdditionalFields.Add("purpose", Purpose);
    }

    HttpClient->UploadFile(Endpoint, RequestMethod, FilePath, AdditionalFields, SessionResponse, true);
}

void ULootLockerServerFilesRequest::DeleteFileForPlayer(int PlayerId, int FileId,
    const FDeleteFileForPlayerResponseBP& OnCompletedRequestBP, const FServerDeleteFileForPlayerResponseDelegate& OnCompletedRequest)
{
    const FServerResponseCallback SessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse Response)
    {
        FLootLockerServerDeleteFileForPlayerResponse ResponseStruct; 
        if (Response.success)
        {
            ResponseStruct.success = true;
        }
        else {
            ResponseStruct.success = false;
            UE_LOG(LogTemp, Error, TEXT("DeleteFileForPlayer failed from lootlocker"));
        }
        ResponseStruct.ServerCallStatusCode = Response.ServerCallStatusCode;
        ResponseStruct.ServerCallHasError = Response.ServerCallHasError;
        ResponseStruct.FullTextFromServer = Response.FullTextFromServer;
        OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
        OnCompletedRequest.ExecuteIfBound(ResponseStruct);
    });

    FLootLockerServerEndPoints ServerEndpoint = ULootLockerServerGameEndpoints::DeleteFileForPlayerEndpoint;
    const FString Endpoint = FString::Format(*ServerEndpoint.endpoint, { PlayerId, FileId });

    const FString RequestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(ServerEndpoint.requestMethod));
    const FString ContentString;
    HttpClient->SendApi(Endpoint, RequestMethod, ContentString, SessionResponse, true);
}
