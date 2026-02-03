// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCharacterRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerCharacterRequest::ULootLockerServerCharacterRequest()
{
}

void ULootLockerServerCharacterRequest::GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerCharactersResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerCharacters, { PlayerID }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterRequest::GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetCharacterInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetCharacterInventory, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterRequest::GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetCharacterInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetCharacterInventory, { PlayerID, CharacterID }, QueryParams, OnCompletedRequest);
}

void ULootLockerServerCharacterRequest::GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetCharacterLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToCharacterLoadoutResponse>(FLootLockerServerEquipAssetToCharacterLoadoutRequest{AssetInstanceID}, ULootLockerServerEndpoints::EquipAssetToCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToCharacterLoadoutResponse>(FLootLockerServerEquipAssetToCharacterLoadoutByAssetIdAndVariationIdRequest{AssetID, AssetVariationID}, ULootLockerServerEndpoints::EquipAssetToCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToCharacterLoadoutResponse>(FLootLockerServerEquipAssetToCharacterLoadoutByAssetIdAndRentalOptionIdRequest{AssetID, RentalOptionID}, ULootLockerServerEndpoints::EquipAssetToCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

void ULootLockerServerCharacterRequest::UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerUnequipAssetFromCharacterLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::UnequipAssetFromCharacterLoadout, { PlayerID, CharacterID, InstanceID}, {}, OnCompletedRequest);
}
