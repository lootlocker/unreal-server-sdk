// Copyright (c) 2021 LootLocker


#include "LootLockerServerHttpClient.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/FileHelper.h"
#include "Utils/LootLockerServerUtilities.h"

ULootLockerServerHttpClient::ULootLockerServerHttpClient()
{

}

void ULootLockerServerHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FLootLockerServerResponseCallback& onCompleteRequest, TMap<FString, FString> customHeaders /*= TMap<FString, FString>()*/) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif

	Request->SetURL(endPoint);

	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	const ULootLockerServerConfig* config = GetDefault<ULootLockerServerConfig>();
	Request->SetHeader(TEXT("LL-Version"), config->LootLockerVersion);

	for (TTuple<FString, FString> CustomHeader : customHeaders)
	{
		Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
	}

	Request->SetVerb(requestType);
	Request->SetContentAsString(data);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, endPoint, requestType, data](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerServerResponse response;

			response.Success = ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, data);
			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallStatusCode = Response->GetResponseCode();
			if(!response.Success)
			{
				const TSharedPtr<FJsonObject> JsonObject = LootLockerServerUtilities::JsonObjectFromFString(response.FullTextFromServer);
				const FString ErrorFieldString = JsonObject->HasField("error") && !JsonObject->GetStringField("error").IsEmpty() ? JsonObject->GetStringField("error") : "N/A";
				const FString MessageFieldString = JsonObject->HasField("message") && !JsonObject->GetStringField("message").IsEmpty() ? JsonObject->GetStringField("message") : "N/A";
				const FString TraceIDFieldString = JsonObject->HasField("trace_id") && !JsonObject->GetStringField("trace_id").IsEmpty() ? JsonObject->GetStringField("trace_id") : "N/A";
				response.Error = FString::Format(TEXT("Error {0} with message \"{1}\". Trace Id: {2}"), { ErrorFieldString, MessageFieldString, TraceIDFieldString });
			}
			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();
}

bool ULootLockerServerHttpClient::ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful, FString RequestMethod, FString Endpoint, FString Data)
{
	if (!bWasSuccessful || !InResponse.IsValid())
		return false;

	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode()))
	{
		return true;
	}

	UE_LOG(LogLootLockerServerSDK, Warning, TEXT("Http Response returned error code: %d"), InResponse->GetResponseCode());
	UE_LOG(LogLootLockerServerSDK, Warning, TEXT("Http Response content:\n%s"), *InResponse->GetContentAsString());
	UE_LOG(LogLootLockerServerSDK, Warning, TEXT("Http Request endpoint: %s to %s"), *RequestMethod, *Endpoint);
	UE_LOG(LogLootLockerServerSDK, Warning, TEXT("Http Request data: %s"), *Data);
	return false;
}

void ULootLockerServerHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString> AdditionalFields, const FLootLockerServerResponseCallback& onCompleteRequest, TMap<FString, FString> customHeaders /*= TMap<FString, FString>()*/) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif


	Request->SetURL(endPoint);

	FString Boundary = "lootlockerboundary";

	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=" + Boundary));

	for (TTuple<FString, FString> CustomHeader : customHeaders)
	{
		Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
	}

	Request->SetVerb(requestType);

	TArray<uint8> UpFileRawData;
	if (!FFileHelper::LoadFileToArray(UpFileRawData, *FilePath)) {
		FLootLockerServerResponse FailResponse;
		FailResponse.Success = false;
		FailResponse.FullTextFromServer = FString::Format(TEXT("Could not read file {0}"), { FilePath });
		FailResponse.Error = FailResponse.FullTextFromServer;

		onCompleteRequest.ExecuteIfBound(FailResponse);
		return;
	}

	TArray<uint8> Data;

	const FString BeginBoundary = TEXT("\r\n--" + Boundary + "\r\n");
	const FString EndBoundary = TEXT("\r\n--" + Boundary + "--\r\n");

	for (auto KeyValuePair : AdditionalFields) {
		Data.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());

		FString ParameterEntry = "Content-Type: text/plain; charset=\"utf-8\"\r\n";
		ParameterEntry.Append(TEXT("Content-Disposition: form-data; name=\""));
		ParameterEntry.Append(KeyValuePair.Key);
		ParameterEntry.Append(TEXT("\"\r\n\r\n"));
		ParameterEntry.Append(KeyValuePair.Value);

		Data.Append((uint8*)TCHAR_TO_ANSI(*ParameterEntry), ParameterEntry.Len());
	}

	Data.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());

	FString FileHeader = (TEXT("Content-Type: application/octet-stream\r\n"));
	FileHeader.Append(TEXT("Content-disposition: form-data; name=\"file\"; filename=\""));

	int32 LastSlashPos;
	FilePath.FindLastChar('/', LastSlashPos);
	FString FileName = FilePath.RightChop(LastSlashPos + 1);

	FileHeader.Append(FileName + "\"\r\n\r\n");

	Data.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());
	Data.Append(UpFileRawData);
	Data.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(Data);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, requestType, endPoint](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerServerResponse response;

			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallStatusCode = Response->GetResponseCode();

			response.Success = ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, FString("Data Stream"));
			if (!response.Success)
			{
				const TSharedPtr<FJsonObject> JsonObject = LootLockerServerUtilities::JsonObjectFromFString(response.FullTextFromServer);
				const FString ErrorFieldString = JsonObject->HasField("error") && !JsonObject->GetStringField("error").IsEmpty() ? JsonObject->GetStringField("error") : "N/A";
				const FString MessageFieldString = JsonObject->HasField("message") && !JsonObject->GetStringField("message").IsEmpty() ? JsonObject->GetStringField("message") : "N/A";
				const FString TraceIDFieldString = JsonObject->HasField("trace_id") && !JsonObject->GetStringField("trace_id").IsEmpty() ? JsonObject->GetStringField("trace_id") : "N/A";
				response.Error = FString::Format(TEXT("Error {0} with message \"{1}\". Trace Id: {2}"), { ErrorFieldString, MessageFieldString, TraceIDFieldString });
			}

			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();
}
