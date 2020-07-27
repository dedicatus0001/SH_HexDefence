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
	// �α��� ��ư Ŭ���� //
	UPROPERTY(meta = (BindWidget))
		UEditableText* EditableText_ID;
	UPROPERTY(meta = (BindWidget))
		UEditableText* EditableText_PW;

	// Login Button ó��;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_LoginButton;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Login;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Cancel;

	// InGame Button ó��;	
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_LoginBox;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Single;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Multi1;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Edit1;
	
	// �̱� ����  & ��Ƽ ���� ��ȯ;
	void SingleAndMultiToggle(bool IsSingleGame);
	void SingleGame();
	void MultiGame();

	// �̺�Ʈ ��������Ʈ;
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
