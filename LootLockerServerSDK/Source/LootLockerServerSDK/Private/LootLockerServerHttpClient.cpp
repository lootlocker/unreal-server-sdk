// Copyright (c) 2021 LootLocker


#include "LootLockerServerHttpClient.h"
#include "Containers/Array.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/FileHelper.h"
#include "Utils/LootLockerServerUtilities.h"

ULootLockerServerHttpClient* ULootLockerServerHttpClient::Instance = nullptr;

ULootLockerServerHttpClient& ULootLockerServerHttpClient::GetInstance()
{
	if (Instance != nullptr)
	{
		Instance = NewObject<ULootLockerServerHttpClient>();

		Instance->AddToRoot();
	}
	return *Instance;
}

void ULootLockerServerHttpClient::SendRequest_Internal(HTTPRequest InRequest) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif

	Request->SetURL(InRequest.EndPoint);

	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	const ULootLockerServerConfig* config = GetDefault<ULootLockerServerConfig>();
	Request->SetHeader(TEXT("LL-Version"), config->LootLockerVersion);

	for (const TTuple<FString, FString>& CustomHeader : InRequest.CustomHeaders)
	{
		Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
	}

	Request->SetVerb(InRequest.RequestType);
	Request->SetContentAsString(InRequest.Data);


#if WITH_EDITOR
	FString DelimitedHeaders;
	TArray<FString> AllHeaders = Request->GetAllHeaders();
	for (auto Header : AllHeaders)
	{
        DelimitedHeaders += TEXT("____") + Header + TEXT("\n");
	}
	UE_LOG(LogLootLockerServerSDK, Log, TEXT("Request to endpoint %s\n__With headers %s\n__And with content: %s"), *Request->GetURL(), *DelimitedHeaders, *InRequest.Data);
#endif //WITH_EDITOR

	Request->OnProcessRequestComplete().BindLambda([InRequest](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerServerResponse response;

			response.Success = ResponseIsValid(Response, bWasSuccessful, InRequest.RequestType, InRequest.EndPoint, InRequest.Data);
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
			InRequest.OnCompleteRequest.ExecuteIfBound(response);
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

void ULootLockerServerHttpClient::UploadFile_Internal(const FString& FilePath, const TMap<FString, FString> AdditionalFields, HTTPRequest InRequest) const
{
	TArray<uint8> RawData;
	if (!FFileHelper::LoadFileToArray(RawData, *FilePath)) {
		FLootLockerServerResponse FailResponse;
		FailResponse.Success = false;
		FailResponse.FullTextFromServer = FString::Format(TEXT("Could not read file {0}"), { FilePath });
		FailResponse.Error = FailResponse.FullTextFromServer;

		InRequest.OnCompleteRequest.ExecuteIfBound(FailResponse);
		return;
	}

	int32 LastSlashPos;
	FilePath.FindLastChar('/', LastSlashPos);
	FString FileName = FilePath.RightChop(LastSlashPos + 1);

	UploadRawFile_Internal(RawData, FileName, AdditionalFields, InRequest);
}

void ULootLockerServerHttpClient::UploadRawFile_Internal(const TArray<uint8>& RawData, const FString& FileName, const TMap<FString, FString> AdditionalFields, HTTPRequest InRequest) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif

	Request->SetURL(*InRequest.EndPoint);

	FString Boundary = "lootlockerboundary";

	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=" + Boundary));

	for (const TTuple<FString, FString>& CustomHeader : InRequest.CustomHeaders)
	{
		Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
	}

	Request->SetVerb(InRequest.RequestType);

	TArray<uint8> Data;

	const FString BeginBoundary = TEXT("\r\n--" + Boundary + "\r\n");
	const FString EndBoundary = TEXT("\r\n--" + Boundary + "--\r\n");

	for (const TTuple<FString, FString>& KeyValuePair : AdditionalFields) {
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

	FileHeader.Append(FileName + "\"\r\n\r\n");

	Data.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());
	Data.Append(RawData);
	Data.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(Data);

	Request->OnProcessRequestComplete().BindLambda([this, InRequest](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerServerResponse response;

			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallStatusCode = Response->GetResponseCode();

			response.Success = ResponseIsValid(Response, bWasSuccessful, InRequest.RequestType, InRequest.EndPoint, FString("Data Stream"));
			if (!response.Success)
			{
				const TSharedPtr<FJsonObject> JsonObject = LootLockerServerUtilities::JsonObjectFromFString(response.FullTextFromServer);
				const FString ErrorFieldString = JsonObject->HasField("error") && !JsonObject->GetStringField("error").IsEmpty() ? JsonObject->GetStringField("error") : "N/A";
				const FString MessageFieldString = JsonObject->HasField("message") && !JsonObject->GetStringField("message").IsEmpty() ? JsonObject->GetStringField("message") : "N/A";
				const FString TraceIDFieldString = JsonObject->HasField("trace_id") && !JsonObject->GetStringField("trace_id").IsEmpty() ? JsonObject->GetStringField("trace_id") : "N/A";
				response.Error = FString::Format(TEXT("Error {0} with message \"{1}\". Trace Id: {2}"), { ErrorFieldString, MessageFieldString, TraceIDFieldString });
			}

			InRequest.OnCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();
}
