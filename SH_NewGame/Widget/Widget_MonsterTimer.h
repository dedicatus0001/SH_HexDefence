// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MonsterTimer.generated.h"

class UHorizontalBox;
class USizeBox;
class UTextBlock;

UCLASS()
class SH_NEWGAME_API UWidget_MonsterTimer : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* HorizontalBox_Timer;

	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBox_CurrantCnt;
	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBox_MaxCnt;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_CurrantCnt;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_MaxCnt;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Life;

	void TimerStart(UINT Max);
	void TimerEnd();
	void SetLife(UINT life);
	void CurrantCntPlus();
	void CurrantCntMinus();
	void LifeIncrease();
	void LifeDecrease();

	UINT GetLife() const;
	UINT MaxMonsterCnt = 0;
	UINT CurrantMonsterCnt = 0;

protected:
	virtual void NativeConstruct() override;

	UINT Life;

};
