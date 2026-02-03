// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerHeroRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerHeroRequest::ULootLockerServerHeroRequest()
{
}

FString ULootLockerServerHeroRequest::GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerHeroesResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerHeroes, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerHeroRequest::GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroInventory, { PlayerID, HeroID }, {}, OnCompletedRequest);
}

FString ULootLockerServerHeroRequest::GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroInventory, { PlayerID, HeroID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerHeroRequest::GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequest);
}

FString ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutRequest{AssetInstanceID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequest);
}

FString ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndVariationIdRequest{AssetID, AssetVariationID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequest);
}

FString ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndRentalOptionIdRequest{AssetID, RentalOptionID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, OnCompletedRequest);
}

FString ULootLockerServerHeroRequest::UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerUnequipAssetFromHeroLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::UnequipAssetFromHeroLoadout, { PlayerID, HeroID, InstanceID}, {}, OnCompletedRequest);
}
