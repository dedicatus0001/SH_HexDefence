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
	// �� ���� // ���ο� ���� ��� ã��
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

	// ���� ���� // 
	AActor_Tile* StartTile = nullptr;
	// Ž�� ���� // 1~3�� // 2�� �׽�Ʈ
	AActor_Tile* EndTile = nullptr;
	// �� ������
	TArray<AActor_Tile*> Tile;
	TArray<AActor_Tile*> SearchTile;
	// ���� ���潺 , ������;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 MonsterDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 MonsterDefenseLife;
};
