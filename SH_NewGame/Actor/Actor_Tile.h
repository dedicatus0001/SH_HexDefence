// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../SaveGame/SH_SaveGame.h"
#include "Actor_Tile.generated.h"

enum FhexagonTile
{
	TopRight,
	ZeroRight,
	ButtomRight,
	ButtomLeft,
	ZeroLeft,
	TopLeft,
};

enum FStateTile
{
	StartTile,
	EndTile,
	ObstacleTile,
	WallTile,
	Tile,
};

class AActor_BoxFlag;
class UMaterialInstanceDynamic;
class UStaticMeshComponent;
class UChildActorComponent;
class UCapsuleComponent;
class UPrimitiveComponent;
class UTimelineComponent;
class UCurveFloat;
class AActor_Monster;
enum class ETowerState : uint8;

UCLASS()
class SH_NEWGAME_API AActor_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Tile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* TileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UChildActorComponent* FlagChilActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCapsuleComponent* CollisionCapsule;
	UPROPERTY()
		TArray<AActor_Tile*> BorderTile; // 주변 인접 타일 Max 6개

	// 타일 번호
	UINT TileNum;
	// 타일 상태
	FSaveTileData TileState;
	// 상태 박스
	AActor_BoxFlag* FlagBox; 
	// 상태
	FStateTile StateTile;
	// 타워 정보
	bool SetTower(AActor* tower);
	FORCEINLINE AActor* GetTower() const { return Tower_Obstacle; }
	// 길찾기 연결 대상
	AActor_Tile* ParantTile = nullptr;
	UINT TotalDistance = 0;
	// 타임라인
	class UTimelineComponent* Timeline_TileEffect;
	// 현재 타일에 있는 몬스터 리스트
	TArray<AActor_Monster*> MonsterList;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* MI_Tile;
	// Tower Actor // 현재 타워 정보? // 
	AActor* Tower_Obstacle;
	// 타임라인 이벤트
	class UCurveFloat* fCurve;

	UFUNCTION()
		void StartTimelineEvent(float value);
	UFUNCTION()
		void EndTimelineEvent();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 타일 크기(Z축) 변경
	void SetZScale(FVector ZScale = FVector(2.f));
	// 타일 생상 변경
	void EndBorderTile(FColor TileColor = FColor::Blue);
	void ChangeColor(FColor Color);
	void ChangeColor();
	// 클릭 대상 효과 처리
	void FocusTileEffect();
	//
	bool SetTileState(FStateTile state);
	bool SetTileState(FSaveTileData state);
	// Tile, Monster 정보 교환
	UFUNCTION() 
		void BeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()  
		void EndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
