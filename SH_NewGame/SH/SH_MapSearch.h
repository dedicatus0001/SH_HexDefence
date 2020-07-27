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
	// 시작 지점 // 
	AActor_Tile* CurrantTile = nullptr;
	// 탐색 지점 // 1~3개 // 2개 테스트
	AActor_Tile* EndTile = nullptr;

protected:
	TArray<AActor_Tile*> OpenList;
	TArray<AActor_Tile*> CloseList;

};
