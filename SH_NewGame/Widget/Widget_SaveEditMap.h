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
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		TSubclassOf<UWidget_SaveEditMapSlot> SaveSlotWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		uint8 MaxSlotCnt = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		FString SlotName = "Test";
	// Init SaveData Load 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveEdit")
		bool bLoadSelect = true;
protected:
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_SaveSlot;
	// �׽�Ʈ ���� �ѹ� // ����  = 0;
	uint8 SlotNum = 0;
	// �ʱ� ����� �� �б�
	void InitLoadEditMap();
	void InitSaveSlotMap();
};
