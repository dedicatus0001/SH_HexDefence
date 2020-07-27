// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../SaveGame/SH_SaveGame.h"
#include "Widget_SaveEditMapSlot.generated.h"

class UTextBlock;
class UButton;
class USaveGame;

UCLASS()
class SH_NEWGAME_API UWidget_SaveEditMapSlot : public UUserWidget
{
	GENERATED_BODY()
	// 세이브 위젯 맵 데이터 슬롯 처리 부분 클래스
public:
	// 데이터 저장 처리 방법
	UFUNCTION()
		void SetSaveSlot();
	UFUNCTION()
		void SetLoadSlot();

	void InitLoadSlotData(FSaveMapData Newdata);
	void LastSaveSlot();
	// 슬롯 번호
	uint8 SlotNum;
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_SlotNum;
	// 로드 버튼
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_LoadInfo;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Load;
	// 세이브 버튼
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Save;
	// 슬롯 이름 + 번호
	FString SaveSlotName;
	USaveGame* SaveObject;
	// 맵 정보 
	FSaveMapData SaveMapData;

};
