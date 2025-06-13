// Copyright (c) 2021 LootLocker

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"
#include "HttpModule.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerEndpoints.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerStateData.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Utils/LootLockerServerUtilities.h"

#include "LootLockerServerHttpClient.generated.h"

UCLASS()
class LOOTLOCKERSERVERSDK_API ULootLockerServerHttpClient : public UObject
{
	GENERATED_BODY()
public:
    static ULootLockerServerHttpClient& GetInstance();
    template<typename ResponseType>
    struct ResponseInspector
    {
        DECLARE_DELEGATE_OneParam(FLootLockerServerResponseInspectorCallback, ResponseType&);
    };
    template<typename ResponseType, typename RequestType, typename BlueprintDelegate, typename CppDelegate>
    static void SendRequest(RequestType Request, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BlueprintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback(), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
	{
    	GetInstance().SendRequest_Internal(TemplatedHTTPRequest<ResponseType>::Make(Request, Endpoint, InOrderedArguments, QueryParams, OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback, CustomHeaders));
	}

    template<typename ResponseType, typename BlueprintDelegate, typename CppDelegate>
    static void SendRawRequest(FString RequestBody, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BlueprintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback(), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        GetInstance().SendRequest_Internal(TemplatedHTTPRequest<ResponseType>::MakeRaw(RequestBody, Endpoint, InOrderedArguments, QueryParams, OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback, CustomHeaders));
    }

    template<typename ResponseType, typename BlueprintDelegate, typename CppDelegate>
    static void SendRawWWWFormUrlEncodedRequest(FString RequestBody, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BlueprintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback(), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        GetInstance().SendRequest_Internal(TemplatedHTTPRequest<ResponseType>::MakeRaw(RequestBody, Endpoint, InOrderedArguments, QueryParams, OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback, CustomHeaders, "application/x-www-form-urlencoded"));
    }

    template<typename ResponseType, typename BlueprintDelegate, typename CppDelegate>
    static void UploadFile(const FString& FilePath, const TMap<FString, FString> AdditionalFields, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BlueprintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback(), TMap<FString, FString> CustomHeaders = TMap<FString, FString>()) 
    {
        GetInstance().UploadFile_Internal(FilePath, AdditionalFields, TemplatedHTTPRequest<ResponseType>::Make(FLootLockerServerEmptyRequest{}, Endpoint, InOrderedArguments, QueryParams, OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback, CustomHeaders));
    }

    template<typename ResponseType, typename BlueprintDelegate, typename CppDelegate>
    static void UploadRawFile(const TArray<uint8>& RawData, const FString& FileName, const TMap<FString, FString> AdditionalFields, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BlueprintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback(), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        GetInstance().UploadRawFile_Internal(RawData, FileName, AdditionalFields, TemplatedHTTPRequest<ResponseType>::Make(FLootLockerServerEmptyRequest{}, Endpoint, InOrderedArguments, QueryParams, OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback, CustomHeaders));
    }

private:
    ULootLockerServerHttpClient();
    const FString UserAgent;
    const FString UserInstanceIdentifier;
    FString SDKVersion;
    struct HTTPRequest
    {
        FString EndPoint = "";
        FString RequestType = "";
        FString ContentType = "";
        FString Data = "";
        FLootLockerServerResponseCallback OnCompleteRequest;
        TMap<FString, FString> CustomHeaders;

        FString ToString() {
            FString StringRepresentation = FString::Format(TEXT("{0} to {1}, with data {2}"), {RequestType, EndPoint, Data});
            for (auto& header : CustomHeaders) {
                StringRepresentation.Append(FString::Format(TEXT("\n  {0} : {1}"), {header.Key, header.Value}));
            }
            return StringRepresentation;
        };
    };
    static ULootLockerServerHttpClient* Instance;
    static bool ResponseIsSuccess(const FHttpResponsePtr& InResponse, bool bWasSuccessful);
    static void LogFailedRequestInformation(const FLootLockerServerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const FString& DelimitedRequestHeaders, const TArray<FString>& ResponseHeaders, const FDateTime& RequestStartTime);
	static void LogSuccessfulRequestInformation(const FLootLockerServerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const FString& DelimitedRequestHeaders, const TArray<FString>& ResponseHeaders, const FDateTime& RequestStartTime);
	void SendRequest_Internal(HTTPRequest InRequest) const;
    void UploadFile_Internal(const FString& FilePath, const TMap<FString, FString> AdditionalFields, HTTPRequest InRequest) const;
    void UploadRawFile_Internal(const TArray<uint8>& RawData, const FString& FileName, const TMap<FString, FString> AdditionalFields, HTTPRequest InRequest) const;

    template<typename ResponseType>
    struct TemplatedHTTPRequest
    {
        template<typename BluePrintDelegate, typename CppDelegate>
        static FLootLockerServerResponseCallback CreateLambda(const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback)
        {
            return FLootLockerServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback](FLootLockerServerResponse response)
            {
                ResponseType ResponseStruct;

                if (!response.FullTextFromServer.IsEmpty())
                {
                    FJsonObjectConverter::JsonObjectStringToUStruct<ResponseType>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                }

                ResponseStruct.Success = response.Success;
                ResponseStruct.StatusCode = response.StatusCode;
                if(!ResponseStruct.Success)
                {
                    ResponseStruct.ErrorData = response.ErrorData;
                }
                ResponseStruct.FullTextFromServer = response.FullTextFromServer;
                ResponseInspectorCallback.ExecuteIfBound(ResponseStruct);
                OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
                OnCompletedRequest.ExecuteIfBound(ResponseStruct);
            });
        }

