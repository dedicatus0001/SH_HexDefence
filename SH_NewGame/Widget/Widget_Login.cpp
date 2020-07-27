// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Login.h"
#include "Engine/Engine.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"

void UWidget_Login::NativeConstruct()
{
	Super::NativeConstruct();
	
	// 로그인 버튼 
	VerticalBox_LoginButton->SetVisibility(ESlateVisibility::Visible);
	Button_Login->OnClicked.AddDynamic(this, &UWidget_Login::LoginEvent);
	Button_Cancel->OnClicked.AddDynamic(this, &UWidget_Login::CancelEvent);

	// 로그인 후 버튼
	VerticalBox_LoginBox->SetVisibility(ESlateVisibility::Collapsed);
	Button_Single->OnClicked.AddDynamic(this, &UWidget_Login::SoloEvent);
	Button_Multi1->OnClicked.AddDynamic(this, &UWidget_Login::MultiEvent);
	Button_Edit1->OnClicked.AddDynamic(this, &UWidget_Login::EditEvent);

}

void UWidget_Login::LoginEvent()
{
	FText ID = EditableText_ID->GetText();
	FText PW = EditableText_PW->GetText();
	
	// ID , PW 처리 조건 
	//if (ID == ) if (PW == )
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "ID : " + ID.ToString() + "// PW : " + PW.ToString());

	VerticalBox_LoginButton->SetVisibility(ESlateVisibility::Collapsed);
	VerticalBox_LoginBox->SetVisibility(ESlateVisibility::Visible);

}
void UWidget_Login::CancelEvent()
{
	// 게임 나가기
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("Exit");
}
// 인게임 진행 처리 
void UWidget_Login::SoloEvent()
{
	// 맵 목록으로;	
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
// 버튼 싱글&멀티 전환
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
	// 버튼 설정
	Button_Single->SetVisibility(ESlateVisibility::Collapsed);
	Button_Multi1->SetVisibility(ESlateVisibility::Visible);
	Button_Edit1->SetVisibility(ESlateVisibility::Visible);

}
void UWidget_Login::MultiGame()
{
	// 버튼 설정
	Button_Single->SetVisibility(ESlateVisibility::Visible);
	Button_Multi1->SetVisibility(ESlateVisibility::Collapsed);
	Button_Edit1->SetVisibility(ESlateVisibility::Visible);
}