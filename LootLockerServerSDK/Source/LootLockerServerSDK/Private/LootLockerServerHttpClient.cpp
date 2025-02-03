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
			ULootLockerServerLogger::Log(ELootLockerServerLogLevel::Verbose, FString::Format(TEXT("LootLockerServer version: v{0}"), { SDKVersion }));
		}
	}
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

	Request->SetHeader(TEXT("User-Agent"), UserAgent);
	Request->SetHeader(TEXT("User-Instance-Identifier"), UserInstanceIdentifier);
	Request->SetHeader(TEXT("SDK-Version"), SDKVersion);
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

	FString DelimitedHeaders = "";
	TArray<FString> AllHeaders = Request->GetAllHeaders();
	for (auto Header : AllHeaders)
	{
        DelimitedHeaders += TEXT("    ") + Header + TEXT("\n");
	}
	ULootLockerServerLogger::Log(ELootLockerServerLogLevel::Verbose, FString::Format(TEXT("Request {0} to endpoint {1}\n  With headers {2}\n  And with content: {3}"), { Request->GetVerb(), *Request->GetURL(), *DelimitedHeaders, *InRequest.Data }));

	Request->OnProcessRequestComplete().BindLambda([InRequest](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (!Response.IsValid())
		{
			FLootLockerServerResponse Error = LootLockerServerResponseFactory::Error<FLootLockerServerResponse>("HTTP Response was invalid");
			LogFailedRequestInformation(Error, InRequest.RequestType, InRequest.EndPoint, InRequest.Data, TArray<FString>());
			InRequest.OnCompleteRequest.ExecuteIfBound(Error);
			return;
		}
		FLootLockerServerResponse response;
		response.Success = ResponseIsSuccess(Response, bWasSuccessful);
		response.ServerCallStatusCode = response.StatusCode = Response->GetResponseCode();
		response.FullTextFromServer = Response->GetContentAsString();
		if (!response.Success)
		{
			FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerErrorData>(
				response.FullTextFromServer, &response.ErrorData, 0, 0);
			if (response.ErrorData.Code.IsEmpty())
			{
				response.Error = response.ErrorData.Message = response.FullTextFromServer;
			}
			else
			{
				response.Error = response.ErrorData.Message;
			}
			FString RetryAfterHeader = Response->GetHeader("retry-after");
			if (!RetryAfterHeader.IsEmpty())
			{
				response.ErrorData.Retry_after_seconds = FCString::Atoi(*RetryAfterHeader);
			}
			LogFailedRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, InRequest.Data, Response->GetAllHeaders());
		}
#if WITH_EDITOR
		else
		{
			LogSuccessfulRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, InRequest.Data, Response->GetAllHeaders());
		}
#endif
		InRequest.OnCompleteRequest.ExecuteIfBound(response);
	});
	Request->ProcessRequest();
}

