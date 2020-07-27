// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_LoginPlayerController.h"
#include "Widget/Widget_MainLogin.h"


void ASH_LoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	// �α��� ȭ��  
	if (FindLoginUI)
	{
		LoginUI = CreateWidget<UWidget_MainLogin>(this, FindLoginUI.Get());
		if (LoginUI)
		{
			LoginUI->AddToViewport();
		}
	}
}
