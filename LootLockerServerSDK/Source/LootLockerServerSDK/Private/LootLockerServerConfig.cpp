// Copyright (c) 2021 LootLocker

#include "LootLockerServerConfig.h"
#include "Launch/Resources/Version.h"

FString ULootLockerServerConfig::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 27
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuter(), Enum, true);
#else
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuterUPackage(), Enum, true);
#endif
	if (!EnumPtr)
		return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

	return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();

}
