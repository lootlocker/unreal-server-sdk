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
    void PopulateMetadataJsonRepresentations(const TArray<TSharedPtr<FJsonValue>>& JsonItems, TArray<FLootLockerServerInventoryItem>& Items)
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

FString ULootLockerServerItemRequestHandler::ListPlayerInventoryItems(int PlayerID, int Page, int PerPage, const FLootLockerServerListPlayerInventoryItemsResponseDelegate& OnCompletedRequest)
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
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListPlayerInventoryItemsResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListPlayerInventoryItems, { PlayerID }, QueryParams, FLootLockerServerListPlayerInventoryItemsResponseDelegate(), ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerListPlayerInventoryItemsResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerServerListPlayerInventoryItemsResponse& Response)
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
            // Preserve the raw HTTP body across re-deserialization of the normalized items.
            const FString RawResponseBody = Response.FullTextFromServer;
            FJsonObjectConverter::JsonObjectToUStruct(ResponseAsJson.ToSharedRef(), FLootLockerServerListPlayerInventoryItemsResponse::StaticStruct(), &Response, 0, 0);
            Response.Success = true;
            Response.FullTextFromServer = RawResponseBody;
        }

        // Must run after the re-deserialization above, which replaces Response.Items.
        PopulateMetadataJsonRepresentations(*JsonItems, Response.Items);

        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerServerItemRequestHandler::GetPlayerInventoryItem(int PlayerID, const FString& InventoryId, const FLootLockerServerGetPlayerInventoryItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetPlayerInventoryItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetPlayerInventoryItem, { PlayerID, InventoryId }, {}, FLootLockerServerGetPlayerInventoryItemResponseDelegate(), ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerGetPlayerInventoryItemResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerServerGetPlayerInventoryItemResponse& Response)
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

FString ULootLockerServerItemRequestHandler::DeletePlayerInventoryItem(int PlayerID, const FString& InventoryId, const FLootLockerServerDeletePlayerInventoryItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerDeletePlayerInventoryItemResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::DeletePlayerInventoryItem, { PlayerID, InventoryId }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::GrantItemToPlayerInventory(int PlayerID, const FLootLockerServerGrantItemRequest& Request, const FLootLockerServerGrantItemResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGrantItemResponse>(Request, ULootLockerServerEndpoints::GrantItemToPlayerInventory, { PlayerID }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::SplitPlayerInventoryItemStack(int PlayerID, const FString& InventoryId, const FLootLockerServerSplitInventoryItemRequest& Request, const FLootLockerServerSplitPlayerInventoryItemStackResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerSplitPlayerInventoryItemStackResponse>(Request, ULootLockerServerEndpoints::SplitPlayerInventoryItemStack, { PlayerID, InventoryId }, {}, OnCompletedRequest);
}

FString ULootLockerServerItemRequestHandler::MergePlayerInventoryItemStacks(int PlayerID, const FLootLockerServerMergeInventoryItemsRequest& Request, const FLootLockerServerMergePlayerInventoryItemStacksResponseDelegate& OnCompletedRequest)
{
    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerMergePlayerInventoryItemStacksResponse>(Request, ULootLockerServerEndpoints::MergePlayerInventoryItemStacks, { PlayerID }, {}, OnCompletedRequest);
}