void ULootLockerServerHttpClient::UploadFile_Internal(const FString& FilePath, const TMap<FString, FString> AdditionalFields, HTTPRequest InRequest) const
{
	TArray<uint8> RawData;
	if (!FFileHelper::LoadFileToArray(RawData, *FilePath)) {
		InRequest.OnCompleteRequest.ExecuteIfBound(LootLockerServerResponseFactory::Error<FLootLockerServerResponse>(FString::Format(TEXT("Could not read file {0}"), { FilePath })));
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

	FString DelimitedHeaders = "";
	TArray<FString> AllHeaders = Request->GetAllHeaders();
	for (auto Header : AllHeaders)
	{
        DelimitedHeaders += TEXT("    ") + Header + TEXT("\n");
	}

	ULootLockerServerLogger::Log(ELootLockerServerLogLevel::Verbose, FString::Format(TEXT("Request {0} to endpoint {1}\n  With headers {2}\n  And with content: {3}"), { Request->GetVerb(), Request->GetURL(), DelimitedHeaders, FString("File Content") }));

	Request->OnProcessRequestComplete().BindLambda([this, InRequest](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (!Response.IsValid())
		{
			FLootLockerServerResponse Error = LootLockerServerResponseFactory::Error<FLootLockerServerResponse>("HTTP Response was invalid");
			LogFailedRequestInformation(Error, InRequest.RequestType, InRequest.EndPoint, FString("Data Stream"), TArray<FString>());
			InRequest.OnCompleteRequest.ExecuteIfBound(Error);
			return;
		}
		FLootLockerServerResponse response;
		response.Success = ResponseIsSuccess(Response, bWasSuccessful);
		response.ServerCallStatusCode = response.StatusCode = Response->GetResponseCode();
		response.FullTextFromServer = Response->GetContentAsString();
		if (!response.Success)
		{
			FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerErrorData>(
				response.FullTextFromServer, &response.ErrorData, 0, 0);
			if (response.ErrorData.Code.IsEmpty())
			{
				response.Error = response.ErrorData.Message = response.FullTextFromServer;
			}
			else
			{
				response.Error = response.ErrorData.Message;
			}
			FString RetryAfterHeader = Response->GetHeader("retry-after");
			if (!RetryAfterHeader.IsEmpty())
			{
				response.ErrorData.Retry_after_seconds = FCString::Atoi(*RetryAfterHeader);
			}
			LogFailedRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, FString("Data Stream"), Response->GetAllHeaders());
		}
#if WITH_EDITOR
		else 
		{
			LogSuccessfulRequestInformation(response, InRequest.RequestType, InRequest.EndPoint, FString("Data Stream"), Response->GetAllHeaders());
		}
#endif

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

void ULootLockerServerHttpClient::LogFailedRequestInformation(const FLootLockerServerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const TArray<FString>& ResponseHeaders)
{
	FString LogString = FString::Format(TEXT("{0} request to {1} failed"), { RequestMethod, Endpoint });
	const bool IsInformativeError = !Response.ErrorData.Code.IsEmpty();
	if (IsInformativeError)
	{
		LogString += FString::Format(TEXT("\n   {0}"), { Response.ErrorData.Message });
		LogString += FString::Format(TEXT("\n    Error Code: {0}"), { Response.ErrorData.Code });
		LogString += FString::Format(TEXT("\n    Further Information: {0}"), { Response.ErrorData.Doc_url });
		LogString += FString::Format(TEXT("\n    Request ID: {0}"), { Response.ErrorData.Request_id });
		LogString += FString::Format(TEXT("\n    Trace ID: {0}"), { Response.ErrorData.Trace_id });
	}
	LogString += FString::Format(TEXT("\n   HTTP Status code : {0}"), { Response.StatusCode });
	if (!Data.IsEmpty()) {
		LogString += FString::Format(TEXT("\n   Request Data: {0}"), { Data });
	}
#if WITH_EDITOR
	if(ResponseHeaders.Num() > 0)
	{
		LogString += FString::Format(TEXT("\n   -- Response Headers --"), { Data });
		for (FString ResponseHeader : ResponseHeaders)
		{
			LogString += FString::Format(TEXT("\n     {0}"), { ResponseHeader });
		}
	}
#endif

	if (!IsInformativeError)
	{
		LogString += FString::Format(TEXT("\n   Response Data: {0}"), { Response.FullTextFromServer });
	}
	LogString += "\n###";
	ULootLockerServerLogger::Log(ELootLockerServerLogLevel::Warning, LogString);
}

void ULootLockerServerHttpClient::LogSuccessfulRequestInformation(const FLootLockerServerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const TArray<FString>& ResponseHeaders)
{
	FString LogString = FString::Format(TEXT("{0} request to {1} succeeded"), { RequestMethod, Endpoint });
	LogString += FString::Format(TEXT("\n   HTTP Status code : {0}"), { Response.StatusCode });
	if (!Data.IsEmpty()) {
		LogString += FString::Format(TEXT("\n   Request Data: {0}"), { Data });
	}
#if WITH_EDITOR
	if (ResponseHeaders.Num() > 0)
	{
		LogString += FString::Format(TEXT("\n   -- Response Headers --"), { Data });
		for (FString ResponseHeader : ResponseHeaders)
		{
			LogString += FString::Format(TEXT("\n     {0}"), { ResponseHeader });
		}
	}
#endif
	LogString += FString::Format(TEXT("\n   Response Data: {0}"), { Response.FullTextFromServer });
	LogString += "\n###";
	ULootLockerServerLogger::Log(ELootLockerServerLogLevel::VeryVerbose, LogString);
}
