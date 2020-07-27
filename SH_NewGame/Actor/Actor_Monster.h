// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Monster.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class USkeletalMeshComponent;
class USkeletalMesh;
class AActor_Tile;
class SH_MapSearch;
class UCapsuleComponent;
class UWidgetComponent;
class UWidget_HPBar;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveDelegate);

UCLASS()
class SH_NEWGAME_API AActor_Monster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Monster();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MonsterMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCapsuleComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* MonsterSkeletalComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UWidgetComponent* HPWidgetComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UMaterialInstanceDynamic* MI_Monster;

	// 몬스터 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Allowprivateaccess = true), Category = "MonsterINFO")
		float MonsterDamage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Allowprivateaccess = true), Category = "MonsterINFO")
		float MonsterHP = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Allowprivateaccess = true), Category = "MonsterINFO")
		float MonsterSpeed = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Allowprivateaccess = true), Category = "MonsterINFO")
		USkeletalMesh* MonsterSkeletal;
	
	// 몬스터 사망 처리 
	void MonsterDestroy();
	// 몬스터 피격 처리
	void MonsterAttacked(float Attacked);
	// 맵 탐색 시 현재 위치
	SH_MapSearch* MapSearchData;
	// 맵 이동 타이머
	FTimerHandle MoveTimer;
	// 맵 이동 위치 코너 데이터
	TArray<FVector> MoveArray;
	// 이동 위치 시작  // Start = MoveArray[0] , End =  MoveArray[1]
	FVector vStart, vEnd;
	// 무브 커브 카운터 
	uint8 iMoveTemp = 0;
	bool bTick = false;

	UWidget_HPBar* HPBarWidget;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 경로 재탐색시 시작 타일// 
	AActor_Tile* CurrantPosTile;

	void SetInitMonster(float Damage, float HP, float Speed);
	void MoveMonster();

	UWidget_HPBar* GetHPBarWidget() const { return HPBarWidget; }

	UFUNCTION()
		void MoveResearch();
	
	FMoveDelegate MoveDelegate;
};
