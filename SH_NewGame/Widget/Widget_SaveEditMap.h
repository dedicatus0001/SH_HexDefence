// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SaveEditMap.generated.h"

class UVerticalBox;
class UWidget_SaveEditMapSlot;

UCLASS()
class SH_NEWGAME_API UWidget_SaveEditMap : public UUserWidget
{
	GENERATED_BODY()
	// 세이브 슬롯 관리 위젯
public:
	// 초기화 // BeginPlay()
	virtual void NativeConstruct() override;

	// 사용 하고자 하는 위젯 정보 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		TSubclassOf<UWidget_SaveEditMapSlot> SaveSlotWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		uint8 MaxSlotCnt = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		FString SlotName = "Test";
	// 초기화 방법 설정 // Init SaveData Load 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		bool bLoadSelect = true;
protected:
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_SaveSlot;
	// 테스트 슬롯 넘버 // 시작  = 0;
	uint8 SlotNum = 0;
	// 초기 저장된 맵 읽기 
	void InitLoadEditMap();
	void InitSaveSlotMap();
};
