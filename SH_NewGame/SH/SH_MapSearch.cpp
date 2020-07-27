// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_MapSearch.h"
#include "Engine/Engine.h"
#include "../Actor/Actor_Tile.h"

// �̿� Ÿ�� Ž�� 
bool SH_MapSearch::AStar(AActor_Tile* start, AActor_Tile* end)
{
	if (start == end)
		return true;

	// test // OpenList Ÿ�� ǥ�� �ʱ�ȭ // 
	for (auto it : OpenList)
	{
		it->ChangeColor(FColor::Blue);
	}

	int Cnt = OpenList.Find(start);
	if (Cnt >= 0)
		OpenList.RemoveAt(Cnt);

	CloseList.Add(start);
	for (auto it : start->BorderTile)
	{
		if (it->IsValidLowLevel())
		{
			if (CloseList.Find(it) != INDEX_NONE || it->TileState.bWall)
				continue;

			if (OpenList.Find(it) == INDEX_NONE)
			{
				// Not List
				it->TotalDistance = start->TotalDistance + 1;
				it->ParantTile = start;
			}
			else
			{
				if (it->TotalDistance > start->TotalDistance + 1)
				{
					it->TotalDistance = start->TotalDistance + 1;
					it->ParantTile = start;
				}
				else
				{
					// 
				}
				continue;
			}
			OpenList.Add(it);
		}
	}
	// test // OpenList Ÿ�� ǥ�� // �����
	for (auto it : OpenList)
	{
		it->ChangeColor(FColor::Yellow);
	}
	return false;
}
// �̿� ��� Ž��
void SH_MapSearch::NeighborSearch(TArray<AActor_Tile*> ST)
{
	for (int i = 0; i < ST.Num(); i++)
	{
		if (ST[i]->IsValidLowLevel())
		{
			// TArray<AActor_Tile*> SearchTile;
			// SearchTile.AddUnique(,);
		}
	}
}
// Ÿ�� �� Ž��
bool SH_MapSearch::AStarMapSearch(AActor_Tile* TempStartTile, AActor_Tile* TempEndTile)
{
	if (!TempStartTile && !TempEndTile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "End Return : True");
		return true;
	}
	if (OpenList.Num() > 0)
	{
		// distance check
		AActor_Tile* NewTile = nullptr;
		float CheckDist = 9999;
		// OpenList, EndTile �Ÿ� ��
		for (auto it : OpenList)
		{
			float distance = FVector::Dist(it->GetActorLocation(), TempEndTile->GetActorLocation());
			if (CheckDist > distance)
			{
				CheckDist = distance;
				NewTile = it;
			}
		}
		if (NewTile->IsValidLowLevel())
			return AStar(NewTile, TempEndTile);
	}
	else
	{
		AStar(TempStartTile, TempEndTile);
	}
	return false;
}
// �ִܰŸ� ���� ǥ�� FColor::Cyan
void SH_MapSearch::MapSearchTileCheck(AActor_Tile* TempEndTile)
{
	if (!TempEndTile->IsValidLowLevel())
		return;

	AActor_Tile* EndTileCheck = TempEndTile;
	EndTileCheck->ChangeColor(FColor::Cyan);

	int Cnt = 0;
	while (true)
	{
		if (EndTileCheck->IsValidLowLevel())
		{
			//SearchTile.Add(EndTileCheck);
			SearchTile.Insert(EndTileCheck, 0);
			if (!EndTileCheck->ParantTile->IsValidLowLevel())
				break;

			EndTileCheck = EndTileCheck->ParantTile;
			EndTileCheck->ChangeColor(FColor::Cyan);
		}
		Cnt++;
		if (Cnt > 50) // ���ѷ��� �߻� üũ
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MapSearch Tile Check  : False");
			return;
		}
	}
}
void SH_MapSearch::MapSearch()
{
	// �� Ž�� ���� ����
	for (auto it : OpenList)
	{
		it->ParantTile = nullptr;
	}
	OpenList.Reset();
	for (auto it : CloseList)
	{
		it->ParantTile = nullptr;
	}
	CloseList.Reset();
	SearchTile.Reset();
	// �� Ž��
	int Cnt = 0;
	while (true)
	{
		Cnt++;
		if (AStarMapSearch(CurrantTile, EndTile))
		{
			MapSearchTileCheck(EndTile);
			return;
		}
		if (Cnt > 50) // ���� ���� Ž��
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MapSearch : Overflow");
			return;
		}
	}
}