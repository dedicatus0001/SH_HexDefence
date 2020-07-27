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
	// �浹ó��
	MonsterMesh->SetGenerateOverlapEvents(false);
	MonsterSkeletalComp->SetGenerateOverlapEvents(false);
	Collision->SetGenerateOverlapEvents(false);
	// ���� �޽�
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
	// �� Ž�� ���� // �ִܰŸ� Ž�� ��� // �� ���� ���� ó�� 
	MapSearchData = new SH_MapSearch;
	MapSearchData->CurrantTile = GM->StartTile;
	MapSearchData->EndTile = GM->EndTile;
	MapSearchData->MapSearch();
	// ���� �̵� ó��; // ��� 
	MoveMonster();
	// ���� ���� ��ġ 
	SetActorLocation(MoveArray[0]);
	// HP ����
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
		// ������ Ÿ�� ������ ���� & ������ ó��
		if (iMoveTemp >= MaxCnt)
		{
			bTick = false;
			iMoveTemp = 0;
			// ����� ���� ó�� ; ó�� ���н� 
			ASH_PlayerController* PC = Cast<ASH_PlayerController>(GetWorld()->GetFirstPlayerController());
			// ����� ī���� ����
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
	// ���� ���� ����
	MoveArray.Reset();
	// ���� ī���� ó�� // UI ���÷���
	ASH_PlayerController* PC = Cast<ASH_PlayerController>(GetWorld()->GetFirstPlayerController());
	// ī���� ����
	PC->GetIngameEditUI()->MonsterCntUpdate();
	Destroy();
}
void AActor_Monster::MonsterAttacked(float Attacked)
{
	if (HPBarWidget->SetHPDecrease(Attacked))
		MonsterDestroy();
}