// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_TowerUISlot.generated.h"

class USizeBox;
class UBorder;
class UImage;
class UButton;
class UTextBlock;
class AActor_Tower;

UCLASS()
class SH_NEWGAME_API UWidget_TowerUISlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBox_Slot;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_Slot;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Slot;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Slot;

	// slot �ʱⰪ
	void InitSlot(UTexture2D* image, FString name = "None");
	void InitSlot(AActor* Actortower);

protected:
	virtual void NativeConstruct() override;

	void SetSize(FVector2D size = FVector2D(125.f, 125.f) /*X = Width , Y = Height*/);
	void SetImage(UTexture2D* image);
	void SetName(FString name);

	AActor_Tower* CurrantTowerInfo;

	UFUNCTION()
		void ButtonReleasedEvent();
	UFUNCTION()
		void ButtonPressedEvent();
};