        template<typename BluePrintDelegate, typename CppDelegate>
        static HTTPRequest MakeRaw(FString ContentString, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = ResponseInspector<ResponseType>::FServerResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>(), const FString& ContentType = "")
        {
            // Calculate endpoint
            const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
            FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, FStringFormatNamedArguments{ {"domainKey", Config && !Config->LootLockerDomainKey.IsEmpty() ? Config->LootLockerDomainKey + "." : ""} });
            TArray<FStringFormatArg> UrlEncodedPathParams;
            for (const FStringFormatArg& InOrderedArgument : InOrderedArguments)
            {
	            switch (InOrderedArgument.Type)
	            {
	            case FStringFormatArg::Int:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString::FromInt(InOrderedArgument.IntValue)));
		            break;
	            case FStringFormatArg::UInt:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString::FromInt(InOrderedArgument.UIntValue)));
		            break;
	            case FStringFormatArg::Double:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString::SanitizeFloat(InOrderedArgument.DoubleValue)));
		            break;
	            case FStringFormatArg::String:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(InOrderedArgument.StringValue));
                    break;
#if ENGINE_MAJOR_VERSION >= 5
	            case FStringFormatArg::StringLiteralANSI:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString(InOrderedArgument.StringLiteralANSIValue)));
		            break;
	            case FStringFormatArg::StringLiteralWIDE:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString(InOrderedArgument.StringLiteralWIDEValue)));
		            break;
	            case FStringFormatArg::StringLiteralUCS2:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString(InOrderedArgument.StringLiteralUCS2Value)));
		            break;
	            case FStringFormatArg::StringLiteralUTF8:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString(InOrderedArgument.StringLiteralUTF8Value)));
		            break;
#else
	            case FStringFormatArg::StringLiteral:
                    UrlEncodedPathParams.Add(FGenericPlatformHttp::UrlEncode(FString(InOrderedArgument.StringLiteralValue)));
                    break;
#endif
	            }
            }
            EndpointWithArguments = FString::Format(*EndpointWithArguments, UrlEncodedPathParams);

            const FString optionalToken = ULootLockerServerStateData::GetServerToken();
            if (!optionalToken.IsEmpty()) {
                CustomHeaders.Add(TEXT("x-auth-token"), optionalToken);
            }

            EndpointWithArguments = LootLockerServerUtilities::AppendParametersToUrl(EndpointWithArguments, QueryParams);

            // create callback lambda
            const FLootLockerServerResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

            // send request
            return HTTPRequest{ EndpointWithArguments, Endpoint.GetRequestMethodString(), ContentType.IsEmpty() ? "application/json" : ContentType,ContentString, SessionResponse, CustomHeaders };
        }

        template<typename RequestType, typename BluePrintDelegate, typename CppDelegate>
        static HTTPRequest Make(RequestType RequestStruct, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = ResponseInspector<ResponseType>::FServerResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>(), const FString& ContentType = "")
        {
            FString ContentString = "";
#if ENGINE_MAJOR_VERSION < 5
            FJsonObjectConverter::UStructToJsonObjectString(RequestType::StaticStruct(), &RequestStruct, ContentString, 0, 0);
            if (IsEmptyJsonString(ContentString))
            {
                ContentString = FString();
            }
#else
            if (!std::is_same_v<RequestType, FLootLockerServerEmptyRequest>)
            {
                FJsonObjectConverter::UStructToJsonObjectString(RequestType::StaticStruct(), &RequestStruct, ContentString, 0, 0);
            }
#endif
            return MakeRaw(ContentString, Endpoint, InOrderedArguments, QueryParams, OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback, CustomHeaders, ContentType);
        }

    private:
        static bool IsEmptyJsonString(const FString& JsonString)
        {
            return JsonString.Equals(FString("{}")) ||
                JsonString.Equals(FString("{\r\n}")) ||
                JsonString.Equals(FString("{\n}")) ||
                JsonString.Equals(FString("{ }"));
        }
    };    
};



