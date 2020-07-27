// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MapSelectButton.generated.h"

class UTextBlock;
class UButton;
class UTexture2D;

UCLASS()
class SH_NEWGAME_API UWidget_MapSelectButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* Button_MapName;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* TextBlock_MapNameCnt;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* TextBlock_MapName;

	// TextBlock_MapNameCnt 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MapNameCnt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ButtonTexture;

protected:
	virtual void NativeConstruct() override;

};
