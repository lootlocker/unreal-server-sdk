// Copyright (c) 2021 LootLocker

#pragma once

#include "JsonObjectConverter.h"
#include "LootLockerServerConfig.h"
#include "LootLockerServerEndpoints.h"
#include "LootLockerServerResponse.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerStateData.h"

namespace LootLockerServerUtilities
{
    FString AppendParametersToUrl(FString Url, const TMultiMap<FString, FString>& QueryParams);

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString);
}

template<typename ResponseType>
struct LootLockerServerAPIUtilities
{
    DECLARE_DELEGATE_OneParam(FServerResponseInspectorCallback, ResponseType&);

    template<typename BluePrintDelegate, typename CppDelegate>
    static FLootLockerServerResponseCallback CreateLambda(const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FServerResponseInspectorCallback& ResponseInspectorCallback)
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
                if (ResponseStruct.Token != "")
                {
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
    static void CallAPI(ULootLockerServerHttpClient* HttpClient, RequestType RequestStruct, FLootLockerServerEndPoint Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FServerResponseInspectorCallback& ResponseInspectorCallback = LootLockerServerAPIUtilities<ResponseType>::FServerResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
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

#if WITH_EDITOR
        UE_LOG(LogLootLockerServerSDK, Log, TEXT("Request:"));
        UE_LOG(LogLootLockerServerSDK, Log, TEXT("ContentString:%s"), *ContentString);
        UE_LOG(LogLootLockerServerSDK, Log, TEXT("EndpointWithArguments:%s"), *EndpointWithArguments);
#endif //WITH_EDITOR

        // create callback lambda
        const FLootLockerServerResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

        // send request
        HttpClient->SendApi(EndpointWithArguments, Endpoint.GetRequestMethodString(), ContentString, SessionResponse, CustomHeaders);
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