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
	// �ʱ� Ÿ�� ����
	// �ӽ� ���� ��ġ; ?
	FVector Loc(2000.f);
	FRotator Rot = FRotator::ZeroRotator;
	// �� Ÿ�� ��? // Ÿ�� ���� ���� UI ������Ʈ
	uint8 MaxSlotCnt = TowerList.Num();
	for (int i = 0; i < MaxSlotCnt; i++)
	{
		UWidget_TowerUISlot* UIslot = CreateWidget<UWidget_TowerUISlot>(this, Widget_TowerUISlot.Get());
		// ���� ���� ����
		AActor* Towerinfo = GetWorld()->SpawnActor<AActor>(TowerList[i].Get(), Loc, Rot);
		if (Towerinfo)
		{
			UIslot->InitSlot(Towerinfo);
			ScrollBox_TowerList->AddChild(UIslot);
		}
	}
}

