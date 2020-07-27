// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HPBar.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class SH_NEWGAME_API UWidget_HPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHP(float CurrentVal , float MaxVal);
	bool SetHPDecrease(float DecreaseHP = 1.f);
	void SetHPIncrease(float IncreaseHP);
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* ProgressBar_HP;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_HP;

	float fCurrentHP;
	float fMaxHP;
};
