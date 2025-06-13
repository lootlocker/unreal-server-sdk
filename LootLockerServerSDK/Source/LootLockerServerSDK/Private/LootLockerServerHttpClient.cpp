// Copyright (c) 2021 LootLocker


#include "LootLockerServerHttpClient.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Containers/Array.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/FileHelper.h"
#include "LootLockerServerLogger.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Guid.h"

ULootLockerServerHttpClient* ULootLockerServerHttpClient::Instance = nullptr;

ULootLockerServerHttpClient& ULootLockerServerHttpClient::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<ULootLockerServerHttpClient>();

		Instance->AddToRoot();
	}
	return *Instance;
}

ULootLockerServerHttpClient::ULootLockerServerHttpClient()
	: UserAgent(FString::Format(TEXT("X-UnrealEngineServer-Agent/{0}"), { ENGINE_VERSION_STRING }))
	, UserInstanceIdentifier(FGuid::NewGuid().ToString())
{
	if (SDKVersion.IsEmpty())
	{
		const TSharedPtr<IPlugin> Ptr = IPluginManager::Get().FindPlugin("LootLockerServerSDK");
		if (Ptr.IsValid())
		{
			SDKVersion = Ptr->GetDescriptor().VersionName;
			FLootLockerServerLogger::Log(FString::Format(TEXT("LootLockerServer version: v{0}"), { SDKVersion }), ELootLockerServerLogLevel::Verbose);
		}
	}
}

void ULootLockerServerHttpClient::SendRequest_Internal(HTTPRequest InRequest) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();

	Request->SetURL(InRequest.EndPoint);

	Request->SetHeader(TEXT("User-Agent"), UserAgent);
	Request->SetHeader(TEXT("User-Instance-Identifier"), UserInstanceIdentifier);
	Request->SetHeader(TEXT("SDK-Version"), SDKVersion);
	Request->SetHeader(TEXT("Content-Type"), InRequest.ContentType);
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	const ULootLockerServerConfig* config = GetDefault<ULootLockerServerConfig>();
	Request->SetHeader(TEXT("LL-Version"), config->LootLockerVersion);

	for (const TTuple<FString, FString>& CustomHeader : InRequest.CustomHeaders)
	{
		Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
	}

	Request->SetVerb(InRequest.RequestType);
	Request->SetContentAsString(InRequest.Data);

	FString RequestHeaders = FString::Join(Request->GetAllHeaders(), TEXT("\n"));

    FDateTime RequestTime = FDateTime::Now();

	Request->OnProcessRequestComplete().BindLambda([InRequest, RequestHeaders, RequestTime](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (!Response.IsValid())
		{
			FLootLockerServerResponse Error = LootLockerServerResponseFactory::Error<FLootLockerServerResponse>("HTTP Response was invalid", LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_HTTP);
			LogFailedRequestInformation(Error, InRequest.RequestType, InRequest.EndPoint, InRequest.Data, RequestHeaders, TArray<FString>(), RequestTime);
			InRequest.OnCompleteRequest.ExecuteIfBound(Error);
			return;
		}
		FLootLockerServerResponse response;
		response.Success = ResponseIsSuccess(Response, bWasSuccessful);
		response.StatusCode = Response->GetResponseCode();
		response.FullTextFromServer = Response->GetContentAsString();
		if (!response.Success)
		{
			FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerErrorData>(
				response.FullTextFromServer, &response.ErrorData, 0, 0);
			if (response.ErrorData.Code.IsEmpty())
			{
				response.ErrorData.Message = response.FullTextFromServer;
			}

			FString RetryAfterHeader = Response->GetHeader("retry-after");
			if (!RetryAfterHeader.IsEmpty()) {
				response.ErrorData.Retry_after_seconds = FCString::Atoi(*RetryAfterHeader);
			}
			LogFailedRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, InRequest.Data, RequestHeaders, Response->GetAllHeaders(), RequestTime);
		}
		else
		{
			LogSuccessfulRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, InRequest.Data, RequestHeaders, Response->GetAllHeaders(), RequestTime);
		}
		InRequest.OnCompleteRequest.ExecuteIfBound(response);
	});
	Request->ProcessRequest();
}

