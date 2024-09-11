// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerMetadataRequest.h"

#include "LootLockerServerHttpClient.h"
#include "Dom/JsonObject.h"
#include "Utils/LootLockerServerUtilities.h"

//==================================================
// Metadata Entry Methods
//==================================================

bool FLootLockerServerMetadataEntry::TryGetValueAsString(FString& Output) const
{
	return EntryAsJson.TryGetStringField(TEXT("value"), Output);
}

bool FLootLockerServerMetadataEntry::TryGetValueAsDouble(double& Output) const
{
	return EntryAsJson.TryGetNumberField(TEXT("value"), Output);
}

bool FLootLockerServerMetadataEntry::TryGetValueAsInteger(int& Output) const
{
	return EntryAsJson.TryGetNumberField(TEXT("value"), Output);
}

bool FLootLockerServerMetadataEntry::TryGetValueAsBool(bool& Output) const
{
	return EntryAsJson.TryGetBoolField(TEXT("value"), Output);
}

bool FLootLockerServerMetadataEntry::TryGetRawValue(TSharedPtr<FJsonValue>& Output) const
{
	if (!EntryAsJson.HasField(TEXT("value")))
	{
		return false;
	}
	Output = EntryAsJson.Values[TEXT("value")];
	return Output.IsValid();
}

bool FLootLockerServerMetadataEntry::TryGetSerializedValue(FString& Output) const
{
	TSharedPtr<FJsonValue> Val;
	if(!TryGetRawValue(Val) || !Val.IsValid())
	{
		return false;
	}
	if (Type == ELootLockerServerMetadataTypes::Json || Type == ELootLockerServerMetadataTypes::Base64)
	{
		if (Val->Type == EJson::Object) {
			Output = LootLockerServerUtilities::FStringFromJsonObject(Val->AsObject());
			return !Output.IsEmpty();
		}
		Output = LootLockerServerUtilities::FStringFromJsonArray(Val->AsArray());
		return !Output.IsEmpty();
	}
	return Val->TryGetString(Output);
}

template<typename T>
bool FLootLockerServerMetadataEntry::TryGetValueAsUStruct(T& Output) const
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
	if (!TryGetValueAsJsonObject(jsonObject))
	{
		return false;
	}
	return FJsonObjectConverter::JsonObjectToUStruct<T>(jsonObject.ToSharedRef(), &Output, 0, 0);		
}

bool FLootLockerServerMetadataEntry::TryGetValueAsJsonObject(TSharedPtr<FJsonObject>& Output) const
{
	if(!EntryAsJson.HasTypedField(TEXT("value"), EJson::Object))
	{
		return false;
	}
	Output = EntryAsJson.GetObjectField(TEXT("value"));
	return Output.IsValid();
}

bool FLootLockerServerMetadataEntry::TryGetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const
{
	if (!EntryAsJson.HasTypedField(TEXT("value"), EJson::Array))
	{
		return false;
	}
	Output = EntryAsJson.GetArrayField(TEXT("value"));
	return true;
}

bool FLootLockerServerMetadataEntry::TryGetValueAsBase64(FLootLockerServerMetadataBase64Value& Output) const
{
	return TryGetValueAsUStruct(Output);
}

void FLootLockerServerMetadataEntry::_INTERNAL_SetJsonRepresentation(const FJsonObject& obj)
{
	EntryAsJson = obj;
}

int FLootLockerServerListMetadataResponse::__INTERNAL_GetEntryIndexByKey(const FString Key) const
{
	if(KeyToEntryIndex.Contains(Key))
	{
		const int* index = KeyToEntryIndex.Find(Key);
		if (index != nullptr && *index >= 0 && *index < Entries.Num()) {
			const FLootLockerServerMetadataEntry& EntryRef = Entries[*index];
			if(EntryRef.Key.Equals(Key)) {
				return *index;
			}
		}
	}
	return -1;
}

void FLootLockerServerListMetadataResponse::__INTERNAL_GenerateKeyMap()
{
	KeyToEntryIndex = TMap<FString, int>();
	int index = 0;
	for (FLootLockerServerMetadataEntry& Entry : Entries)
	{
		KeyToEntryIndex.Add(Entry.Key, index++);
	}
}

//==================================================
// Metadata Request Handler
//==================================================

ULootLockerServerMetadataRequest::ULootLockerServerMetadataRequest()
{
}

