// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerItemRequestHandler.h"

#include "LootLockerServerHttpClient.h"
#include "Dom/JsonObject.h"
#include "Utils/LootLockerServerUtilities.h"

namespace
{
    /**
     * The backend list endpoint returns raw inventory rows, which currently marshal in
     * PascalCase because the Inventory struct has no JSON tags. Rewrite the known keys to the
     * snake_case names the DTOs use so both the list and get-item endpoints deserialize.
     * Keys that are already snake_case are left untouched, so this is a no-op once the backend
     * adds JSON tags.
     */
    bool NormalizeInventoryItemKeys(TSharedPtr<FJsonObject>& ItemObject)
    {
        static const TMap<FString, FString> PascalToSnake = {
            { TEXT("ID"), TEXT("id") },
            { TEXT("PlayerID"), TEXT("player_id") },
            { TEXT("ItemTemplateID"), TEXT("item_template_id") },
            { TEXT("ItemType"), TEXT("item_type") },
            { TEXT("Consumable"), TEXT("consumable") },
            { TEXT("Count"), TEXT("count") },
            { TEXT("Source"), TEXT("source") },
            { TEXT("CreatedAt"), TEXT("created_at") },
            { TEXT("UpdatedAt"), TEXT("updated_at") },
            { TEXT("DeletedAt"), TEXT("deleted_at") },
            { TEXT("Metadata"), TEXT("metadata") },
        };

        bool bRenamedAnyKey = false;
        for (const TPair<FString, FString>& Pair : PascalToSnake)
        {
            if (ItemObject->HasField(Pair.Key) && !ItemObject->HasField(Pair.Value))
            {
                ItemObject->SetField(Pair.Value, ItemObject->TryGetField(Pair.Key));
                ItemObject->RemoveField(Pair.Key);
                bRenamedAnyKey = true;
            }
        }
        return bRenamedAnyKey;
    }

    /**
     * FJsonObjectConverter populates the public metadata fields, but the value itself lives in the
     * entry's private JSON representation, so it has to be copied over explicitly. Matches entries
     * by key, which is unique within a single item's metadata.
     */
    void PopulateMetadataJsonRepresentations(const TArray<TSharedPtr<FJsonValue>>& JsonItems, TArray<FLootLockerServerItem>& Items)
    {
        const int32 ItemCount = FMath::Min(JsonItems.Num(), Items.Num());
        for (int32 ItemIndex = 0; ItemIndex < ItemCount; ++ItemIndex)
        {
            TSharedPtr<FJsonObject> JsonItemObject = JsonItems[ItemIndex].IsValid() ? JsonItems[ItemIndex]->AsObject() : nullptr;
            if (!JsonItemObject.IsValid())
            {
                continue;
            }

            const TArray<TSharedPtr<FJsonValue>>* JsonEntries = nullptr;
            if (!JsonItemObject->TryGetArrayField(TEXT("metadata"), JsonEntries) || JsonEntries == nullptr)
            {
                continue;
            }

            for (const TSharedPtr<FJsonValue>& JsonEntry : *JsonEntries)
            {
                TSharedPtr<FJsonObject> JsonEntryObject = JsonEntry.IsValid() ? JsonEntry->AsObject() : nullptr;
                if (!JsonEntryObject.IsValid())
                {
                    continue;
                }

                FString EntryKey;
                if (!JsonEntryObject->TryGetStringField(TEXT("key"), EntryKey))
                {
                    continue;
                }

                for (FLootLockerServerMetadataEntry& ResponseEntry : Items[ItemIndex].Metadata)
                {
                    if (ResponseEntry.Key.Equals(EntryKey))
                    {
                        ResponseEntry._INTERNAL_SetJsonRepresentation(*JsonEntryObject);
                    }
                }
            }
        }
    }
}

ULootLockerServerItemRequestHandler::ULootLockerServerItemRequestHandler()
{
}

