// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_TowerUI.generated.h"

class UHorizontalBox;
class UScrollBox;
class UWidget_TowerUISlot;

UCLASS()
class SH_NEWGAME_API UWidget_TowerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* HorizontalBox_TowerList;
	UPROPERTY(meta = (BindWidget))
		UScrollBox* ScrollBox_TowerList;

	// TowerUI Slot Setting ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UWidget_TowerUISlot> Widget_TowerUISlot;
	// Tower List Array // Add Blueprint Widget 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> TowerList;

protected:
	virtual void NativeConstruct() override;
};
