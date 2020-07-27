// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Default.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "interface/SH_Interface.h"
#include "Actor/Actor_Tile.h"
#include "Widget/Widget_IngameEdit.h"
#include "Components/InputComponent.h"

#include "SH_PlayerController.h"
#include "SH_GameModeBase.h"


// Sets default values
APawn_Default::APawn_Default()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Map Load

}

// Called when the game starts or when spawned
void APawn_Default::BeginPlay()
{
	Super::BeginPlay();
	
	PC = Cast<ASH_PlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void APawn_Default::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawn_Default::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftMouseButton", IE_Released, this, &APawn_Default::LeftMouseReleased);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &APawn_Default::LeftMousePressed);

	PlayerInputComponent->BindAction("TestNum1", IE_Pressed, this, &APawn_Default::TestNum1Pressed);

	// 단축키 // 타일 설정 변경 키
	PlayerInputComponent->BindAction("Edit1", IE_Pressed, this, &APawn_Default::Edit1Pressed);
	PlayerInputComponent->BindAction("Edit2", IE_Pressed, this, &APawn_Default::Edit2Pressed);
	PlayerInputComponent->BindAction("Edit3", IE_Pressed, this, &APawn_Default::Edit3Pressed);
	PlayerInputComponent->BindAction("Edit4", IE_Pressed, this, &APawn_Default::Edit4Pressed);
}


void APawn_Default::LeftMouseReleased()
{
	{  // 타일 클릭 이벤트 처리
		if (CheckTile->IsValidLowLevel())
		{
			if (PC)
			{
				PC->GetIngameEditUI()->WidgetUpdate(CheckTile);
			}

			// 원복 (&& 취소 , )
			if (CurrentHitActor->IsValidLowLevel())
			{
				CurrentHitActor->ChangeColor();
				CurrentHitActor->EndBorderTile();
				CurrentHitActor->FocusTileEffect();
			}
			if (!CheckTile->TileState.bWall)
			{
				// 주변 타일 효과?
				CheckTile->ChangeColor(FColor::Red);
				CheckTile->EndBorderTile(FColor::Green);
			}

			CurrentHitActor = CheckTile;
			CheckTile->FocusTileEffect();
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, CurrentHitActor->GetName());
		}
	}
}

void APawn_Default::LeftMousePressed()
{
	{  // 타일 클릭 이벤트 처리
		FVector2D MousePos;
		PC->GetMousePosition(MousePos.X, MousePos.Y);

		FVector WorldLocation, WorldDirection;
		if (PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			FHitResult HitTile;
			GetWorld()->LineTraceSingleByChannel(HitTile, WorldLocation, (WorldDirection * 10000.f) + WorldLocation, ECollisionChannel::ECC_Visibility);
			CheckTile = Cast<AActor_Tile>(HitTile.GetActor());
			// TowerList 체크
			PC->GetIngameEditUI()->GetTowerListUI()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}


void APawn_Default::TestNum1Pressed()
{
	// Text Button Event;

}

void APawn_Default::Edit1Pressed()
{
	PC->GetIngameEditUI()->SetWall();
}
void APawn_Default::Edit2Pressed()
{
	PC->GetIngameEditUI()->SetObstacle();
}
void APawn_Default::Edit3Pressed()
{
	PC->GetIngameEditUI()->SetStartTile();
}
void APawn_Default::Edit4Pressed()
{
	PC->GetIngameEditUI()->SetEndTile();
}
