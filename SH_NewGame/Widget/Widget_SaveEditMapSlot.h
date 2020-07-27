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
	// ���̺� ���� �� ������ ���� ó�� �κ� Ŭ����
public:
	// ������ ���� ó�� ���
	UFUNCTION()
		void SetSaveSlot();
	UFUNCTION()
		void SetLoadSlot();

	void InitLoadSlotData(FSaveMapData Newdata);
	void LastSaveSlot();
	// ���� ��ȣ
	uint8 SlotNum;
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_SlotNum;
	// �ε� ��ư
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_LoadInfo;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Load;
	// ���̺� ��ư
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Save;
	// ���� �̸� + ��ȣ
	FString SaveSlotName;
	USaveGame* SaveObject;
	// �� ���� 
	FSaveMapData SaveMapData;

};
