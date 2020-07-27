// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_TowerUI.h"
#include "Widget_TowerUISlot.h"
#include "Engine/Engine.h"
#include "../SH_GameModeBase.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"

void UWidget_TowerUI::NativeConstruct()
{
	Super::NativeConstruct();
	ScrollBox_TowerList->SetOrientation(EOrientation::Orient_Horizontal);
	// 초기 타워 세팅
	// 임시 스폰 위치; ?
	FVector Loc(2000.f);
	FRotator Rot = FRotator::ZeroRotator;
	// 총 타워 수? // 타워 세팅 정보 UI 업데이트
	uint8 MaxSlotCnt = TowerList.Num();
	for (int i = 0; i < MaxSlotCnt; i++)
	{
		UWidget_TowerUISlot* UIslot = CreateWidget<UWidget_TowerUISlot>(this, Widget_TowerUISlot.Get());
		// 슬롯 정보 세팅
		AActor* Towerinfo = GetWorld()->SpawnActor<AActor>(TowerList[i].Get(), Loc, Rot);
		if (Towerinfo)
		{
			UIslot->InitSlot(Towerinfo);
			ScrollBox_TowerList->AddChild(UIslot);
		}
	}
}

