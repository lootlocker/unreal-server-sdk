// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerEndpoints.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerStateData.h"
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

private:
    struct HTTPRequest
    {
        FString EndPoint;
        FString RequestType;
        FString Data;
        FLootLockerServerResponseCallback OnCompleteRequest;
        TMap<FString, FString> CustomHeaders;
    };
    static ULootLockerServerHttpClient* Instance;
    static bool ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful, FString RequestMethod, FString Endpoint, FString Data);
    void SendRequest_Internal(HTTPRequest InRequest) const;
    void UploadFile_Internal(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>
        AdditionalFields, const FLootLockerServerResponseCallback& onCompleteRequest, TMap<FString, FString> customHeaders =
        TMap<FString, FString>()) const;

    template<typename ResponseType>
    struct TemplatedHTTPRequest
    {
        template<typename BluePrintDelegate, typename CppDelegate>
        static FLootLockerServerResponseCallback CreateLambda(const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback)
        {
            FLootLockerServerResponseCallback ResponseHandler = FLootLockerServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback](FLootLockerServerResponse response)
                {
                    ResponseType ResponseStruct;

                    if (!response.FullTextFromServer.IsEmpty())
                    {
                        FJsonObjectConverter::JsonObjectStringToUStruct<ResponseType>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                    }
                    if (response.ServerCallStatusCode == 200 || response.ServerCallStatusCode == 204)
                    {
                        ResponseStruct.Success = true;
                        if (ResponseStruct.Token.IsEmpty())
                        {
                            ResponseStruct.Token = ULootLockerServerStateData::GetServerToken();
                        }
                        else {
                            ULootLockerServerStateData::SetServerToken(ResponseStruct.Token);
                        }
                    }
                    else
                    {
                        ResponseStruct.Success = false;
                        ResponseStruct.Error = response.Error;
                    }
                    ResponseStruct.FullTextFromServer = response.FullTextFromServer;
                    ResponseInspectorCallback.ExecuteIfBound(ResponseStruct);
                    OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
                    OnCompletedRequest.ExecuteIfBound(ResponseStruct);
                });
            return ResponseHandler;
        }

        template<typename RequestType, typename BluePrintDelegate, typename CppDelegate>
        static HTTPRequest Make(RequestType RequestStruct, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const typename ResponseInspector<ResponseType>::FLootLockerServerResponseInspectorCallback& ResponseInspectorCallback = ResponseInspector<ResponseType>::FServerResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
        {
            FString ContentString;
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

            // calculate endpoint
            const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();
            FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, FStringFormatNamedArguments{ {"domainKey", Config && !Config->LootLockerDomainKey.IsEmpty() ? Config->LootLockerDomainKey + "." : ""} });
            EndpointWithArguments = FString::Format(*EndpointWithArguments, InOrderedArguments);

            const FString optionalToken = ULootLockerServerStateData::GetServerToken();
            if (!optionalToken.IsEmpty()) {
                CustomHeaders.Add(TEXT("x-auth-token"), optionalToken);
            }

            EndpointWithArguments = LootLockerServerUtilities::AppendParametersToUrl(EndpointWithArguments, QueryParams);

            // create callback lambda
            const FLootLockerServerResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

            // send request
            return HTTPRequest{ EndpointWithArguments, Endpoint.GetRequestMethodString(), ContentString, SessionResponse, CustomHeaders };
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



