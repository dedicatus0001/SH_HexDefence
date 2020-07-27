// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Button.generated.h"

class UButton;
class UTextBlock;

DECLARE_DYNAMIC_DELEGATE(FButtonClieckEvent);

UCLASS()
class SH_NEWGAME_API UWidget_Button : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
		UButton* Button_IngameEdit;
	UPROPERTY(meta = (BindWidget), VisibleAnyWhere)
		UTextBlock* TextBlock_IngameEdit;

	void SetTileCheck(bool bTilecheck);

	bool ButtonCheck;

	UPROPERTY()
		FButtonClieckEvent ButtonClieckEvent;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void ButtonClickedEvent();
};
