// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoTriggers.h"

#include "LootLockerServerSDKManager.h"

void ADemoTriggers::DemoInvokeTriggerOnBehalfOfPlayer()
{
	ULootLockerServerSDKManager::InvokeTriggerOnBehalfOfPlayer(FInvokeTriggerResponse::CreateUObject(this, &ADemoTriggers::OnInvokeTriggerOnBehalfOfPlayerCompleted), TriggerName, PlayerId);
}

void ADemoTriggers::OnInvokeTriggerOnBehalfOfPlayerCompleted(FLootLockerServerInvokeTriggerResponse Response)
{
	if (Response.success)
	{
		UE_LOG(LogTemp, Verbose, TEXT("InvokeTriggerOnBehalfOfPlayer Success"));
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("InvokeTriggerOnBehalfOfPlayer Failed"));
	}
}


