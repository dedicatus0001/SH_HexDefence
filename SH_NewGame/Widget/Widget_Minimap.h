// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Minimap.generated.h"

/**
 * 
 */
UCLASS()
class SH_NEWGAME_API UWidget_Minimap : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Minimap;

protected:
	virtual void NativeConstruct() override;


};
