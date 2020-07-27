// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Button.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UWidget_Button::NativeConstruct()
{
	Super::NativeConstruct();

	Button_IngameEdit->OnClicked.AddDynamic(this , &UWidget_Button::ButtonClickedEvent);

}

void UWidget_Button::ButtonClickedEvent()
{
	SetTileCheck(!ButtonCheck);
	ButtonClieckEvent.ExecuteIfBound();
}


void UWidget_Button::SetTileCheck(bool bTilecheck)
{
	ButtonCheck = bTilecheck;
	if (ButtonCheck)
	{
		TextBlock_IngameEdit->SetText(FText::FromName("YES"));
		TextBlock_IngameEdit->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
	}
	else
	{
		TextBlock_IngameEdit->SetText(FText::FromName("NO"));
		TextBlock_IngameEdit->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	}
}