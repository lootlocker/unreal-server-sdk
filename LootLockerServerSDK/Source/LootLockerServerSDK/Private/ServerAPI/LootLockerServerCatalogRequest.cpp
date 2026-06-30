// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerCatalogRequest.h"

#include "LootLockerServerHttpClient.h"
#include "Utils/LootLockerServerUtilities.h"

ULootLockerServerCatalogRequest::ULootLockerServerCatalogRequest()
{
}

FString ULootLockerServerCatalogRequest::ListCatalogItemsByKey(const FString& CatalogKey, int Count, const FString& After, const FLootLockerServerListCatalogPricesResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0)
    {
        QueryParams.Add("per_page", FString::FromInt(Count));
    }
    if (!After.IsEmpty())
    {
        QueryParams.Add("cursor", After);
    }

    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListCatalogPricesResponse>(
        FLootLockerServerEmptyRequest{},
        ULootLockerServerEndpoints::ListCatalogItemsByKey,
        { CatalogKey },
        QueryParams,
        OnResponseCompleted);
}

FString ULootLockerServerCatalogRequest::ListCatalogItemsById(const TArray<FString>& CatalogListingIds, bool IncludeMetadata, const TArray<FString>& MetadataKeys, const FLootLockerServerListCatalogItemsByIdResponseDelegate& OnResponseCompleted)
{
    FLootLockerServerListCatalogItemsByIdRequest Request;
    Request.Ids = CatalogListingIds;

    if (IncludeMetadata)
    {
        Request.Includes.Metadata.All = (MetadataKeys.Num() == 0);
        Request.Includes.Metadata.Keys = MetadataKeys;
    }

    if (!IncludeMetadata)
    {
        return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListCatalogItemsByIdResponse>(
            Request,
            ULootLockerServerEndpoints::ListCatalogItemsById,
            {},
            {},
            OnResponseCompleted);
    }

    ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerListCatalogItemsByIdResponse>::FLootLockerServerResponseInspectorCallback MetadataParser =
        ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerListCatalogItemsByIdResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([OnResponseCompleted](FLootLockerServerListCatalogItemsByIdResponse& Response)
    {
        if (!Response.Success || Response.Items.Num() == 0)
        {
            OnResponseCompleted.ExecuteIfBound(Response);
            return;
        }
        TSharedPtr<FJsonObject> FullJsonObject = LootLockerServerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        if (!FullJsonObject.IsValid())
        {
            OnResponseCompleted.ExecuteIfBound(Response);
            return;
        }
        TArray<TSharedPtr<FJsonValue>> JsonItems = FullJsonObject->GetArrayField(TEXT("items"));
        if (JsonItems.Num() != Response.Items.Num())
        {
            OnResponseCompleted.ExecuteIfBound(Response);
            return;
        }

        for (int i = 0; i < JsonItems.Num(); i++)
        {
            TSharedPtr<FJsonObject> JsonItemObject = JsonItems[i]->AsObject();
            if (!JsonItemObject.IsValid())
            {
                continue;
            }
            TArray<TSharedPtr<FJsonValue>> JsonMetadataArray = JsonItemObject->GetArrayField(TEXT("metadata"));
            FLootLockerServerListCatalogItemsByIdEntry& Entry = Response.Items[i];

            for (int j = 0; j < JsonMetadataArray.Num(); j++)
            {
                TSharedPtr<FJsonObject> JsonMetadataObject = JsonMetadataArray[j]->AsObject();
                if (!JsonMetadataObject.IsValid())
                {
                    continue;
                }
                FString MetadataKey = JsonMetadataObject->GetStringField(TEXT("key"));
                for (int k = 0; k < Entry.Metadata.Num(); k++)
                {
                    if (Entry.Metadata[k].Key.Equals(MetadataKey))
                    {
                        Entry.Metadata[k]._INTERNAL_SetJsonRepresentation(*JsonMetadataObject.Get());
                        break;
                    }
                }
            }
        }

        OnResponseCompleted.ExecuteIfBound(Response);
    });

    return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListCatalogItemsByIdResponse>(
        Request,
        ULootLockerServerEndpoints::ListCatalogItemsById,
        {},
        {},
        FLootLockerServerListCatalogItemsByIdResponseDelegate(),
        MetadataParser);
}
