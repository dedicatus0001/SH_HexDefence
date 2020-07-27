// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Monster.h"
#include "Actor_Tile.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "../Widget/Widget_IngameEdit.h"
#include "../Widget/Widget_HPBar.h"
#include "../SH_PlayerController.h"
#include "../SH_GameModeBase.h"
#include "../SH/SH_MapSearch.h"

// Sets default values
AActor_Monster::AActor_Monster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = SceneComp;
	
	MonsterMesh = CreateDefaultSubobject<UStaticMeshComponent>("MonsterMesh");
	MonsterSkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>("MonsterSkeletalComp");
	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");

	Collision->SetupAttachment(SceneComp);
	Collision->SetCapsuleRadius(20.f);
	Collision->SetCapsuleHalfHeight(40.f);
	Collision->AddLocalOffset(FVector(0, 0, 80.f));

	MonsterMesh->SetupAttachment(Collision);
	MonsterSkeletalComp->SetupAttachment(Collision);

	MonsterMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.6f));
	MonsterSkeletalComp->SetWorldScale3D(FVector(0.3f, 0.3f, 0.6f));
	// 충돌처리
	MonsterMesh->SetGenerateOverlapEvents(false);
	MonsterSkeletalComp->SetGenerateOverlapEvents(false);
	Collision->SetGenerateOverlapEvents(false);
	// 몬스터 메쉬
	if (MonsterSkeletal)
		MonsterSkeletalComp->SetSkeletalMesh(MonsterSkeletal);
	// HP
	HPWidgetComp = CreateDefaultSubobject<UWidgetComponent>("HPWidgetComponent");
	HPWidgetComp->SetupAttachment(Collision);
}
// Called when the game starts or when spawned
void AActor_Monster::BeginPlay()
{
	Super::BeginPlay();
	
	ASH_GameModeBase* GM = Cast<ASH_GameModeBase>(GetWorld()->GetAuthGameMode());
	// 맵 탐색 정보 // 최단거리 탐색 결과 // 각 몬스터 마다 처리 
	MapSearchData = new SH_MapSearch;
	MapSearchData->CurrantTile = GM->StartTile;
	MapSearchData->EndTile = GM->EndTile;
	MapSearchData->MapSearch();
	// 몬스터 이동 처리; // 경로 
	MoveMonster();
	// 시작 출현 위치 
	SetActorLocation(MoveArray[0]);
	// HP 위젯
	HPBarWidget = Cast<UWidget_HPBar>(HPWidgetComp->GetClass());
}
void AActor_Monster::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	delete MapSearchData;
	Super::EndPlay(EndPlayReason);
}
// Called every frame
void AActor_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bTick)
	{
		static uint8 MaxCnt = MoveArray.Num();
		if (iMoveTemp < MaxCnt)
		{
			vStart = MoveArray[iMoveTemp];
			if (MoveArray.Num() - 1 > iMoveTemp)
				vEnd = MoveArray[iMoveTemp + 1];

			FVector vDis = (vStart - vEnd);
			SetActorLocation(GetActorLocation() - vDis.GetSafeNormal() * (DeltaTime * MonsterSpeed));
			if (FVector::Dist(GetActorLocation(), vEnd) < 1.f)
			{
				iMoveTemp++;
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "// MoveCnt : " + FString::FromInt(iMoveTemp) + "/ " + FString::FromInt(MaxCnt));
			}
		}
		// 마지막 타일 도착시 제거 & 라이프 처리
		if (iMoveTemp >= MaxCnt)
		{
			bTick = false;
			iMoveTemp = 0;
			// 생명력 감소 처리 ; 처리 실패시 
			ASH_PlayerController* PC = Cast<ASH_PlayerController>(GetWorld()->GetFirstPlayerController());
			// 생명력 카운터 증가
			PC->GetIngameEditUI()->LifeCntUpdate();
			MonsterDestroy();
		}
	}
}
void AActor_Monster::SetInitMonster(float Damage, float HP, float Speed)
{
	MonsterDamage = Damage;
	MonsterHP = HP;
	MonsterSpeed = Speed;
}
void AActor_Monster::MoveMonster()
{
	// MoveTile Search;
	int NextTile = 9999;
	for (int index = 0; index < MapSearchData->SearchTile.Num(); index++)
	{
		if (index == MapSearchData->SearchTile.Num() - 1)
		{
			MoveArray.Add(MapSearchData->SearchTile[index]->GetActorLocation());
			break;
		}
		int Next = MapSearchData->SearchTile[index]->BorderTile.Find(MapSearchData->SearchTile[index + 1]);
		if (Next != NextTile)
		{
			MoveArray.Add(MapSearchData->SearchTile[index]->GetActorLocation());
			NextTile = Next;
		}
	}
	// Move Function
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Monster Move Point : " + FString::FromInt(MoveArray.Num()));
	bTick = true;
}
void AActor_Monster::MoveResearch()
{
	ASH_GameModeBase* GM = Cast<ASH_GameModeBase>(GetWorld()->GetAuthGameMode());

	if (CurrantPosTile->IsValidLowLevel())
	{
		MapSearchData->CurrantTile = CurrantPosTile;
		MapSearchData->EndTile = GM->EndTile;
		MapSearchData->MapSearch();
	}
}
void AActor_Monster::MonsterDestroy()
{
	// 무브 라인 리셋
	MoveArray.Reset();
	// 몬스터 카운터 처리 // UI 리플레쉬
	ASH_PlayerController* PC = Cast<ASH_PlayerController>(GetWorld()->GetFirstPlayerController());
	// 카운터 증가
	PC->GetIngameEditUI()->MonsterCntUpdate();
	Destroy();
}
void AActor_Monster::MonsterAttacked(float Attacked)
{
	if (HPBarWidget->SetHPDecrease(Attacked))
		MonsterDestroy();
}