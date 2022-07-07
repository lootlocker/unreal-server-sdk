// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerAPI/LootLockerServerAssetRequest.h"

#include "JsonObjectConverter.h"
#include "LootLockerServerGameEndpoints.h"
#include "LootLockerServerSDK/Private/Utils/LootLockerServerUtilities.h"

ULootLockerServerHttpClient* ULootLockerServerAssetRequest::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerAssetRequest::ULootLockerServerAssetRequest()
{
    HttpClient = NewObject<ULootLockerServerHttpClient>();
}

void ULootLockerServerAssetRequest::GetAssetsToGame(int StartFromIndex, int ItemsCount, ELootLockerServerAssetFilter AssetFilter, bool IncludeUGC, const FServerAssetsResponseDelegateBP& OnCompletedRequestBP, const FServerAssetsResponseDelegate& OnCompletedRequest)
{
    FServerResponseCallback sessionResponse = FServerResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerServerResponse response)
        {
            FLootLockerServerGetAssetsToGameResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerServerGetAssetsToGameResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogLootLockerServer, Error, TEXT("GetAssets failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerServerEndPoints Endpoint = ULootLockerServerGameEndpoints::GetAssetsToGameEndpoint;
    FString requestMethod = ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString EndpointUrl = Endpoint.endpoint;
    if (StartFromIndex != 0)
    {
        EndpointUrl = LootLockerServerUtilities::AppendParameterToUrl(EndpointUrl, "after=" + FString::FromInt(StartFromIndex));
    }
    if (ItemsCount != 50)
    {
        EndpointUrl = LootLockerServerUtilities::AppendParameterToUrl(EndpointUrl, "count=" + FString::FromInt(ItemsCount));
    }
    FString Filter = "";
    switch (AssetFilter)
    {
        case ELootLockerServerAssetFilter::Purchasable:
            Filter = "purchasable";
            break;
        case ELootLockerServerAssetFilter::NonPurchasable:
            Filter = "!purchasable";
            break;
        case ELootLockerServerAssetFilter::Rentable:
            Filter = "rentable";
            break;
        case ELootLockerServerAssetFilter::NonRentable:
            Filter = "!rentable";
            break;
        case ELootLockerServerAssetFilter::Popular:
            Filter = "popular";
            break;
        case ELootLockerServerAssetFilter::UnPopular:
            Filter = "!popular";
            break;
    }
    if (!Filter.IsEmpty())
    {
        EndpointUrl = LootLockerServerUtilities::AppendParameterToUrl(EndpointUrl, "filter=" + Filter);
    }
    
    if (IncludeUGC)
    {
        EndpointUrl = LootLockerServerUtilities::AppendParameterToUrl(EndpointUrl, "include_ugc=true");
    }
    HttpClient->SendApi(EndpointUrl, requestMethod, ContentString, sessionResponse, true);
}