void ULootLockerServerMetadataRequest::ListMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FString& Key, const TArray<FString>& Tags, const bool IgnoreFiles, const FLootLockerServerListMetadataResponseBP& OnCompleteBP, const FLootLockerServerListMetadataResponseDelegate& OnComplete)
{
	TMultiMap<FString, FString> QueryParams;
	if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
	if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
	if (!Key.IsEmpty()) QueryParams.Add("key", Key);
	if (!Tags.IsEmpty()) {
		for (FString Tag : Tags)
		{
			QueryParams.Add("tags", Tag);
		}
	}
	if (IgnoreFiles) QueryParams.Add("ignore_files", "true");

	FString SourceAsString = ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerMetadataSources"), static_cast<int32>(Source)).ToLower();
	SourceAsString.ReplaceCharInline(' ', '_');

	ULootLockerServerHttpClient::SendRequest<FLootLockerServerListMetadataResponse>(FLootLockerServerEmptyRequest(), ULootLockerServerEndpoints::ListMetadata, { SourceAsString, SourceID }, QueryParams, FLootLockerServerListMetadataResponseBP(), FLootLockerServerListMetadataResponseDelegate(), ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerListMetadataResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([OnCompleteBP, OnComplete](FLootLockerServerListMetadataResponse& Response)
	{
		// Make sure we will have entries to parse before continuing
		if(!Response.Success || Response.Entries.IsEmpty() || Response.Entries.IsEmpty())
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;
		}
		Response.__INTERNAL_GenerateKeyMap();
		TSharedPtr<FJsonObject> obj = LootLockerServerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
		// Ensure that the full response was parsed before continuing
		if(!obj.IsValid())
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;			
		}

		TArray<TSharedPtr<FJsonValue>> JsonEntries = obj.Get()->GetArrayField(TEXT("entries"));
		// Make sure that the entries array was parsed before continuing
		if(JsonEntries.Num() != Response.Entries.Num())
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;
		}

		for (TSharedPtr<FJsonValue> JsonEntry : JsonEntries)
		{
			TSharedPtr<FJsonObject> JsonEntryObject = JsonEntry.Get()->AsObject();
			FString EntryKey = JsonEntryObject.Get()->GetStringField(TEXT("key"));
			int EntryIndex = Response.__INTERNAL_GetEntryIndexByKey(EntryKey);
			// If the fetched entry index is out of range or if it points to the wrong key, try to find the entry the old-fashioned way before giving up
			if (EntryIndex < 0 || EntryIndex >= Response.Entries.Num() 
				|| !Response.Entries[EntryIndex].Key.Equals(EntryKey)) {
				for (FLootLockerServerMetadataEntry& ResponseEntry : Response.Entries)
				{
					if (ResponseEntry.Key.Equals(EntryKey))
					{
						ResponseEntry._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
					}
				}
			}
			else
			{
				Response.Entries[EntryIndex]._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
			}
		}

		OnCompleteBP.ExecuteIfBound(Response);
		OnComplete.ExecuteIfBound(Response);
	}));
}

void ULootLockerServerMetadataRequest::GetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerServerGetMetadataResponseBP& OnCompleteBP, const FLootLockerServerGetMetadataResponseDelegate& OnComplete)
{
	ListMetadata(Source, SourceID, 1, 1, Key, TArray<FString>(), IgnoreFiles, FLootLockerServerListMetadataResponseBP(), FLootLockerServerListMetadataResponseDelegate::CreateLambda([OnCompleteBP, OnComplete, Key](const FLootLockerServerListMetadataResponse& ListResponse)
	{
		FLootLockerServerGetMetadataResponse SingleEntryResponse;
		SingleEntryResponse.Success = ListResponse.Success;
		SingleEntryResponse.StatusCode = ListResponse.StatusCode;
		SingleEntryResponse.FullTextFromServer = ListResponse.FullTextFromServer;
		SingleEntryResponse.ErrorData = ListResponse.ErrorData;
		if(ListResponse.Success && ListResponse.Entries.Num() == 1 && ListResponse.Entries[0].Key.Equals(Key))
		{
			SingleEntryResponse.Entry = ListResponse.Entries[0];
		}
		OnCompleteBP.ExecuteIfBound(SingleEntryResponse);
		OnComplete.ExecuteIfBound(SingleEntryResponse);
	}));
}
