// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerHeroRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerHeroRequest::ULootLockerServerHeroRequest()
{
}

void ULootLockerServerHeroRequest::GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseBP& OnCompletedRequestBP, const FLootLockerServerGetPlayerHeroResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerHeroesResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerHeroes, { PlayerID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerHeroRequest::GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequestBP, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroInventory, { PlayerID, HeroID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerHeroRequest::GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseBP& OnCompletedRequestBP, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(Count > 0)
    {
        QueryParams.Add("count", FString::FromInt(Count));
    }
    if (After > 0)
    {
        QueryParams.Add("after", FString::FromInt(After));
    }
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroInventory, { PlayerID, HeroID }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerHeroRequest::GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerServerGetHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutRequest{AssetInstanceID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndVariationIdRequest{AssetID, AssetVariationID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndRentalOptionIdRequest{AssetID, RentalOptionID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerServerHeroRequest::UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerUnequipAssetFromHeroLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::UnequipAssetFromHeroLoadout, { PlayerID, HeroID, InstanceID}, {}, OnCompletedRequestBP, OnCompletedRequest);
}
