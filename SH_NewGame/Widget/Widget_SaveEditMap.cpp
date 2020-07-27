// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SaveEditMap.h"
#include "Widget_SaveEditMapSlot.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "../SaveGame/SH_SaveGame.h"
#include "Engine/Engine.h"

void UWidget_SaveEditMap::NativeConstruct()
{
	Super::NativeConstruct();
	if (bLoadSelect)
		// ������ ������ �̸� �����ϴ� ���
		InitSaveSlotMap();
	else
		// ����� ���� �а� ���ο� ���� ���� �߰� �ϱ�
		InitLoadEditMap();
}
void UWidget_SaveEditMap::InitLoadEditMap()
{
	while (true)
	{
		FString str = SlotName + FString::FromInt(SlotNum);
		// ���� ���� 
		UWidget_SaveEditMapSlot* NewSlot = CreateWidget<UWidget_SaveEditMapSlot>(this, SaveSlotWidget);
		if (NewSlot)
		{
			NewSlot->SlotNum = SlotNum;
			VerticalBox_SaveSlot->AddChild(NewSlot);
		}
		else
		{
			// ���� ���� ����
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Create Slot  Fail : NULL");
			return;
		}
		// ���� ó�� //�ε� ������ 
		USaveGame* LoadData = UGameplayStatics::LoadGameFromSlot(str, 0);
		if (LoadData->IsValidLowLevel())
		{
			USH_SaveGame* NewLoadData = Cast<USH_SaveGame>(LoadData);
			if (NewLoadData)
			{
				NewSlot->InitLoadSlotData(NewLoadData->SaveData);
			}
			SlotNum++;
		}
		else
		{
			NewSlot->LastSaveSlot();
			break;
		}
	}
}
void UWidget_SaveEditMap::InitSaveSlotMap()
{
	for (int i = 0; i < MaxSlotCnt; i++)
	{
		FString str = SlotName + FString::FromInt(i); // SlotNum
		// ���� ���� 
		UWidget_SaveEditMapSlot* NewSlot = CreateWidget<UWidget_SaveEditMapSlot>(this, SaveSlotWidget);
		if (NewSlot)
		{
			NewSlot->SlotNum = i;
			VerticalBox_SaveSlot->AddChild(NewSlot);
		}
		// ���� ó�� //�ε� ������ 
		USaveGame* LoadData = UGameplayStatics::LoadGameFromSlot(str, 0);
		if (LoadData->IsValidLowLevel())
		{
			USH_SaveGame* NewLoadData = Cast<USH_SaveGame>(LoadData);
			if (NewLoadData)
			{
				NewSlot->InitLoadSlotData(NewLoadData->SaveData);
			}
		}
		else
		{
			NewSlot->LastSaveSlot();
		}
	}
}