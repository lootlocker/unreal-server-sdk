// Copyright (c) 2021 LootLocker


#include "LootLockerServerStateData.h"

#include "LootLockerServerConfig.h"

FString ULootLockerServerStateData::ServerToken = "";

FString ULootLockerServerStateData::GetServerToken()
{
	return ServerToken;
}

void ULootLockerServerStateData::SetServerToken(FString InServerToken) {
	if(ServerToken.Equals(InServerToken)) {
		return;
	}
	ServerToken = InServerToken;
}

void ULootLockerServerStateData::ClearState()
{
	ServerToken = "";
}
