// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_MainLogin.h"
#include "Widget_Login.h"
#include "Widget_MapSelect.h"
#include "Components/Button.h"
#include "Engine/Engine.h"

void UWidget_MainLogin::NativeConstruct()
{
	Super::NativeConstruct();

	Widget_MapList->SetVisibility(ESlateVisibility::Collapsed);
	LoginWidget->SetVisibility(ESlateVisibility::Visible);

	LoginWidget;
}

void UWidget_MainLogin::StartSingleGame_Implementation()
{

	
}

void UWidget_MainLogin::SingleGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "SingleGame kmwfkmwkf");

}
