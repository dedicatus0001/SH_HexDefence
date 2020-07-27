// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_IngameEdit.generated.h"

class AActor_Tile;
class UButton;
class UTextBlock;
class UEditableText;
class UVerticalBox;
class UWidget_Button;
class ASH_PlayerController;
class ASH_GameModeBase;
class UWidget_MonsterTimer; // Ingame Top UI // Monster Cnt
class UWidget_TowerUI; // Tower List 
class UWidget_SaveEditMap; // ���̺� �ε� â

UCLASS()
class SH_NEWGAME_API UWidget_IngameEdit : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// �� ���� 
	UPROPERTY(meta = (BindWidget))
		UButton* Button_CreateMap;
	UPROPERTY(meta = (BindWidget))
		UEditableText* EditableText_Width;
	UPROPERTY(meta = (BindWidget))
		UEditableText* EditableText_Height;
	// Ÿ�� ����
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_TileSelect;
	UPROPERTY(meta = (BindWidget))
		UWidget_Button* Button_Obstacle;
	UPROPERTY(meta = (BindWidget))
		UWidget_Button* Button_Wall;
	UPROPERTY(meta = (BindWidget))
		UWidget_Button* Button_Start;
	UPROPERTY(meta = (BindWidget))
		UWidget_Button* Button_End;
	// ���� ���� // ���� ����
	UPROPERTY(meta = (BindWidget))
		UButton* Button_MonsterSpawn;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_MonsterSpawn;
	// ������ �� ���̺� & �ε� 
	UPROPERTY(meta = (BindWidget))
		UButton* Button_SaveAndLoadMap;
	UPROPERTY(meta = (BindWidget))
		UWidget_SaveEditMap* Widget_SaveEditMap;
	// ��� Ÿ�̸� UI
	UPROPERTY(meta = (BindWidget))
		UWidget_MonsterTimer* Widget_MonsterTimer;
	// �ϴ� Ÿ�� ��ġ ����Ʈ
	UPROPERTY(meta = (BindWidget))
		UWidget_TowerUI* Widget_TowerListUI;

	UUserWidget* GetTowerListUI() const;

	// CheckTile // ���� Ÿ�� 
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_TileName;
	
	void WidgetUpdate(AActor_Tile* CheckTile);
	void ButtonWidgetUpdate();
	
	AActor_Tile* WidgetTileinfo;
	// ���� UI ������Ʈ;
	void MonsterCntUpdate(bool bCntIncease = true);
	void LifeCntUpdate(bool bCntDecease = true);
	// object tile controller
	UFUNCTION()
		void SetObstacle();
	UFUNCTION()
		void SetWall();
	UFUNCTION()
		void SetStartTile();
	UFUNCTION()
		void SetEndTile();
	// �� ���� // �ε� & ����
	UFUNCTION()
		void CreateMapEvent();
protected:
	virtual void NativeConstruct() override;
	
	void SetWidgetVisibility(ESlateVisibility buttonvisibility);

	ASH_PlayerController* PC;
	ASH_GameModeBase* GM;

	bool bTogle = true;

	// ���� ���� // ���� ���� // 
	UFUNCTION()
		void GameStart();
	UFUNCTION()
		void ChangedTextEvent(const FText& Text);
	UFUNCTION()
		void CreateMapDelayEvent();
	UFUNCTION() // ������ �� ���̺�&�ε�
		void SaveAndLoadEditMapEvent();
};
