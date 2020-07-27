// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_GameInstance.h"
#include "SH_GameModeBase.h"


void USH_GameInstance::InitLoadGame()
{
	const UWorld* const world = GetWorld();

	if (world)
	{
		ASH_GameModeBase* GM = Cast<ASH_GameModeBase>(world->GetAuthGameMode());
		if(GM)
		{
			

		}
	}

}