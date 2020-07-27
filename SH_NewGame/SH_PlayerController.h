// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SH_PlayerController.generated.h"

class UWidget_IngameEdit;
class UWidget_MainLogin;
class AActor_Tile;
class AActor_Monster;

UCLASS()
class SH_NEWGAME_API ASH_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASH_PlayerController();

	// ����Ʈ ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameUI")
		TSubclassOf<UWidget_IngameEdit> FindIngameEditUI;

	FORCEINLINE UWidget_IngameEdit* GetIngameEditUI() const { return IngameEditUI; }

	// ���� Ǯ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterPool")
		TSubclassOf<AActor> SpawnMonster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterPool")
		int SpawnMonsterCnt = 5;

	// ���� ���� �Լ� 
	void MonsterSpawnTimer(float fRate);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UWidget_IngameEdit* IngameEditUI;

	UFUNCTION()
		void MonsterSpawn();
	
	FTimerHandle TimerHandle;
	int SpawnCnt;
	TArray<AActor*> MonsterPool;
};
