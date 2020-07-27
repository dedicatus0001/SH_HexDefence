// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn_Default.generated.h"

class ASH_PlayerController;
class AActor_Tile;

UCLASS()
class SH_NEWGAME_API APawn_Default : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawn_Default();

	// 체크 중인 타일
	AActor_Tile* CheckTile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void LeftMousePressed();
	UFUNCTION()
		void TestNum1Pressed();
	UFUNCTION()
		void Edit1Pressed();
	UFUNCTION()
		void Edit2Pressed();
	UFUNCTION()
		void Edit3Pressed();
	UFUNCTION()
		void Edit4Pressed();
	UFUNCTION()
		void LeftMouseReleased();

	// Mouse Hit Object // 클릭 후 이전 타일 정보
	AActor_Tile* CurrentHitActor;

	// Frist PlayerController
	ASH_PlayerController* PC;

	// Timer
	FTimerHandle NewTimer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
