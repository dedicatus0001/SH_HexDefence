// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_IngameEdit.h"
#include "Engine/Engine.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/VerticalBox.h"
#include "Widget_MonsterTimer.h"

#include "../SH_PlayerController.h"
#include "../SH_GameModeBase.h"
#include "../Widget/Widget_Button.h"
#include "../Widget/Widget_TowerUI.h"
#include "../Widget/Widget_SaveEditMap.h"
#include "../Actor/Actor_Tile.h"
#include "../Pawn_Default.h"

void UWidget_IngameEdit::NativeConstruct()
{
	Super::NativeConstruct();

	SetWidgetVisibility(ESlateVisibility::Collapsed);

	PC = Cast<ASH_PlayerController>(GetWorld()->GetFirstPlayerController());
	GM = Cast<ASH_GameModeBase>(GetWorld()->GetAuthGameMode());

	Button_Obstacle->ButtonClieckEvent.BindUFunction(this, "SetObstacle");
	Button_Wall->ButtonClieckEvent.BindUFunction(this, "SetWall");
	Button_Start->ButtonClieckEvent.BindUFunction(this, "SetStartTile");
	Button_End->ButtonClieckEvent.BindUFunction(this, "SetEndTile");
	// 게임 스타트 함수
	Button_MonsterSpawn->OnClicked.AddDynamic(this, &UWidget_IngameEdit::GameStart);
	TextBlock_MonsterSpawn->SetText(FText::FromString("Game Start"));
	// 타워 설정 UI
	Widget_TowerListUI->SetVisibility(ESlateVisibility::Collapsed);
	// 맵 생성
	Button_CreateMap->OnClicked.AddDynamic(this , &UWidget_IngameEdit::CreateMapEvent);
	EditableText_Width->OnTextChanged.AddDynamic(this , &UWidget_IngameEdit::ChangedTextEvent);
	EditableText_Height->OnTextChanged.AddDynamic(this, &UWidget_IngameEdit::ChangedTextEvent);
	VerticalBox_TileSelect->SetVisibility(ESlateVisibility::Collapsed);
	// 맵 세이브
	Button_SaveAndLoadMap->OnClicked.AddDynamic(this, &UWidget_IngameEdit::SaveAndLoadEditMapEvent);
	Widget_SaveEditMap->SetVisibility(ESlateVisibility::Collapsed);
}
UUserWidget* UWidget_IngameEdit::GetTowerListUI() const
{
	return Widget_TowerListUI;
}
void UWidget_IngameEdit::WidgetUpdate(AActor_Tile* CheckTile)
{
	if (CheckTile->IsValidLowLevel())
	{	
		WidgetTileinfo = CheckTile;
		SetWidgetVisibility(ESlateVisibility::Visible);
		FString str = "TileName : " + CheckTile->GetName();
		TextBlock_TileName->SetText(FText::FromString(str));
		// 
		ButtonWidgetUpdate();
	}
	else
	{
		SetWidgetVisibility(ESlateVisibility::Collapsed);
		TextBlock_TileName->SetText(FText::FromString("TileName : None"));
	}
}
void UWidget_IngameEdit::ButtonWidgetUpdate()
{
	if (WidgetTileinfo->IsValidLowLevel())
	{
		Button_Obstacle->SetTileCheck(WidgetTileinfo->TileState.bObstacle);
		Button_Wall->SetTileCheck(WidgetTileinfo->TileState.bWall);
		Button_Start->SetTileCheck(WidgetTileinfo->TileState.bStart);
		Button_End->SetTileCheck(WidgetTileinfo->TileState.bEnd);
	}
}
void UWidget_IngameEdit::SetWidgetVisibility(ESlateVisibility buttonvisibility)
{
	// 
	Button_Obstacle->SetVisibility(buttonvisibility);
	Button_Wall->SetVisibility(buttonvisibility);
	Button_Start->SetVisibility(buttonvisibility);
	Button_End->SetVisibility(buttonvisibility);

}
// 2
void UWidget_IngameEdit::SetObstacle()
{
	if (WidgetTileinfo->TileState.bStart || WidgetTileinfo->TileState.bEnd)
		return;
	if (WidgetTileinfo->TileState.bObstacle)
	{
		// 이미 타워가 있을때 , 타워 정보 출력

		return;
	}

	if (WidgetTileinfo->TileState.bWall)
	{
		WidgetTileinfo->SetTileState(FStateTile::ObstacleTile);
		ButtonWidgetUpdate();
		// 타워 목록 UI;
		Widget_TowerListUI->SetVisibility(ESlateVisibility::Visible);
		// 타워 설치 -> Widget_TowerListUI 이벤트 처리;
	}
}
// 1
void UWidget_IngameEdit::SetWall()
{
	Widget_TowerListUI->SetVisibility(ESlateVisibility::Collapsed);
	if (WidgetTileinfo->TileState.bStart || WidgetTileinfo->TileState.bEnd)
		return;

	WidgetTileinfo->SetTileState(FStateTile::WallTile);
	ButtonWidgetUpdate();
}
// 3
void UWidget_IngameEdit::SetStartTile()
{
	Widget_TowerListUI->SetVisibility(ESlateVisibility::Collapsed);
	if (!WidgetTileinfo)
		return;
	
	bool bState = WidgetTileinfo->SetTileState(FStateTile::StartTile);
	ButtonWidgetUpdate();
	if (GM->StartTile && WidgetTileinfo != GM->StartTile)
	{
		GM->StartTile->SetTileState(FStateTile::StartTile);
	}
	if (bState)
		GM->StartTile = WidgetTileinfo;
	else
		GM->StartTile = nullptr;
}
// 4
void UWidget_IngameEdit::SetEndTile()
{
	Widget_TowerListUI->SetVisibility(ESlateVisibility::Collapsed);
	if (!WidgetTileinfo)
		return;

	bool bEnd = WidgetTileinfo->SetTileState(FStateTile::EndTile);
	ButtonWidgetUpdate();

	if (GM->EndTile && GM->EndTile != WidgetTileinfo)
	{
		if (GM->EndTile)
			GM->EndTile->SetTileState(FStateTile::EndTile);
	}

	if(bEnd)
		GM->EndTile = WidgetTileinfo;
	else
		GM->EndTile = nullptr;
}
void UWidget_IngameEdit::GameStart()
{
	Widget_TowerListUI->SetVisibility(ESlateVisibility::Collapsed);

	if (bTogle)
	{
		// 스폰 타임 설정 
		PC->MonsterSpawnTimer(2.f);

		Widget_MonsterTimer->TimerStart(GM->MonsterDefense);
		Widget_MonsterTimer->SetLife(GM->MonsterDefenseLife);
		TextBlock_MonsterSpawn->SetText(FText::FromString("Game End"));
		bTogle = false;
	}
	else
	{
		Widget_MonsterTimer->TimerEnd();
		Widget_MonsterTimer->SetLife(0);
		TextBlock_MonsterSpawn->SetText(FText::FromString("Game Start"));
		bTogle = true;
	}
}

