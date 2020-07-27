// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_MonsterTimer.h"
#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"


void UWidget_MonsterTimer::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_CurrantCnt->SetWidthOverride(100);
	SizeBox_MaxCnt->SetWidthOverride(100);

	SetVisibility(ESlateVisibility::Collapsed);

}

void UWidget_MonsterTimer::TimerStart(UINT Max)
{
	SetVisibility(ESlateVisibility::Visible);

	CurrantMonsterCnt = 0;
	MaxMonsterCnt = Max;
	TextBlock_CurrantCnt->SetText(FText::FromString(FString::FromInt(CurrantMonsterCnt)));
	TextBlock_MaxCnt->SetText(FText::FromString(FString::FromInt(MaxMonsterCnt)));
}

void UWidget_MonsterTimer::CurrantCntPlus()
{
	CurrantMonsterCnt++;
	// 몬스터 스폰시
	TextBlock_CurrantCnt->SetText(FText::FromString(FString::FromInt(CurrantMonsterCnt)));
	TextBlock_MaxCnt->SetText(FText::FromString(FString::FromInt(MaxMonsterCnt)));
}

void UWidget_MonsterTimer::CurrantCntMinus()
{
	CurrantMonsterCnt--;
	// 몬스터 스폰시
	TextBlock_CurrantCnt->SetText(FText::FromString(FString::FromInt(CurrantMonsterCnt)));
	TextBlock_MaxCnt->SetText(FText::FromString(FString::FromInt(MaxMonsterCnt)));
}

void UWidget_MonsterTimer::TimerEnd()
{
	SetVisibility(ESlateVisibility::Collapsed);

	MaxMonsterCnt = 0;
	CurrantMonsterCnt = 0;
	TextBlock_CurrantCnt->SetText(FText::FromString(FString::FromInt(CurrantMonsterCnt)));
	TextBlock_MaxCnt->SetText(FText::FromString(FString::FromInt(MaxMonsterCnt)));
}

void UWidget_MonsterTimer::SetLife(UINT life)
{
	Life = life;
	TextBlock_Life->SetText(FText::FromString(FString::FromInt(Life)));
}

UINT UWidget_MonsterTimer::GetLife() const
{
	// int32 iLife = FCString::Atoi(*TextBlock_Life->GetText().ToString());
	return Life;
}

void UWidget_MonsterTimer::LifeIncrease()
{
	Life++;
	TextBlock_Life->SetText(FText::FromString(FString::FromInt(Life)));
}

void UWidget_MonsterTimer::LifeDecrease()
{
	Life--;
	TextBlock_Life->SetText(FText::FromString(FString::FromInt(Life)));
}