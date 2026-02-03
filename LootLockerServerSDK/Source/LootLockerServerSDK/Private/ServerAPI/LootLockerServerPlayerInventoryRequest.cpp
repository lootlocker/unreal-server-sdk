// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPlayerInventoryRequest.h"

#include "LootLockerServerHttpClient.h"

ULootLockerServerPlayerInventoryRequest::ULootLockerServerPlayerInventoryRequest()
{
}

void ULootLockerServerPlayerInventoryRequest::GetUniversalInventory(const FLootLockerServerGetUniversalInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetUniversalInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetUniversalInventory, {}, {}, FLootLockerServerGetUniversalInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::GetPlayerInventory(int PlayerID, const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerInventory, { PlayerID }, {}, FLootLockerServerGetPlayerInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::GetPaginatedPlayerInventory(int PlayerID, int Count, int After, const FLootLockerServerGetPlayerInventoryResponseDelegate& OnCompletedRequest)
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
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerInventoryResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerInventory, { PlayerID }, QueryParams, FLootLockerServerGetPlayerInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::GetPlayerLoadout(int PlayerID, const FLootLockerServerGetPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerLoadout, { PlayerID }, {}, FLootLockerServerGetPlayerLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetId(int PlayerID, int AssetID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetIdRequest{ AssetID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetInstanceId(int PlayerID, int AssetInstanceID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetInstanceIdRequest{ AssetInstanceID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndAssetVariationId(int PlayerID, int AssetID, int AssetVariationID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetIdAndVariationIdRequest{ AssetID, AssetVariationID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::EquipAssetToPlayerLoadoutByAssetIdAndRentalOptionId(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerEquipAssetToPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerEquipAssetToPlayerLoadoutResponse>(FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest{ AssetID, RentalOptionID }, ULootLockerServerEndpoints::EquipAssetToPlayerLoadout, { PlayerID }, {}, FLootLockerServerEquipAssetToPlayerLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::UnequipAssetFromPlayerLoadout(int PlayerID, int InstanceID, const FLootLockerServerUnequipAssetFromPlayerLoadoutResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerUnequipAssetFromPlayerLoadoutResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::UnEquipAssetFromPlayerLoadout, { PlayerID, InstanceID }, {}, FLootLockerServerUnequipAssetFromPlayerLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetID(int PlayerID, int AssetID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAddAssetToPlayerInventoryResponse>(FLootLockerServerAssetByAssetIdRequest{ AssetID }, ULootLockerServerEndpoints::AddAssetToPlayerInventory, { PlayerID }, {}, FLootLockerServerAddAssetToPlayerInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndVariationID(int PlayerID, int AssetID, int VariationID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAddAssetToPlayerInventoryResponse>(FLootLockerServerAssetByAssetIdAndVariationIdRequest{ AssetID, VariationID }, ULootLockerServerEndpoints::AddAssetToPlayerInventory, { PlayerID }, {}, FLootLockerServerAddAssetToPlayerInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::AddAssetToPlayerInventoryByAssetIDAndRentalOptionID(int PlayerID, int AssetID, int RentalOptionID, const FLootLockerServerAddAssetToPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAddAssetToPlayerInventoryResponse>(FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest{ AssetID, RentalOptionID }, ULootLockerServerEndpoints::AddAssetToPlayerInventory, { PlayerID }, {}, FLootLockerServerAddAssetToPlayerInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAlterPlayerInventoryResponse>(
        FLootLockerServerAlterPlayerInventoryByAssetIdRequest{ AssetsToRemove, AssetsToAdd },
        ULootLockerServerEndpoints::AlterPlayerInventory,
        { PlayerID },
        {},
        FLootLockerServerAlterPlayerInventoryResponseBP(),
        OnCompletedRequest
    );
}

void ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndVariationID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndVariationIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAlterPlayerInventoryResponse>(
        FLootLockerServerAlterPlayerInventoryByAssetIdAndAssetVariationIdRequest{ AssetsToRemove, AssetsToAdd },
        ULootLockerServerEndpoints::AlterPlayerInventory,
        { PlayerID },
        {},
        FLootLockerServerAlterPlayerInventoryResponseBP(),
        OnCompletedRequest
    );
}

void ULootLockerServerPlayerInventoryRequest::AlterPlayerInventoryAddAssetsByAssetIDAndRentalOptionID(int PlayerID, const TArray<FLootLockerServerAssetByAssetIdAndRentalOptionIdRequest>& AssetsToAdd, const TArray<int> AssetsToRemove, const FLootLockerServerAlterPlayerInventoryResponseDelegate& OnCompletedRequest)
{
    ULootLockerServerHttpClient::SendRequest<FLootLockerServerAlterPlayerInventoryResponse>(
        FLootLockerServerAlterPlayerInventoryByAssetIdAndRentalOptionIdRequest{ AssetsToRemove, AssetsToAdd },
        ULootLockerServerEndpoints::AlterPlayerInventory,
        { PlayerID },
        {},
        FLootLockerServerAlterPlayerInventoryResponseBP(),
        OnCompletedRequest
    );
}

