// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_TowerUISlot.h"
#include "Engine/Engine.h"
#include "../Actor/Actor_Tower.h"
#include "../Actor/Actor_Tile.h"
#include "../Pawn_Default.h"

#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UWidget_TowerUISlot::NativeConstruct()
{
	Super::NativeConstruct();
		
	SetSize();

	Button_Slot->OnPressed.AddDynamic(this, &UWidget_TowerUISlot::ButtonPressedEvent);
	Button_Slot->OnReleased.AddDynamic(this, &UWidget_TowerUISlot::ButtonReleasedEvent);
}
void UWidget_TowerUISlot::SetSize(FVector2D size  /*X = Width , Y = Height*/)
{
	SizeBox_Slot->SetWidthOverride(size.X);
	SizeBox_Slot->SetHeightOverride(size.Y);
}
void UWidget_TowerUISlot::SetImage(UTexture2D* image)
{
	if(image)
		Image_Slot->SetBrushFromTexture(image);
}
void UWidget_TowerUISlot::SetName(FString name)
{
	TextBlock_Slot->SetText(FText::FromString(name));
}
// Button Init
void UWidget_TowerUISlot::InitSlot(UTexture2D* image, FString name)
{
	SetImage(image);
	SetName(name);
}
// Button Init
void UWidget_TowerUISlot::InitSlot(AActor* Actortower)
{
	// ���� ���Կ� ���� Ÿ�� ����;
	CurrantTowerInfo = Cast<AActor_Tower>(Actortower);
	if (CurrantTowerInfo)
	{
		// ������  , �̸�
		SetImage(CurrantTowerInfo->Towerimage);
		SetName(CurrantTowerInfo->TowerName);
		//CurrantTowerInfo->SlotWidget = this;
	}
}
// Tower Slot 
void UWidget_TowerUISlot::ButtonPressedEvent()
{
	Button_Slot->SetIsEnabled(false);
}
void UWidget_TowerUISlot::ButtonReleasedEvent()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Tower Select ClickedEvent");
	// Ÿ������ ? Actor_Tile > ETowerState ���� �ѱ��? // 
	if (CurrantTowerInfo)
	{
		APawn_Default* Pawn = Cast<APawn_Default>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Pawn)
		{
			// �÷��̾� ���� �� ���� Ÿ�� Ÿ�� ����
			if (Pawn->CheckTile->SetTower(CurrantTowerInfo))
			{
				SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
	Button_Slot->SetIsEnabled(true);
}


