// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_MapSelect.h"
#include "Widget_MapSelectButton.h"
#include "Components/VerticalBox.h"

void UWidget_MapSelect::NativeConstruct()
{
	Super::NativeConstruct();

	for (auto it : SelectMap)
	{
		UWidget_MapSelectButton* SubButton = CreateWidget<UWidget_MapSelectButton>(this, SelectButton.Get());

		if (it.MapName != "None")
		{
			SubButton->MapNameCnt = it.MapName;
		}
		if (it.MapButtonImage)
		{
			SubButton->ButtonTexture = it.MapButtonImage;
		}
		VerticalBox_SelectMap->AddChildToVerticalBox(SubButton);
	}

	// 맵 데이터 // 로드 게임 // 
	const UWorld* const world = GetWorld();

	if (world)
	{
		
	}



}
