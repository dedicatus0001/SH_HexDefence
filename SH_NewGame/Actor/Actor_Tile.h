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
		TArray<AActor_Tile*> BorderTile; // �ֺ� ���� Ÿ�� Max 6��

	// Ÿ�� ��ȣ
	UINT TileNum;
	// Ÿ�� ����
	FSaveTileData TileState;
	// ���� �ڽ�
	AActor_BoxFlag* FlagBox; 
	// ����
	FStateTile StateTile;
	// Ÿ�� ����
	bool SetTower(AActor* tower);
	FORCEINLINE AActor* GetTower() const { return Tower_Obstacle; }
	// ��ã�� ���� ���
	AActor_Tile* ParantTile = nullptr;
	UINT TotalDistance = 0;
	// Ÿ�Ӷ���
	class UTimelineComponent* Timeline_TileEffect;
	// ���� Ÿ�Ͽ� �ִ� ���� ����Ʈ
	TArray<AActor_Monster*> MonsterList;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* MI_Tile;
	// Tower Actor // ���� Ÿ�� ����? // 
	AActor* Tower_Obstacle;
	// Ÿ�Ӷ��� �̺�Ʈ
	class UCurveFloat* fCurve;

	UFUNCTION()
		void StartTimelineEvent(float value);
	UFUNCTION()
		void EndTimelineEvent();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Ÿ�� ũ��(Z��) ����
	void SetZScale(FVector ZScale = FVector(2.f));
	// Ÿ�� ���� ����
	void EndBorderTile(FColor TileColor = FColor::Blue);
	void ChangeColor(FColor Color);
	void ChangeColor();
	// Ŭ�� ��� ȿ�� ó��
	void FocusTileEffect();
	//
	bool SetTileState(FStateTile state);
	bool SetTileState(FSaveTileData state);
	// Tile, Monster ���� ��ȯ
	UFUNCTION() 
		void BeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()  
		void EndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
