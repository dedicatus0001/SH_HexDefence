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
	// 상속 루트
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_SelectMap;
	// 셀렉트 슬롯 버튼 클래스 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> SelectButton;
	// 생성 맵 정보 // TArray.Num() 총 개수;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMapSelect> SelectMap;


protected:
	virtual void NativeConstruct() override;

};
