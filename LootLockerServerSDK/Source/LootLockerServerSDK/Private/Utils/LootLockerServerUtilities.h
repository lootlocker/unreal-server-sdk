// Copyright (c) 2021 LootLocker

#pragma once

#include "JsonObjectConverter.h"

namespace LootLockerServerUtilities
{
    FString AppendParametersToUrl(FString Url, const TMultiMap<FString, FString>& QueryParams);

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString);
}