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
    const FListFilesForPlayerResponseBP& OnCompletedRequestBP, const FListFilesForPlayerResponse& OnCompletedRequest)
{
    FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerListFilesForPlayerResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerListFilesForPlayerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Listing player files from lootlocker failed"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::ListFilesForPlayerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
    FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

    UE_LOG(LogTemp, Log, TEXT("data=%s"), *ContentString);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerFilesRequest::GetFileByIdForPlayer(int PlayerId, int FileId,
    const FGetFileByIdForPlayerResponseBP& OnCompletedRequestBP, const FGetFileByIdForPlayerResponse& OnCompletedRequest)
{
    FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetFileByIdForPlayerResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerPlayerFile>(response.FullTextFromServer, &ResponseStruct.item, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Getting player file from lootlocker failed"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetFileByIdForPlayerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId, FileId });
    FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

    UE_LOG(LogTemp, Log, TEXT("data=%s"), *ContentString);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerServerFilesRequest::UploadFileForPlayer(int PlayerId, const FString& FilePath, const FString& Purpose,
    const FUploadFileForPlayerResponseBP& OnCompletedRequestBP, const FUploadFileForPlayerResponse& OnCompletedRequest)
{
    FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerUploadFileForPlayerResponse ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = true;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerPlayerFile>(response.FullTextFromServer, &ResponseStruct.item, 0, 0);

            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("Uploading player file to lootlocker failed"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetFileByIdForPlayerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
    FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    TMap<FString, FString> AdditionalFields;
    if (!Purpose.IsEmpty()) {
        AdditionalFields.Add("purpose", Purpose);
    }

    UE_LOG(LogTemp, Log, TEXT("data=%s"), *ContentString);
    HttpClient->UploadFile(endpoint, requestMethod, FilePath, AdditionalFields, sessionResponse, true);
}

void ULootLockerServerFilesRequest::DeleteFileForPlayer(int PlayerId, int FileId, const FDeleteFileForPlayerResponseBP& OnCompletedRequestBP, const FDeleteFileForPlayerResponse& OnCompletedRequest)
{
    FString ContentString;

    FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerDeleteFileForPlayerResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerDeleteFileForPlayerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("DeleteFileForPlayer failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::DeleteFileForPlayerEndpoint;
    FString TempEndpoint = Endpoint.endpoint;
    FString newEndpoint = FString::Format(*TempEndpoint, { PlayerId, FileId });

    FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
