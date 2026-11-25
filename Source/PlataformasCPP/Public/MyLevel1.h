// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevel1.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASCPP_API AMyLevel1 : public ALevelScriptActor
{
	GENERATED_BODY()
public: 
	UBoxComponent* winTrigger;
	
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;
	
	void Win(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
		int bodyIndex, bool isSweep, const FHitResult& sweepResult);
};

