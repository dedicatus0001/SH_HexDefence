// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MapSelect.generated.h"

class UWidget_MapSelectButton;
class UTexture2D;
class UVerticalBox;

USTRUCT(BlueprintType)
struct FMapSelect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MapName = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* MapButtonImage;

};

UCLASS()
class SH_NEWGAME_API UWidget_MapSelect : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ��� ��Ʈ
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_SelectMap;
	// ����Ʈ ���� ��ư Ŭ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> SelectButton;
	// ���� �� ���� // TArray.Num() �� ����;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMapSelect> SelectMap;


protected:
	virtual void NativeConstruct() override;

};
