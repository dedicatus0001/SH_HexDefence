// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SH_SaveGame.generated.h"

USTRUCT()
struct FSaveTileData
{
	GENERATED_USTRUCT_BODY()
	// Ÿ�� ���� 
	UPROPERTY()
		bool bObstacle = false;
	UPROPERTY()
		bool bWall = false;
	UPROPERTY()
		bool bStart = false;
	UPROPERTY()
		bool bEnd = false;
};
USTRUCT()
struct FSaveMapData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float SlotNum;
	UPROPERTY()
		uint8 MapWidth;
	UPROPERTY()
		uint8 MapHeight;
	// Ÿ������; 
	// Max = MapWidth * Height;
	UPROPERTY()
		TArray<FSaveTileData> TileMap;
	// TileMap.SetNum(Max);

};

UCLASS()
class SH_NEWGAME_API USH_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// Ÿ�� �� ���̺� ������
	UPROPERTY()
		FSaveMapData SaveData;

};