void UWidget_IngameEdit::MonsterCntUpdate(bool bCntIncease)
{
	if(bCntIncease)
		Widget_MonsterTimer->CurrantCntPlus();
	else
		Widget_MonsterTimer->CurrantCntMinus();
}
void UWidget_IngameEdit::LifeCntUpdate(bool bCntDecease)
{
	if (bCntDecease)
		Widget_MonsterTimer->LifeDecrease();
	else
		Widget_MonsterTimer->LifeIncrease();
}
/** 맵 생성 */
void UWidget_IngameEdit::CreateMapEvent()
{
	if (!EditableText_Width->GetText().IsEmpty() && !EditableText_Height->GetText().IsEmpty())
	{
		int32 width = FCString::Atoi(*EditableText_Width->GetText().ToString());
		int32 height = FCString::Atoi(*EditableText_Height->GetText().ToString());
		if (GM->HexMap_Width == width && GM->HexMap_Height == height)
			return;

		GM->HexMap_Width = width;
		GM->HexMap_Height = height;
	}
	if (GM->HexMap_Width == 0 || GM->HexMap_Height == 0)
		return;

	// 재 생성 기능 필요 // 기존 타일 삭제? 
	GM->CreateMap();
	VerticalBox_TileSelect->SetVisibility(ESlateVisibility::Visible);
	// 캐릭터 위치 설정 // Y
	float YDist = FVector::Dist(GM->Tile[0]->GetActorLocation(), GM->Tile[GM->HexMap_Width - 1]->GetActorLocation());
	// 캐릭터 위치 설정 // X
	float XDist = FVector::Dist(GM->Tile[GM->HexMap_Width - 1]->GetActorLocation(), GM->Tile.Last()->GetActorLocation());
	FVector Loc = GM->Tile[0]->GetActorLocation();
	FVector CameraLoc = FVector(Loc.X, Loc.Y + YDist / 2, Loc.Z + XDist * 1.2f); //  
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(CameraLoc);
	// 카메라 방향
	FVector vCameraView = (GM->Tile[0]->GetActorLocation() + GM->Tile.Last()->GetActorLocation()) / 2;
	// 밑변
	float fBottom = FVector::Dist(FVector(Loc.X, Loc.Y + YDist / 2, 0), FVector(Loc.X - XDist, Loc.Y + YDist / 2, 0));
	// 높이 
	float fHeight = XDist * 1.2f;
	float fDegree = -atan(fHeight / fBottom) * 180 / PI;
	// float at = atan();
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(-70, 180, 0));
	
	// 0.5sec 딜레이 // 맵 생성 오류 방지
	Button_CreateMap->SetIsEnabled(false);
	FTimerHandle CreateMapDelay;
	GetWorld()->GetTimerManager().SetTimer(CreateMapDelay, this, &UWidget_IngameEdit::CreateMapDelayEvent, 0.5f, false);

}
void UWidget_IngameEdit::ChangedTextEvent(const FText& Text)
{
	int32 NumText = FCString::Atoi(*Text.ToString());
	// 숫자만 입력 가능; // 가로,세로 128 이하
	if (NumText == 0 || NumText > 128)
	{
		EditableText_Width->SetText(FText());
		EditableText_Height->SetText(FText());
	}
}
void UWidget_IngameEdit::CreateMapDelayEvent()
{
	Button_CreateMap->SetIsEnabled(true);
}
void UWidget_IngameEdit::SaveAndLoadEditMapEvent()
{
	if (Widget_SaveEditMap->GetVisibility() == ESlateVisibility::Collapsed)
		Widget_SaveEditMap->SetVisibility(ESlateVisibility::Visible);
	else
		Widget_SaveEditMap->SetVisibility(ESlateVisibility::Collapsed);
}