FString ULootLockerServerItemRequestHandler::ListPlayerItems(int PlayerID, int Page, int PerPage, const FLootLockerServerListPlayerItemsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0)
    {
        QueryParams.Add("page", FString::FromInt(Page));
    }
    if (PerPage > 0)
    {
        QueryParams.Add("per_page", FString::FromInt(PerPage));
    }
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListPlayerItemsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerItems, { PlayerID }, QueryParams, FLootLockerServerListPlayerItemsResponseDelegate(), ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerListPlayerItemsResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerServerListPlayerItemsResponse& Response)
    {
        // The response is deserialized before this inspector runs, so re-run the conversion once the
        // PascalCase keys have been rewritten to the snake_case names the DTO declares.
        if (!Response.Success || Response.FullTextFromServer.IsEmpty())
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        TSharedPtr<FJsonObject> ResponseAsJson = LootLockerServerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        if (!ResponseAsJson.IsValid())
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        const TArray<TSharedPtr<FJsonValue>>* JsonItems = nullptr;
        if (!ResponseAsJson->TryGetArrayField(TEXT("items"), JsonItems) || JsonItems == nullptr)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        bool bNormalizedAnyItem = false;
        for (const TSharedPtr<FJsonValue>& JsonItem : *JsonItems)
        {
            TSharedPtr<FJsonObject> JsonItemObject = JsonItem.IsValid() ? JsonItem->AsObject() : nullptr;
            if (!JsonItemObject.IsValid())
            {
                continue;
            }
            bNormalizedAnyItem |= NormalizeInventoryItemKeys(JsonItemObject);
        }

        if (bNormalizedAnyItem)
        {
            FJsonObjectConverter::JsonObjectToUStruct(ResponseAsJson.ToSharedRef(), FLootLockerServerListPlayerItemsResponse::StaticStruct(), &Response, 0, 0);
            Response.Success = true;
            Response.FullTextFromServer = LootLockerServerUtilities::FStringFromJsonObject(ResponseAsJson);
        }

        // Must run after the re-deserialization above, which replaces Response.Items.
        PopulateMetadataJsonRepresentations(*JsonItems, Response.Items);

        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerItemRequestHandler::GetPlayerItem(int PlayerID, const FString& InventoryId, const FLootLockerServerGetPlayerItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerItem, { PlayerID, InventoryId }, {}, FLootLockerServerGetPlayerItemResponseDelegate(), ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerGetPlayerItemResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerServerGetPlayerItemResponse& Response)
    {
        // FJsonObjectConverter populates the public metadata fields, but the value itself lives in the
        // entry's private JSON representation, so it has to be copied over explicitly.
        if (!Response.Success || Response.Metadata.Num() <= 0)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        TSharedPtr<FJsonObject> ResponseAsJson = LootLockerServerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        if (!ResponseAsJson.IsValid())
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        const TArray<TSharedPtr<FJsonValue>>* JsonEntries = nullptr;
        if (!ResponseAsJson->TryGetArrayField(TEXT("metadata"), JsonEntries) || JsonEntries == nullptr)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        for (const TSharedPtr<FJsonValue>& JsonEntry : *JsonEntries)
        {
            TSharedPtr<FJsonObject> JsonEntryObject = JsonEntry.IsValid() ? JsonEntry->AsObject() : nullptr;
            if (!JsonEntryObject.IsValid())
            {
                continue;
            }

            FString EntryKey;
            if (!JsonEntryObject->TryGetStringField(TEXT("key"), EntryKey))
            {
                continue;
            }

            for (FLootLockerServerMetadataEntry& ResponseEntry : Response.Metadata)
            {
                if (ResponseEntry.Key.Equals(EntryKey))
                {
                    ResponseEntry._INTERNAL_SetJsonRepresentation(*JsonEntryObject);
                }
            }
        }

        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerItemRequestHandler::DeletePlayerItem(int PlayerID, const FString& InventoryId, const FLootLockerServerDeletePlayerItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerDeletePlayerItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeletePlayerItem, { PlayerID, InventoryId }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::GrantItemToPlayer(int PlayerID, const FLootLockerServerGrantItemRequest& Request, const FLootLockerServerGrantItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGrantItemResponse>(Request, ULootLockerServerEndpoints::GrantItemToPlayer, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::SplitPlayerItemStack(int PlayerID, const FString& InventoryId, const FLootLockerServerSplitItemRequest& Request, const FLootLockerServerSplitPlayerItemStackResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSplitPlayerItemStackResponse>(Request, ULootLockerServerEndpoints::SplitPlayerItemStack, { PlayerID, InventoryId }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::MergePlayerItemStacks(int PlayerID, const FLootLockerServerMergeItemsRequest& Request, const FLootLockerServerMergePlayerItemStacksResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerMergePlayerItemStacksResponse>(Request, ULootLockerServerEndpoints::MergePlayerItemStacks, { PlayerID }, {}, OnCompletedRequest);
}