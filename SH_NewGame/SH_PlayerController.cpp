// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_PlayerController.h"
#include "Widget/Widget_IngameEdit.h"
#include "Widget/Widget_MainLogin.h"
#include "Actor/Actor_Monster.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"


ASH_PlayerController::ASH_PlayerController()
{
	//static ConstructorHelpers::FObjectFinder<UWidget_IngameEdit> FindInGameWidget(TEXT("/Game/UI/SH_IngameUI"));
	//if (FindInGameWidget.Succeeded())
	//	UWidget_IngameEdit* IngameEditUI = FindInGameWidget.Object;

}

void ASH_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	// 게임 맵 설정 // > 세이브 로드 기능 추가 <
	if (FindIngameEditUI)
	{
		IngameEditUI = CreateWidget<UWidget_IngameEdit>(this, FindIngameEditUI.Get());
		if (IngameEditUI)
		{
			IngameEditUI->AddToViewport();
		}
	}
	
}

void ASH_PlayerController::MonsterSpawnTimer(float fRate)
{
	MonsterPool.Reset();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASH_PlayerController::MonsterSpawn, fRate, true);
}

void ASH_PlayerController::MonsterSpawn()
{
	// 몬스터 정보 처리 , 어떤 몬스터? <Damage , HP , Speed 세팅 >;
	FActorSpawnParameters ActorSpawnParameters;

	SpawnCnt++;
	FVector StartLoc(1000.f, 1000.f, 1000.f);
	AActor* Spawn = GetWorld()->SpawnActor<AActor>(SpawnMonster, StartLoc, FRotator::ZeroRotator, ActorSpawnParameters);
	MonsterPool.Add(Spawn);
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Spanw : " + FString::FromInt(MonsterPool.Num()));

	if (SpawnMonsterCnt == SpawnCnt)
	{
		SpawnCnt = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Spanw Stop");
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}