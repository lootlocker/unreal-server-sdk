// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPurchaseRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerPurchaseRequest::ULootLockerServerPurchaseRequest()
{
}

const TMultiMap<FString, FString> ULootLockerServerPurchaseRequest::IncludeProductsQueryParams = {{"no_products", "true"}};

void ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByID(int PlayerID, int PurchaseID, const FLootLockerServerPurchaseStatusResponseBP& OnCompletedRequestBP, const FLootLockerServerPurchaseStatusResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPurchaseStatusResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::CheckPurchaseStatus, { PlayerID, PurchaseID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByPlatformTransactionID(int PlayerID, int PlatformTransactionID, const FLootLockerServerPurchaseStatusResponseBP& OnCompletedRequestBP, const FLootLockerServerPurchaseStatusResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPurchaseStatusResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::CheckPurchaseStatus, { PlayerID, PlatformTransactionID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByIDWith_IncludeProducts(int PlayerID, int PurchaseID, const FLootLockerServerPurchaseStatusWithProductsResponseBP& OnCompletedRequestBP, const FLootLockerServerPurchaseStatusWithProductsResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPurchaseStatusWithProductsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::CheckPurchaseStatus, { PlayerID, PurchaseID }, IncludeProductsQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerPurchaseRequest::CheckPurchaseStatusForPlayerByPlatformTransactionID_IncludeProducts(int PlayerID, int PlatformTransactionID, const FLootLockerServerPurchaseStatusWithProductsResponseBP& OnCompletedRequestBP, const FLootLockerServerPurchaseStatusWithProductsResponseDelegate& OnCompletedRequest) 
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerPurchaseStatusWithProductsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::CheckPurchaseStatus, { PlayerID, PlatformTransactionID }, IncludeProductsQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

