// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SaveEditMapSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "../SH_GameModeBase.h"
#include "../SH_PlayerController.h"
#include "../Actor/Actor_Tile.h"
#include "../Widget/Widget_IngameEdit.h"
#include "Engine/Engine.h"

void UWidget_SaveEditMapSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Save->OnReleased.AddDynamic(this, &UWidget_SaveEditMapSlot::SetSaveSlot);
	Button_Load->OnReleased.AddDynamic(this, &UWidget_SaveEditMapSlot::SetLoadSlot);
	Button_Load->SetVisibility(ESlateVisibility::Hidden);
	// 슬롯 이름
	SaveSlotName = "Test" + FString::FromInt(SlotNum);

}
void UWidget_SaveEditMapSlot::SetSaveSlot()
{
	// 현재 슬롯 번호에 ..// 맵 데이터 저장
	SaveObject = UGameplayStatics::CreateSaveGameObject(USH_SaveGame::StaticClass());
	USH_SaveGame* NewGameSave = Cast<USH_SaveGame>(SaveObject);
	if (!NewGameSave)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "NewGameSave Object Cast Fail //////");
		return;
	}
	ASH_GameModeBase* GM = Cast<ASH_GameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		// 맵 데이터 
		FSaveMapData NewData;
		NewData.MapHeight = GM->HexMap_Height;
		NewData.MapWidth = GM->HexMap_Width;
		NewData.SlotNum = SlotNum;
		for (auto it : GM->Tile)
		{
			// 타일 정보
			NewData.TileMap.Add(it->TileState);
		}
		InitLoadSlotData(NewData);
		// 세이브 //  세이브 조건 처리; // 세이브시 확인 작업 
		NewGameSave->SaveData = NewData;
		UGameplayStatics::SaveGameToSlot(NewGameSave, SaveSlotName, 0);
	}
}
void UWidget_SaveEditMapSlot::SetLoadSlot()
{
	// 맵 데이터 불러오기
	USaveGame* LoadObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	if (LoadObject)
	{
		USH_SaveGame* NewGameLoad = Cast<USH_SaveGame>(LoadObject);
		if (NewGameLoad)
		{
			ASH_PlayerController* PC = Cast<ASH_PlayerController>(GetWorld()->GetFirstPlayerController());
			if (PC)
			{
				PC->GetIngameEditUI()->EditableText_Width->SetText(FText::FromString(FString::FromInt(NewGameLoad->SaveData.MapWidth)));
				PC->GetIngameEditUI()->EditableText_Height->SetText(FText::FromString(FString::FromInt(NewGameLoad->SaveData.MapHeight)));
				PC->GetIngameEditUI()->CreateMapEvent();
				ASH_GameModeBase* GM = Cast<ASH_GameModeBase>(GetWorld()->GetAuthGameMode());
				if (GM)
				{
					if (GM->Tile.Num() != NewGameLoad->SaveData.TileMap.Num())
					{
						GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Load Error : Map Num() Not Equal");
						return;
					}
					for (int i = 0; i < NewGameLoad->SaveData.TileMap.Num(); i++)
					{
						GM->Tile[i]->SetTileState(NewGameLoad->SaveData.TileMap[i]);
						if (NewGameLoad->SaveData.TileMap[i].bEnd == true)
							GM->StartTile = GM->Tile[i];
						if (NewGameLoad->SaveData.TileMap[i].bStart == true)
							GM->EndTile = GM->Tile[i];
					}
				}
			}
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Load Data : " + FString::FromInt(NewGameLoad->SaveData.MapHeight) + " // " + FString::FromInt(NewGameLoad->SaveData.MapWidth));
		}
	}
}
// 초기 슬롯 읽기
void UWidget_SaveEditMapSlot::InitLoadSlotData(FSaveMapData Newdata)
{
	Button_Load->SetVisibility(ESlateVisibility::Visible);
	// 슬롯 좌측 번호 
	SaveMapData = Newdata;
	TextBlock_SlotNum->SetText(FText::FromString(FString::FromInt(SlotNum) + " /"));
	FString str = "Width : " + FString::FromInt(SaveMapData.MapWidth) + "/ Height : " + FString::FromInt(SaveMapData.MapHeight);
	TextBlock_LoadInfo->SetText(FText::FromString(str));;
}
void UWidget_SaveEditMapSlot::LastSaveSlot()
{
	Button_Load->SetVisibility(ESlateVisibility::Hidden);
	TextBlock_SlotNum->SetText(FText::FromString(FString::FromInt(SlotNum) + " /"));
}