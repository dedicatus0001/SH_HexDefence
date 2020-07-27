// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_GameModeBase.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Actor/Actor_Tile.h"
#include "Actor/Actor_BoxFlag.h"

void ASH_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 게임 맵 생성 // 맵 생성 방법 ? 
	// CreateMap();
}

// 육각형 타일 맵 생성 // 사각형 height * width;
void ASH_GameModeBase::CreateMap()
{
	for (auto it : Tile)
	{
		it->Destroy();
	}
	Tile.Empty();

	FVector Loc = FVector(0, 0, 0);
	FRotator Rot = FRotator(0, 0, 0);

	int dir = 1;
	float fX = Loc.X;
	float fY = Loc.Y;
	float fRadius = (200.f + YOffset);
	float fHalfRadius = (200.f + YOffset) / 2;

	for (int i = 0; i < HexMap_Height; i++)
	{
		// 라인 : 홀수 1 , 짝수 -1
		dir *= -1;
		fY = Loc.Y;
		fY += fHalfRadius * ((dir * 0.5f) + 0.5f);
		fX = -(fHalfRadius)* sqrt(3) * i;

		for (int j = 0; j < HexMap_Width; j++)
		{
			// 줄 당 생성 타일
			float TempY = (fY + fRadius * j);
			AActor_Tile* newTile = GetWorld()->SpawnActor<AActor_Tile>(FVector(fX, TempY, Loc.Z), Rot);
			float TileNum = (HexMap_Width * i + j);
			newTile->TileNum = TileNum;

			// 1 <-> 4 // 2 <-> 5 // 3 <-> 0
			//  5  0
			// 4    1
			//  3  2

			// 이웃 타일 설정
			if (Tile.Num() != 0)
			{
				if (j != 0)
				{
					// ZeroRight , ZeroLeft 
					Tile[TileNum - 1]->BorderTile[1] = newTile;
					newTile->BorderTile[4] = Tile[TileNum - 1];
				}

				if (i != 0)
				{
					// 방향 계산 방식으로 변경 ?
					// TopRight , TopLeft
					if (dir > 0) // 홀
					{
						Tile[(HexMap_Width * (i - 1) + j)]->BorderTile[2] = newTile;
						newTile->BorderTile[5] = Tile[(HexMap_Width * (i - 1) + j)];
						newTile->BorderTile[0] = Tile[(HexMap_Width * (i - 1) + j)]->BorderTile[1];
						if (newTile->BorderTile[0]->IsValidLowLevel())
						{
							newTile->BorderTile[0]->BorderTile[3] = newTile;
						}
					}
					else //if (j != (width - 1)) // 짝
					{
						Tile[(HexMap_Width * (i - 1) + j)]->BorderTile[3] = newTile;
						newTile->BorderTile[0] = Tile[(HexMap_Width * (i - 1) + j)];
						newTile->BorderTile[5] = Tile[(HexMap_Width * (i - 1) + j)]->BorderTile[4];
						if (newTile->BorderTile[5]->IsValidLowLevel())
						{
							newTile->BorderTile[5]->BorderTile[2] = newTile;
						}
					}
				}
			}
			Tile.Add(newTile);
		}
	}
}
// 이웃 타일 탐색 
bool ASH_GameModeBase::AStar(AActor_Tile* start , AActor_Tile* end)
{
	if (start == end)
		return true;

	// test // OpenList 타일 표시 초기화
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
	// test // OpenList 타일 표시
	for (auto it : OpenList)
	{
		it->ChangeColor(FColor::Yellow);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::FromInt(OpenList.Num()));
	return false;
}
