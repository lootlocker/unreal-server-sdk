// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerHeroRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerHeroRequest::ULootLockerServerHeroRequest()
{
}

void ULootLockerServerHeroRequest::GetPlayerHeroes(int PlayerID, const FLootLockerServerGetPlayerHeroResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerHeroesResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerHeroes, { PlayerID }, {}, FLootLockerServerGetPlayerHeroResponseBP(), OnCompletedRequest);
}

void ULootLockerServerHeroRequest::GetPlayerHeroInventory(int PlayerID, int HeroID, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroInventory, { PlayerID, HeroID }, {}, FLootLockerServerGetHeroInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerHeroRequest::GetPaginatedPlayerHeroInventory(int PlayerID, int HeroID, int Count, int After, const FLootLockerServerGetHeroInventoryResponseDelegate& OnCompletedRequest)
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroInventory, { PlayerID, HeroID }, QueryParams, FLootLockerServerGetHeroInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerHeroRequest::GetPlayerHeroLoadout(int PlayerID, int HeroID, const FLootLockerServerGetHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetHeroLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetHeroLoadout, { PlayerID, HeroID }, {}, FLootLockerServerGetHeroLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetInstanceId(int PlayerID, int HeroID, int AssetInstanceID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutRequest{AssetInstanceID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, FLootLockerServerEquipAssetToHeroLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndAssetVariationId(int PlayerID, int HeroID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndVariationIdRequest{AssetID, AssetVariationID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, FLootLockerServerEquipAssetToHeroLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerHeroRequest::EquipAssetToPlayerHeroLoadoutByAssetIdAndRentalOptionId(int PlayerID, int HeroID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToHeroLoadoutResponse>(FLootLockerServerEquipAssetToHeroLoadoutByAssetIdAndRentalOptionIdRequest{AssetID, RentalOptionID}, ULootLockerServerEndpoints::EquipAssetToHeroLoadout, { PlayerID, HeroID }, {}, FLootLockerServerEquipAssetToHeroLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerHeroRequest::UnequipAssetFromPlayerHeroLoadout(int PlayerID, int HeroID, int InstanceID, const FLootLockerServerUnequipAssetFromHeroLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerUnequipAssetFromHeroLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::UnequipAssetFromHeroLoadout, { PlayerID, HeroID, InstanceID}, {}, FLootLockerServerUnequipAssetFromHeroLoadoutResponseBP(), OnCompletedRequest);
}
