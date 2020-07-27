// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Tower.generated.h"

UENUM()
enum class ETowerState : uint8
{
	// 타워 이름 ? 종류
	Tower,
	TowerS,
};

class UCapsuleComponent;
class UTexture2D;
class AActor_Tile;
class UArrowComponent;

UCLASS()
class SH_NEWGAME_API AActor_Tower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Tower();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCapsuleComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UArrowComponent* ArrowComp; // 미사일 위치 지정
	// 타워 정보 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Towerinfo")
		UTexture2D* Towerimage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Towerinfo")
		FString TowerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Towerinfo")
		uint8 TowerDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Towerinfo")
		uint8 TowerHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Towerinfo")
		uint8 TowerSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Towerinfo")
		ETowerState TowerState;
	// 타워 위젯 정보
	// UUserWidget* SlotWidget;
	// UUserWidget* TowerWidget;

	AActor_Tile* CurrentTile = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void TowerAttack();
	void TowerAttack(AActor* Monster);
	void AttackEvent();
};
