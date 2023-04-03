// Copyright (c) 2021 LootLocker

#include "LootLockerServerUtilities.h"

namespace LootLockerServerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter)
    {
        FString AppendSymbol = Url.Contains("?") ? "&" : "?";
        return Url + AppendSymbol + Parameter;
    }
}
