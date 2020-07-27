// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SH_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USH_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SH_NEWGAME_API ISH_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent)
		void FocusTile(AActor* Tile);
	UFUNCTION(BlueprintImplementableEvent)
		void StartSingleGame();

};
