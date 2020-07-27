// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_HPBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_HPBar::NativeConstruct()
{
	Super::NativeConstruct();
	ProgressBar_HP->SetPercent(1);
}
void UWidget_HPBar::SetHP(float CurrentVal, float MaxVal)
{
	fCurrentHP = CurrentVal;
	fMaxHP = MaxVal;

	ProgressBar_HP->SetPercent(fCurrentHP / fMaxHP);
	FString str = FString::FromInt(fCurrentHP) + " / " + FString::FromInt(fMaxHP);
	TextBlock_HP->SetText(FText::FromString(str));
}
bool UWidget_HPBar::SetHPDecrease(float DecreaseHP)
{
	fCurrentHP -= DecreaseHP;
	if (fCurrentHP < 0.f)
		fCurrentHP = 0.f;
	ProgressBar_HP->SetPercent(fCurrentHP / fMaxHP);

	return fCurrentHP == 0.f ? true : false;
}
void UWidget_HPBar::SetHPIncrease(float IncreaseHP)
{
	fCurrentHP += IncreaseHP;
	if (fCurrentHP > fMaxHP)
		fCurrentHP = fMaxHP;
	ProgressBar_HP->SetPercent(fCurrentHP / fMaxHP);
}