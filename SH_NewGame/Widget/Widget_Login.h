// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Interface/SH_Interface.h"
#include "Widget_Login.generated.h"

class UEditableText;
class UVerticalBox;
class UButton;

UCLASS()
class SH_NEWGAME_API UWidget_Login : public UUserWidget , public ISH_Interface
{
	GENERATED_BODY()
	
public:
	// 로그인 버튼 클릭시 //
	UPROPERTY(meta = (BindWidget))
		UEditableText* EditableText_ID;
	UPROPERTY(meta = (BindWidget))
		UEditableText* EditableText_PW;

	// Login Button 처리;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_LoginButton;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Login;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Cancel;

	// InGame Button 처리;	
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_LoginBox;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Single;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Multi1;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Edit1;
	
	// 싱글 게임  & 멀티 게임 전환;
	void SingleAndMultiToggle(bool IsSingleGame);
	void SingleGame();
	void MultiGame();

	// 이벤트 델리게이트;
	DECLARE_EVENT(UWidget_Login, FStartSingleGame);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void LoginEvent();
	UFUNCTION()
		void CancelEvent();
	UFUNCTION()
		void EditEvent();
	UFUNCTION()
		void SoloEvent();
	UFUNCTION()
		void MultiEvent();

	bool bSingleGame;

	FStartSingleGame StartSingleGame;

};
