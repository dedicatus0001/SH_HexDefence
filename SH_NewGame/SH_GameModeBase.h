// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SH_GameModeBase.generated.h"

class AActor_Tile;

UCLASS()
class SH_NEWGAME_API ASH_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	FRandomStream RandomStream;

	TArray<AActor_Tile*> OpenList;
	TArray<AActor_Tile*> CloseList;

public:
	// 맵 생성 // 새로운 생성 방법 찾기
	void CreateMap();
	bool AStar(AActor_Tile* start, AActor_Tile* end);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 HexMap_Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 HexMap_Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float XOffset = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float YOffset = 10.f;

	// 시작 지점 // 
	AActor_Tile* StartTile = nullptr;
	// 탐색 지점 // 1~3개 // 2개 테스트
	AActor_Tile* EndTile = nullptr;
	// 맵 데이터
	TArray<AActor_Tile*> Tile;
	TArray<AActor_Tile*> SearchTile;
	// 몬스터 디펜스 , 라이프;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 MonsterDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 MonsterDefenseLife;
};
