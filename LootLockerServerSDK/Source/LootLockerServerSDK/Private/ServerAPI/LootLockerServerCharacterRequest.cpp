// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCharacterRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerCharacterRequest::ULootLockerServerCharacterRequest()
{
}

FString ULootLockerServerCharacterRequest::GetPlayerCharacters(int PlayerID, const FLootLockerServerGetPlayerCharacterResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerCharactersResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerCharacters, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterRequest::GetPlayerCharacterInventory(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetCharacterInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetCharacterInventory, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterRequest::GetPaginatedPlayerCharacterInventory(int PlayerID, int CharacterID, int Count, int After, const FLootLockerServerGetCharacterInventoryResponseDelegate& OnCompletedRequest)
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetCharacterInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetCharacterInventory, { PlayerID, CharacterID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerCharacterRequest::GetPlayerCharacterLoadout(int PlayerID, int CharacterID, const FLootLockerServerGetCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetCharacterLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetInstanceId(int PlayerID, int CharacterID, int AssetInstanceID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToCharacterLoadoutResponse>(FLootLockerServerEquipAssetToCharacterLoadoutRequest{AssetInstanceID}, ULootLockerServerEndpoints::EquipAssetToCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndAssetVariationId(int PlayerID, int CharacterID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToCharacterLoadoutResponse>(FLootLockerServerEquipAssetToCharacterLoadoutByAssetIdAndVariationIdRequest{AssetID, AssetVariationID}, ULootLockerServerEndpoints::EquipAssetToCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterRequest::EquipAssetToPlayerCharacterLoadoutByAssetIdAndRentalOptionId(int PlayerID, int CharacterID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToCharacterLoadoutResponse>(FLootLockerServerEquipAssetToCharacterLoadoutByAssetIdAndRentalOptionIdRequest{AssetID, RentalOptionID}, ULootLockerServerEndpoints::EquipAssetToCharacterLoadout, { PlayerID, CharacterID }, {}, OnCompletedRequest);
}

FString ULootLockerServerCharacterRequest::UnequipAssetFromPlayerCharacterLoadout(int PlayerID, int CharacterID, int InstanceID, const FLootLockerServerUnequipAssetFromCharacterLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerUnequipAssetFromCharacterLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::UnequipAssetFromCharacterLoadout, { PlayerID, CharacterID, InstanceID}, {}, OnCompletedRequest);
}
