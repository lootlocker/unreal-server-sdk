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

bool FLootLockerServerMetadataEntry::TryGetValueAsFloat(float& Output) const
{
#if ENGINE_MAJOR_VERSION > 5
	return EntryAsJson.TryGetNumberField(TEXT("value"), Output);
#else
	double outDouble = 0.0f;
	bool success = EntryAsJson.TryGetNumberField(TEXT("value"), outDouble);
	Output = static_cast<float>(outDouble);
	return success;
#endif
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
	if(!EntryAsJson.HasTypedField<EJson::Object>(TEXT("value")))
	{
		return false;
	}
	Output = EntryAsJson.GetObjectField(TEXT("value"));
	return Output.IsValid();
}

bool FLootLockerServerMetadataEntry::TryGetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const
{
	if (!EntryAsJson.HasTypedField<EJson::Array>(TEXT("value")))
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

void FLootLockerServerMetadataEntry::SetValueAsString(const FString& Value) 
{
	EntryAsJson.SetStringField(TEXT("value"), Value);
	Type = ELootLockerServerMetadataTypes::String;
}

void FLootLockerServerMetadataEntry::SetValueAsFloat(const float& Value) 
{
	EntryAsJson.SetNumberField(TEXT("value"), Value);
	Type = ELootLockerServerMetadataTypes::Number;
}

void FLootLockerServerMetadataEntry::SetValueAsInteger(const int& Value) 
{
	EntryAsJson.SetNumberField(TEXT("value"), Value);
	Type = ELootLockerServerMetadataTypes::Number;
}

void FLootLockerServerMetadataEntry::SetValueAsBool(const bool& Value) 
{
	EntryAsJson.SetBoolField(TEXT("value"), Value);
	Type = ELootLockerServerMetadataTypes::Bool;
}

void FLootLockerServerMetadataEntry::SetRawValue(const TSharedPtr<FJsonValue>& Value) 
{
	EntryAsJson.SetField(TEXT("value"), Value);
	Type = ELootLockerServerMetadataTypes::Json;
}

template<typename T>
bool FLootLockerServerMetadataEntry::SetValueAsUStruct(const T& Value) 
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Value);
	if(!JsonObject.IsValid())
	{
		return false;
	}
	SetValueAsJsonObject(*JsonObject);
	return true;
}

void FLootLockerServerMetadataEntry::SetValueAsJsonObject(const FJsonObject& Value) 
{
	EntryAsJson.SetObjectField(TEXT("value"), MakeShared<FJsonObject>(Value));
	Type = ELootLockerServerMetadataTypes::Json;
}

void FLootLockerServerMetadataEntry::SetValueAsJsonArray(const TArray<TSharedPtr<FJsonValue>>& Value) 
{
	EntryAsJson.SetArrayField(TEXT("value"), Value);
	Type = ELootLockerServerMetadataTypes::Json;
}

void FLootLockerServerMetadataEntry::SetValueAsBase64(const FLootLockerServerMetadataBase64Value& Value) 
{
	SetValueAsUStruct(Value);
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeStringEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FString& Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::String);
	Entry.SetValueAsString(Value);
	return Entry;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeFloatEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const float& Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::Number);
	Entry.SetValueAsFloat(Value);
	return Entry;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeIntegerEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const int Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::Number);
	Entry.SetValueAsInteger(Value);
	return Entry;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeBoolEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const bool Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::Bool);
	Entry.SetValueAsBool(Value);
	return Entry;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeJsonValueEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const ELootLockerServerMetadataTypes Type, const TSharedPtr<FJsonValue> Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::Json);
	Entry.SetRawValue(Value);
	return Entry;
}

template<typename T>
FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeUStructEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const T& Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::Json);
	Entry.SetValueAsUStruct(Value);
	return Entry;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeJsonObjectEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FJsonObject& Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::Json);
	Entry.SetValueAsJsonObject(Value);
	return Entry;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeJsonArrayEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const TArray<TSharedPtr<FJsonValue>>& Value)
{
	FLootLockerServerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerServerMetadataTypes::Json);
	Entry.SetValueAsJsonArray(Value);
	return Entry;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeBase64Entry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FLootLockerServerMetadataBase64Value& Value)
{
	return MakeUStructEntry(Key, Tags, Access, Value);
}

void FLootLockerServerMetadataEntry::_INTERNAL_SetJsonRepresentation(const FJsonObject& obj)
{
	EntryAsJson = obj;
}

