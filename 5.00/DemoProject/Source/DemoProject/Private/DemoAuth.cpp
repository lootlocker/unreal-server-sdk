// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAuth.h"

void ADemoAuth::DemoStartSession()
{
	ULootLockerServerSDKManager::StartSession(FServerAuthResponse::CreateUObject(this, &ADemoAuth::OnStartSessionCompleted));
}

void ADemoAuth::DemoMaintainSession()
{
	ULootLockerServerSDKManager::MaintainSession(FServerAuthResponse::CreateUObject(this, &ADemoAuth::OnMaintainSessionCompleted));
}

void ADemoAuth::OnStartSessionCompleted(FLootLockerServerAuthenticationResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnStartSession Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnStartSession Failed"));
	}
}

void ADemoAuth::OnMaintainSessionCompleted(FLootLockerServerAuthenticationResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnMaintainSession Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("OnMaintainSession Failed"));
	}
}
