// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Login.h"
#include "Engine/Engine.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"

void UWidget_Login::NativeConstruct()
{
	Super::NativeConstruct();
	
	// �α��� ��ư 
	VerticalBox_LoginButton->SetVisibility(ESlateVisibility::Visible);
	Button_Login->OnClicked.AddDynamic(this, &UWidget_Login::LoginEvent);
	Button_Cancel->OnClicked.AddDynamic(this, &UWidget_Login::CancelEvent);

	// �α��� �� ��ư
	VerticalBox_LoginBox->SetVisibility(ESlateVisibility::Collapsed);
	Button_Single->OnClicked.AddDynamic(this, &UWidget_Login::SoloEvent);
	Button_Multi1->OnClicked.AddDynamic(this, &UWidget_Login::MultiEvent);
	Button_Edit1->OnClicked.AddDynamic(this, &UWidget_Login::EditEvent);

}

void UWidget_Login::LoginEvent()
{
	FText ID = EditableText_ID->GetText();
	FText PW = EditableText_PW->GetText();
	
	// ID , PW ó�� ���� 
	//if (ID == ) if (PW == )
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "ID : " + ID.ToString() + "// PW : " + PW.ToString());

	VerticalBox_LoginButton->SetVisibility(ESlateVisibility::Collapsed);
	VerticalBox_LoginBox->SetVisibility(ESlateVisibility::Visible);

}
void UWidget_Login::CancelEvent()
{
	// ���� ������
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("Exit");
}
// �ΰ��� ���� ó�� 
void UWidget_Login::SoloEvent()
{
	// �� �������;	
	SingleAndMultiToggle(true);
}
void UWidget_Login::MultiEvent()
{
	// 
	SingleAndMultiToggle(false);
}
void UWidget_Login::EditEvent()
{
	// OpenLevel;
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("Open EditMap");
}
// ��ư �̱�&��Ƽ ��ȯ
void UWidget_Login::SingleAndMultiToggle(bool IsSingleGame)
{
	if (bSingleGame == IsSingleGame)
		return;

	bSingleGame = IsSingleGame;
	if (bSingleGame)
		SingleGame();
	else
		MultiGame();
}
void UWidget_Login::SingleGame()
{
	// ��ư ����
	Button_Single->SetVisibility(ESlateVisibility::Collapsed);
	Button_Multi1->SetVisibility(ESlateVisibility::Visible);
	Button_Edit1->SetVisibility(ESlateVisibility::Visible);

}
void UWidget_Login::MultiGame()
{
	// ��ư ����
	Button_Single->SetVisibility(ESlateVisibility::Visible);
	Button_Multi1->SetVisibility(ESlateVisibility::Collapsed);
	Button_Edit1->SetVisibility(ESlateVisibility::Visible);
}