FLootLockerServerMetadataEntry FLootLockerServerMetadataEntry::MakeEntryExceptValue(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const ELootLockerServerMetadataTypes Type)
{
	FLootLockerServerMetadataEntry Entry;
	Entry.Key = Key;
	Entry.Tags = Tags;
	Entry.Type = Type;
	Entry.Access = Access;
	FJsonObject JsonRepresentation;
	JsonRepresentation.SetStringField(TEXT("key"), Key);
	TArray<TSharedPtr<FJsonValue>> TagArray;
	for (const FString& Tag : Tags)
	{
		TagArray.Add(MakeShared<FJsonValueString>(Tag));
	}
	JsonRepresentation.SetArrayField(TEXT("tags"), TagArray);
	JsonRepresentation.SetStringField(TEXT("type"), ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerMetadataTypes"), static_cast<int32>(Type)).ToLower());
	Entry.EntryAsJson = JsonRepresentation;
	return Entry;
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

int FLootLockerServerMetadataSourceAndEntries::__INTERNAL_GetEntryIndexByKey(const FString& Key) const
{
	if (KeyToEntryIndex.Contains(Key))
	{
		const int* index = KeyToEntryIndex.Find(Key);
		if (index != nullptr && *index >= 0 && *index < Entries.Num()) {
			const FLootLockerServerMetadataEntry& EntryRef = Entries[*index];
			if (EntryRef.Key.Equals(Key)) {
				return *index;
			}
		}
	}
	return -1;
}

void FLootLockerServerMetadataSourceAndEntries::__INTERNAL_GenerateKeyMap()
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
	if (Tags.Num() <= 0) {
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
		if(!Response.Success || Response.Entries.Num() <= 0)
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
				FLootLockerServerMetadataEntry& ResponseEntry = Response.Entries[EntryIndex];
				ResponseEntry._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
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

void ULootLockerServerMetadataRequest::SetMetadata(const ELootLockerServerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerServerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerServerSetMetadataResponseBP& OnCompleteBP, const FLootLockerServerSetMetadataResponseDelegate& OnComplete)
{
	if (SourceID.IsEmpty())
	{
		FLootLockerServerSetMetadataResponse Error = LootLockerServerResponseFactory::Error<
			FLootLockerServerSetMetadataResponse>("Can not perform actions for source with empty id");
		OnCompleteBP.ExecuteIfBound(Error);
		OnComplete.ExecuteIfBound(Error);
		return;
	}

	// Set source and source id
	FJsonObject ManuallySerializedRequest;
	FString SourceAsString = ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerMetadataSources"), static_cast<int32>(Source)).ToLower();
	SourceAsString.ReplaceCharInline(' ', '_');
	ManuallySerializedRequest.SetStringField(TEXT("source"), SourceAsString);
	ManuallySerializedRequest.SetStringField(TEXT("source_id"), SourceID);

	// Iterate over actions to perform and manually construct json since there's a ton of magic to it
	TArray<TSharedPtr<FJsonValue>> entries;
	for (const FLootLockerServerSetMetadataAction& ActionToPerform : MetadataToActionsToPerform)
	{
		// Serialize the brunt of the entry automatically
		// Should handle the fields key, tags, and access
		TSharedPtr<FJsonObject> JsonEntry = FJsonObjectConverter::UStructToJsonObject(ActionToPerform.Entry);
		if (!JsonEntry.IsValid())
		{
			FLootLockerServerSetMetadataResponse Error = LootLockerServerResponseFactory::Error<
				FLootLockerServerSetMetadataResponse>("Could not serialize action for key " + ActionToPerform.Entry.Key);
			OnCompleteBP.ExecuteIfBound(Error);
			OnComplete.ExecuteIfBound(Error);
			return;
		}

		// Make type lowercase
		JsonEntry->SetStringField(TEXT("type"), ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerMetadataTypes"), static_cast<int32>(ActionToPerform.Entry.Type)).ToLower());

		// Add the action that should be performed to the entry
		JsonEntry->SetStringField(TEXT("action"), ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerMetadataActions"), static_cast<int32>(ActionToPerform.Action)).ToLower());

		// Manually set the field "value"
		TSharedPtr<FJsonValue> RawEntryValue;
		if (!ActionToPerform.Entry.TryGetRawValue(RawEntryValue))
		{
			FLootLockerServerSetMetadataResponse Error = LootLockerServerResponseFactory::Error<
				FLootLockerServerSetMetadataResponse>("Could not get value to perform action " + JsonEntry->GetStringField(TEXT("action")) + " for key " + ActionToPerform.Entry.Key);
			OnCompleteBP.ExecuteIfBound(Error);
			OnComplete.ExecuteIfBound(Error);
			return;
		}
		JsonEntry->SetField(TEXT("value"), RawEntryValue);

		// Add manually serialized to entries array
		entries.Add(MakeShared<FJsonValueObject>(JsonEntry));
	}

	// Add entries to manually serialized request
	ManuallySerializedRequest.SetArrayField(TEXT("entries"), entries);
	FString SerializedRequest = LootLockerServerUtilities::FStringFromJsonObject(MakeShared<FJsonObject>(ManuallySerializedRequest));
	ULootLockerServerHttpClient::SendRawRequest<FLootLockerServerSetMetadataResponse>(SerializedRequest, ULootLockerServerEndpoints::MetadataActions, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerServerMetadataRequest::GetMultisourceMetadata(const TArray<FLootLockerServerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerServerGetMultisourceMetadataResponseBP& OnCompleteBP,	const FLootLockerServerGetMultisourceMetadataResponseDelegate& OnComplete)
{
	TMultiMap<FString, FString> QueryParams;
	if (IgnoreFiles) QueryParams.Add("ignore_files", "true");
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetMultisourceMetadataResponse>(FLootLockerServerGetMultisourceMetadataRequest{ SourcesAndKeysToGet }, ULootLockerServerEndpoints::GetMultisourceMetadata, {}, QueryParams, FLootLockerServerGetMultisourceMetadataResponseBP(), FLootLockerServerGetMultisourceMetadataResponseDelegate(), ULootLockerServerHttpClient::ResponseInspector<FLootLockerServerGetMultisourceMetadataResponse>::FLootLockerServerResponseInspectorCallback::CreateLambda([OnComplete, OnCompleteBP](FLootLockerServerGetMultisourceMetadataResponse& Response)
		{
			// Make sure we will have source and entry combos to parse before continuing
			if (!Response.Success || Response.Metadata.Num() <= 0)
			{
				OnCompleteBP.ExecuteIfBound(Response);
				OnComplete.ExecuteIfBound(Response);
				return;
			}
			TSharedPtr<FJsonObject> FullResponseObjectFromServer = LootLockerServerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
			// Ensure that the full response was parsed before continuing
			if (!FullResponseObjectFromServer.IsValid())
			{
				OnCompleteBP.ExecuteIfBound(Response);
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			const TArray<TSharedPtr<FJsonValue>>* JsonMetadataArray;
			if (!FullResponseObjectFromServer->TryGetArrayField(TEXT("metadata"), JsonMetadataArray)
				|| JsonMetadataArray == nullptr
				|| JsonMetadataArray->Num() != Response.Metadata.Num())
			{
				FLootLockerServerGetMultisourceMetadataResponse Error = LootLockerServerResponseFactory::Error<
					FLootLockerServerGetMultisourceMetadataResponse>("Could not parse metadata array");
				OnCompleteBP.ExecuteIfBound(Error);
				OnComplete.ExecuteIfBound(Error);
				return;
			}

			// Iterate over each source and do manual entry parsing
			for (int i = 0; i < Response.Metadata.Num(); ++i)
			{
				FLootLockerServerMetadataSourceAndEntries& Metadata = Response.Metadata[i];
				FJsonObject& MetadaAsJson = *(*JsonMetadataArray)[i]->AsObject();
				Metadata.__INTERNAL_GenerateKeyMap();

				TArray<TSharedPtr<FJsonValue>> JsonEntries = MetadaAsJson.GetArrayField(TEXT("entries"));
				// Make sure that the entries array was parsed before continuing
				if (JsonEntries.Num() != Metadata.Entries.Num())
				{
					FLootLockerServerGetMultisourceMetadataResponse Error = LootLockerServerResponseFactory::Error<
						FLootLockerServerGetMultisourceMetadataResponse>("Could not parse metadata entry array for metadata with source id " + Metadata.Source_id);
					OnCompleteBP.ExecuteIfBound(Error);
					OnComplete.ExecuteIfBound(Error);
					return;
				}

				for (TSharedPtr<FJsonValue> JsonEntry : JsonEntries)
				{
					TSharedPtr<FJsonObject> JsonEntryObject = JsonEntry.Get()->AsObject();
					FString EntryKey = JsonEntryObject.Get()->GetStringField(TEXT("key"));
					int EntryIndex = Metadata.__INTERNAL_GetEntryIndexByKey(EntryKey);
					// If the fetched entry index is out of range or if it points to the wrong key, try to find the entry the old-fashioned way before giving up
					if (EntryIndex < 0 || EntryIndex >= Metadata.Entries.Num()
						|| !Metadata.Entries[EntryIndex].Key.Equals(EntryKey)) {
						for (FLootLockerServerMetadataEntry& ResponseEntry : Metadata.Entries)
						{
							if (ResponseEntry.Key.Equals(EntryKey))
							{
								ResponseEntry._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
							}
						}
					}
					else
					{
						Metadata.Entries[EntryIndex]._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
					}
				}

			}

			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
		}));

}
