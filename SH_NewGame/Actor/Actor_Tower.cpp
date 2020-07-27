// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Tower.h"
#include "Actor_Tile.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AActor_Tower::AActor_Tower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = SceneComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Collision->SetCapsuleRadius(60.f);
	Collision->SetCapsuleHalfHeight(40.f);
	Collision->SetupAttachment(SceneComp);
	ArrowComp = CreateDefaultSubobject<UArrowComponent>("Arrow");
	ArrowComp->SetupAttachment(SceneComp);
	ArrowComp->SetRelativeLocation(FVector(0, 0, 120.f));

	Mesh->SetupAttachment(Collision);
	SkeletalMesh->SetupAttachment(Collision);
}
// Called when the game starts or when spawned
void AActor_Tower::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void AActor_Tower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TowerAttack();
}
void AActor_Tower::TowerAttack()
{
	// 1. Ÿ�� ���� ����
	if (!CurrentTile)
		return;

	for (auto it : CurrentTile->BorderTile)
	{
		if (it->IsValidLowLevel())
		{
			it->MonsterList;
		}
	}

}
// Ÿ�� ���� �ý���
void AActor_Tower::TowerAttack(AActor* Monster)
{
	if (Monster)
	{
		// Ÿ�Ͽ� ������ ����? // 
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Attack");
		// ���� �ָ� ������?
		// ���� Ÿ���� �����?
		// ���������� ������?
	}
}
void AActor_Tower::AttackEvent()
{
	// Ÿ�� ���� �̺�Ʈ
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AActor_Tower::TowerAttack, 3.f, true);
}