// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SH_LoginPlayerController.generated.h"

class UWidget_MainLogin;

UCLASS()
class SH_NEWGAME_API ASH_LoginPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// ·Î±×ÀÎ À§Á¬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameUI")
		TSubclassOf<UWidget_MainLogin> FindLoginUI;

	FORCEINLINE UWidget_MainLogin* GetLoginUI() const { return LoginUI; }


protected:
	virtual void BeginPlay() override;

	UWidget_MainLogin* LoginUI;

};
