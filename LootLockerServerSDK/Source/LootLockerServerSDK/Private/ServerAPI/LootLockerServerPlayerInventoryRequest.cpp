// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerInventoryRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerPlayerInventoryRequest::ULootLockerServerPlayerInventoryRequest()
{
}

FString ULootLockerServerPlayerInventoryRequest::GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetUniversalInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetUniversalInventory, {}, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerInventory, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest)
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerInventory, { PlayerID }, QueryParams, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerLoadout, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetIdRequest{ AssetID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetInstanceIdRequest{ AssetInstanceID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetIdAndVariationIdRequest{ AssetID, AssetVariationID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest{ AssetID, RentalOptionID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerUnequipAssetFromPlayerLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::UnEquipAssetFromPlayerLoadout, { PlayerID, InstanceID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAddAssetToPlayerInventoryResponse>(FLootLockerServerAssetByAssetIdRequest{ AssetID }, ULootLockerServerEndpoints::AddAssetToPlayerInventory, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAddAssetToPlayerInventoryResponse>(FLootLockerServerAssetByAssetIdAndVariationIdRequest{ AssetID, VariationID }, ULootLockerServerEndpoints::AddAssetToPlayerInventory, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAddAssetToPlayerInventoryResponse>(FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest{ AssetID, RentalOptionID }, ULootLockerServerEndpoints::AddAssetToPlayerInventory, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAlterPlayerInventoryResponse>(
        FLootLockerServerAlterPlayerInventoryByAssetIdRequest{ AssetsToRemove, AssetsToAdd },
        ULootLockerServerEndpoints::AlterPlayerInventory,
        { PlayerID },
        {},
        OnCompletedRequest
    );
}

FString ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAlterPlayerInventoryResponse>(
        FLootLockerServerAlterPlayerInventoryByAssetIdAndAssetVariationIdRequest{ AssetsToRemove, AssetsToAdd },
        ULootLockerServerEndpoints::AlterPlayerInventory,
        { PlayerID },
        {},
        OnCompletedRequest
    );
}

FString ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerAlterPlayerInventoryResponse>(
        FLootLockerServerAlterPlayerInventoryByAssetIdAndRentalOptionIdRequest{ AssetsToRemove, AssetsToAdd },
        ULootLockerServerEndpoints::AlterPlayerInventory,
        { PlayerID },
        {},
        OnCompletedRequest
    );
}

