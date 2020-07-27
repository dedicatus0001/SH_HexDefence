// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Tile.h"
#include "Actor_Monster.h"
#include "Actor_BoxFlag.h"
#include "Actor_Tower.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Materials/MaterialInstanceDynamic.h"

#define TileEffectAlpha 0.8
#define BorderTileMax 6
#define TileZScale FVector(2.f , 2.f , 6.f)

// Sets default values
AActor_Tile::AActor_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("TileMesh");
	RootComponent = TileMesh;

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("CollisionCapsule");
	CollisionCapsule->SetCapsuleRadius(40.f);
	CollisionCapsule->SetCapsuleHalfHeight(60.f);
	CollisionCapsule->SetupAttachment(TileMesh);

	// 4.25 : StaticMesh'/Game/Mesh/SM_TileMesh'  //4.24 : StaticMesh'/Game/Mesh/SM_Tile1'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Mesh/SM_TileMesh")); 
	if (Mesh.Succeeded())
		TileMesh->SetStaticMesh(Mesh.Object);
	TileMesh->SetWorldScale3D(FVector(2.f));

	// 주변 타일수
	BorderTile.SetNum(BorderTileMax);

	// 타임라인
	Timeline_TileEffect = CreateDefaultSubobject<UTimelineComponent>("Timeline");
	fCurve = CreateDefaultSubobject<UCurveFloat>("Curve");

	//static ConstructorHelpers::FObjectFinder<UCurveFloat> FindCurve(TEXT("/Game/CurveBase")); // CurveFloat'/Game/CurveBase.CurveBase'
	//if (FindCurve.Succeeded())
	//	fCurve = FindCurve.Object;

	FOnTimelineFloat StartTimeline;
	FOnTimelineEvent EndTimeline;

	StartTimeline.BindUFunction(this , FName("StartTimelineEvent"));
	EndTimeline.BindUFunction(this , FName("EndTimelineEvent"));

	fCurve->FloatCurve.AddKey(0, 1.f);
	fCurve->FloatCurve.AddKey(1.f, TileEffectAlpha);
	fCurve->FloatCurve.AddKey(2.f, 1.f);

	if (fCurve)
	{
		Timeline_TileEffect->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		Timeline_TileEffect->AddInterpFloat(fCurve, StartTimeline, FName("Key"));
		Timeline_TileEffect->SetTimelineFinishedFunc(EndTimeline);
		Timeline_TileEffect->SetLooping(true);
	}

}
// Called when the game starts or when spawned
void AActor_Tile::BeginPlay()
{
	Super::BeginPlay();
	
	// 
	MI_Tile = TileMesh->CreateDynamicMaterialInstance(0);
	ChangeColor(FColor::Blue);

	// 
	FlagBox = GetWorld()->SpawnActor<AActor_BoxFlag>(GetActorLocation(), GetActorRotation());
	FlagBox->SetActorHiddenInGame(true);
	
	// 캡슐 충돌처리
	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AActor_Tile::BeginOverlapEvent);
	CollisionCapsule->OnComponentEndOverlap.AddDynamic(this, &AActor_Tile::EndOverlapEvent);
}
void AActor_Tile::SetZScale(FVector ZScale)
{
	SetActorScale3D(ZScale);
}
bool AActor_Tile::SetTileState(FStateTile state)
{
	StateTile = state;
	ChangeColor();
	SetZScale();
	FlagBox->SetActorHiddenInGame(true);

	switch (StateTile)
	{
		case StartTile:
		{	
			if (TileState.bEnd)
				TileState.bEnd = false;
			if (TileState.bStart)
			{
				TileState.bStart = false;
				FlagBox->SetActorHiddenInGame(true);
			}
			else
			{
				TileState.bStart = true;
				FlagBox->SetActorHiddenInGame(false);
				FlagBox->ChangeColor(FColor::Blue);
			}
			return TileState.bStart;
		}
		case EndTile:
		{
			if (TileState.bStart)
				TileState.bStart = false;
			if (TileState.bEnd)
			{
				TileState.bEnd = false;
				FlagBox->SetActorHiddenInGame(true);
			}
			else
			{
				TileState.bEnd = true;
				FlagBox->SetActorHiddenInGame(false);
				FlagBox->ChangeColor(FColor::Red);
			}
			return TileState.bEnd;
		}
		case ObstacleTile: // Tower 설치 하기 >  Spawn , Components ? 
		{
			if (TileState.bWall)
			{
				SetZScale(TileZScale);
				if (TileState.bObstacle)
				{
					TileState.bObstacle = false;
				}
				else
				{
					TileState.bObstacle = true;
				}
			}
			return TileState.bObstacle;
		}
		case WallTile:
		{
			if (TileState.bObstacle)
				TileState.bObstacle = false;
			if (TileState.bWall)
			{
				TileState.bWall = false;
				SetZScale();
				ChangeColor(FColor::Blue);
			}
			else
			{
				TileState.bWall = true;
				SetZScale(TileZScale);
				ChangeColor();
			}
			return TileState.bWall;
		}
	}
	return false;
}
bool AActor_Tile::SetTileState(FSaveTileData state)
{
	TileState = state;
	ChangeColor();
	SetZScale();
	FlagBox->SetActorHiddenInGame(true);

	if(TileState.bStart)
	{
		TileState.bStart = true;
		FlagBox->SetActorHiddenInGame(false);
		FlagBox->ChangeColor(FColor::Blue);
		return TileState.bStart;
	}
	if(TileState.bEnd)
	{
		TileState.bEnd = true;
		FlagBox->SetActorHiddenInGame(false);
		FlagBox->ChangeColor(FColor::Red);
		return TileState.bEnd;
	}
	if(TileState.bWall)
	{
		// 타워 설치 여부 확인 추가 if(TileState.bObstacle)
		TileState.bWall = true;
		SetZScale(TileZScale);
		ChangeColor();
		return TileState.bWall;
	}
	return false;
}
void AActor_Tile::ChangeColor(FColor Color)
{
	if (MI_Tile && !TileState.bWall)
	{
		MI_Tile->SetVectorParameterValue("Color", Color);
	}
}
void AActor_Tile::ChangeColor()
{
	if (MI_Tile)
	{
		MI_Tile->SetVectorParameterValue("Color", FColor::Blue);
		if (TileState.bWall)
		{
			MI_Tile->SetVectorParameterValue("Color", FColor::Black);
		}
	}
}
void AActor_Tile::EndBorderTile(FColor TileColor)
{
	for (auto it : BorderTile)
	{
		if (it->IsValidLowLevel())
		{
			if (it->TileState.bWall)
			{
				it->MI_Tile->SetVectorParameterValue("Color", FColor::Black);
				continue;
			}
			it->MI_Tile->SetVectorParameterValue("Color", TileColor);
		}
	}
}
// Called every frame
void AActor_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AActor_Tile::BeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor_Monster* Monster = Cast<AActor_Monster>(OtherActor);
	if (Monster)
	{
		MonsterList.Add(Monster);
		Monster->CurrantPosTile = this;
	}
}
void AActor_Tile::EndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AActor_Monster* Monster = Cast<AActor_Monster>(OtherActor);
	if (Monster)
	{
		MonsterList.Remove(Monster);
		Monster->CurrantPosTile = nullptr;
	}
}
bool AActor_Tile::SetTower(AActor* Tower)
{
	// 타워가 설치될때 //
	if (TileState.bObstacle)
	{
		// 타워 종류?
		FTransform SpawnTransform = GetActorTransform();
		AActor_Tower* SelectTower = Cast<AActor_Tower>(Tower);
		if (!SelectTower)
			return false;

		if (Tower_Obstacle)
			Tower_Obstacle->SetActorLocation(FVector(2000.f));

		SelectTower->CurrentTile = this;
		Tower_Obstacle = SelectTower;
		Tower_Obstacle->SetActorLocation(GetActorLocation());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Spanw Tower Obstacle : " + Tower_Obstacle->GetName());
		// 타워 범위 설정? // 타워 마다 다른 설정? //

		return true;
	}
	return false;
}
// Timeline
void AActor_Tile::FocusTileEffect()
{
	if (Timeline_TileEffect->IsPlaying())
	{
		Timeline_TileEffect->Stop();
		EndTimelineEvent();
	}
	else
	{
		Timeline_TileEffect->PlayFromStart();
	}
}
// Timeline Play Event
void AActor_Tile::StartTimelineEvent(float value)
{
	if (MI_Tile)
		MI_Tile->SetScalarParameterValue(FName("Opacity"), value);
}
// Timeline Finished Event
void AActor_Tile::EndTimelineEvent()
{
	if (MI_Tile)
		MI_Tile->SetScalarParameterValue(FName("Opacity"), 1.f);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Timeline End : Timeline End");
}