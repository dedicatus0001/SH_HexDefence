// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_BoxFlag.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AActor_BoxFlag::AActor_BoxFlag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = SceneComp;
	
	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>("FlagMesh");
	FlagMesh->SetupAttachment(SceneComp);
	FlagMesh->SetWorldScale3D(FVector(0.6f));
	FlagMesh->AddLocalOffset(FVector(0, 0, 40.f));

	FlagMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Mesh/SM_Box2.SM_Box2"));
	if (Mesh.Succeeded())
		FlagMesh->SetStaticMesh(Mesh.Object);

}

// Called when the game starts or when spawned
void AActor_BoxFlag::BeginPlay()
{
	Super::BeginPlay();

	MI_Flag = FlagMesh->CreateDynamicMaterialInstance(0);
	if (MI_Flag)
	{
		MI_Flag->SetVectorParameterValue("Color", FColor::Black);
	}

}

void AActor_BoxFlag::ChangeColor(FColor Color)
{
	if (MI_Flag)
	{
		MI_Flag->SetVectorParameterValue("Color", Color);
	}
}

// Called every frame
void AActor_BoxFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