void ULootLockerServerHttpClient::UploadFile_Internal(const FString& FilePath, const TMap<FString, FString> AdditionalFields, HTTPRequest InRequest) const
{
	TArray<uint8> RawData;
	if (!FFileHelper::LoadFileToArray(RawData, *FilePath)) {
		InRequest.OnCompleteRequest.ExecuteIfBound(LootLockerServerResponseFactory::Error<FLootLockerServerResponse>(FString::Format(TEXT("Could not read file {0}"), { FilePath }), LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT));
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
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();

	Request->SetURL(InRequest.EndPoint);

	FString Boundary = "lootlockerboundary";

	Request->SetHeader(TEXT("User-Agent"), UserAgent);
	Request->SetHeader(TEXT("User-Instance-Identifier"), UserInstanceIdentifier);
	Request->SetHeader(TEXT("SDK-Version"), SDKVersion);
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

	FString RequestHeaders = FString::Join(Request->GetAllHeaders(), TEXT("\n"));

    FDateTime RequestTime = FDateTime::Now();

	Request->OnProcessRequestComplete().BindLambda([this, InRequest, RequestHeaders, RequestTime](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (!Response.IsValid())
		{
			FLootLockerServerResponse Error = LootLockerServerResponseFactory::Error<FLootLockerServerResponse>("HTTP Response was invalid", LootLockerServerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_HTTP);
			LogFailedRequestInformation(Error, InRequest.RequestType, InRequest.EndPoint, FString("Data Stream"), RequestHeaders, TArray<FString>(), RequestTime);
			InRequest.OnCompleteRequest.ExecuteIfBound(Error);
			return;
		}
		FLootLockerServerResponse response;
		response.Success = ResponseIsSuccess(Response, bWasSuccessful);
		response.StatusCode = Response->GetResponseCode();
		response.FullTextFromServer = Response->GetContentAsString();
		if (!response.Success)
		{
			FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerErrorData>(
				response.FullTextFromServer, &response.ErrorData, 0, 0);
			if (response.ErrorData.Code.IsEmpty())
			{
				response.ErrorData.Message = response.FullTextFromServer;
			}

			FString RetryAfterHeader = Response->GetHeader("retry-after");
			if (!RetryAfterHeader.IsEmpty())
			{
				response.ErrorData.Retry_after_seconds = FCString::Atoi(*RetryAfterHeader);
			}
			LogFailedRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, FString("Data Stream"), RequestHeaders, Response->GetAllHeaders(), RequestTime);
		}
		else 
		{
			LogSuccessfulRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, FString("Data Stream"), RequestHeaders, Response->GetAllHeaders(), RequestTime);
		}

		InRequest.OnCompleteRequest.ExecuteIfBound(response);
	});
	Request->ProcessRequest();
}

bool ULootLockerServerHttpClient::ResponseIsSuccess(const FHttpResponsePtr& InResponse, bool bWasSuccessful)
{
	if (!bWasSuccessful || !InResponse.IsValid())
		return false;

	return EHttpResponseCodes::IsOk(InResponse->GetResponseCode());
}

void ULootLockerServerHttpClient::LogFailedRequestInformation(const FLootLockerServerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const FString& DelimitedRequestHeaders, const TArray<FString>& ResponseHeaders, const FDateTime& RequestStartTime)
{
    FLootLockerServerHttpLogEntry LogEntry;
    LogEntry.Method = RequestMethod;
    LogEntry.Path = Endpoint;
    LogEntry.StatusCode = Response.StatusCode;
    LogEntry.Duration = (FDateTime::Now() - RequestStartTime).GetTotalSeconds();
    LogEntry.RequestData = Data;
    LogEntry.ResponseData = Response.FullTextFromServer;
    LogEntry.RequestHeaders = DelimitedRequestHeaders;
    LogEntry.ResponseHeaders = FString::Join(ResponseHeaders, TEXT("\n"));
    LogEntry.bSuccess = false;
    LogEntry.Timestamp = FDateTime::Now();
    LogEntry.ErrorData = Response.ErrorData;
    FLootLockerServerLogger::LogHttpRequest(LogEntry);
}

void ULootLockerServerHttpClient::LogSuccessfulRequestInformation(const FLootLockerServerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const FString& DelimitedRequestHeaders, const TArray<FString>& ResponseHeaders, const FDateTime& RequestStartTime)
{
    FLootLockerServerHttpLogEntry LogEntry;
    LogEntry.Method = RequestMethod;
    LogEntry.Path = Endpoint;
    LogEntry.StatusCode = Response.StatusCode;
    LogEntry.Duration = (FDateTime::Now() - RequestStartTime).GetTotalSeconds();;
    LogEntry.RequestData = Data;
    LogEntry.ResponseData = Response.FullTextFromServer;
    LogEntry.RequestHeaders = DelimitedRequestHeaders;
    LogEntry.ResponseHeaders = FString::Join(ResponseHeaders, TEXT("\n"));
    LogEntry.bSuccess = true;
    LogEntry.Timestamp = FDateTime::Now();
    LogEntry.ErrorData = Response.ErrorData;
    FLootLockerServerLogger::LogHttpRequest(LogEntry);
}
