// Copyright (c) 2021 LootLocker

#include "LootLockerServerConfig.h"


FString ULootLockerServerConfig::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
	if (!EnumPtr)
		return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

	return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();

}
