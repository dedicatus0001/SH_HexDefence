// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AActor_Tile;

class SH_NEWGAME_API SH_MapSearch
{
public:
	SH_MapSearch() {};
	~SH_MapSearch() {};

public:
	bool AStar(AActor_Tile* start, AActor_Tile* end);

	void NeighborSearch(TArray<AActor_Tile*> ST);
	bool AStarMapSearch(AActor_Tile* TempStartTile, AActor_Tile* TempEndTile);
	void MapSearchTileCheck(AActor_Tile* TempEndTile);
	void MapSearch();

	TArray<AActor_Tile*> SearchTile;
	// ���� ���� // 
	AActor_Tile* CurrantTile = nullptr;
	// Ž�� ���� // 1~3�� // 2�� �׽�Ʈ
	AActor_Tile* EndTile = nullptr;

protected:
	TArray<AActor_Tile*> OpenList;
	TArray<AActor_Tile*> CloseList;

};
