// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Interface/SH_Interface.h"
#include "Widget_MainLogin.generated.h"

class UWidget_Login;
class UWidget_MapSelect;

UCLASS()
class SH_NEWGAME_API UWidget_MainLogin : public UUserWidget , public ISH_Interface
{
	GENERATED_BODY()

public:


protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UWidget_Login* LoginWidget;
	UPROPERTY(meta = (BindWidget))
		UWidget_MapSelect* Widget_MapList;

	UFUNCTION(BlueprintNativeEvent)
		void StartSingleGame();
		virtual void StartSingleGame_Implementation();

		void SingleGame();
};
