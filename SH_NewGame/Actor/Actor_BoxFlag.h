// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_BoxFlag.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class SH_NEWGAME_API AActor_BoxFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_BoxFlag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* FlagMesh;

	UMaterialInstanceDynamic* MI_Flag;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeColor(FColor Color);
};
