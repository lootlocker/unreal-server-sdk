// Copyright (c) 2021 LootLocker


#include "LootLockerServerStateData.h"

#include "LootLockerServerPersistedState.h"
#include "LootLockerServerConfig.h"
#include "Kismet/GameplayStatics.h"
#include "Launch/Resources/Version.h"

FString ULootLockerServerStateData::ServerToken = "";
bool ULootLockerServerStateData::StateLoaded = false;

#if ENGINE_MAJOR_VERSION < 5
const FString ULootLockerStateData::SaveSlot = "LootLocker";
#endif

void ULootLockerServerStateData::LoadStateFromDiskIfNeeded() 
{
	if(StateLoaded)
	{
		return;
	}

	if (ULootLockerServerPersistedState* LoadedState = Cast<ULootLockerServerPersistedState>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveIndex)))
	{
		ServerToken = LoadedState->ServerToken;
		UE_LOG(LogLootLockerServerSDK, Log, TEXT("Loaded LootLocker state from disk"));
		StateLoaded = true;
		return;
	}
	UE_LOG(LogLootLockerServerSDK, Warning, TEXT("Failed to load LootLocker state from disk"));
}

void ULootLockerServerStateData::SaveStateToDisk() 
{
	if (ULootLockerServerPersistedState* SavedState = Cast<ULootLockerServerPersistedState>(UGameplayStatics::CreateSaveGameObject(ULootLockerServerPersistedState::StaticClass())))
	{
		SavedState->ServerToken = ServerToken;

		if (UGameplayStatics::SaveGameToSlot(SavedState, SaveSlot, SaveIndex)) {
			UE_LOG(LogLootLockerServerSDK, Log, TEXT("Saved LootLocker state to disk"));
			return;
		}
	}
    UE_LOG(LogLootLockerServerSDK, Warning, TEXT("Failed to save LootLocker state to disk"));
}

FString ULootLockerServerStateData::GetServerToken()
{
	LoadStateFromDiskIfNeeded();
	return ServerToken;
}

void ULootLockerServerStateData::SetServerToken(FString InServerToken) {
	LoadStateFromDiskIfNeeded();
	if(InServerToken.Equals(InServerToken)) {
		return;
	}
	ServerToken = InServerToken;
	SaveStateToDisk();
}

void ULootLockerServerStateData::ClearState()
{
	LoadStateFromDiskIfNeeded();
	ServerToken = "";
	SaveStateToDisk();
	StateLoaded = false;
}
