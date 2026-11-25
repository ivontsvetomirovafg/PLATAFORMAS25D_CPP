// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASCPP_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, Category = "PlayerParameters")
	float life = 100;
	UPROPERTY(EditAnywhere, Category = "PlayerParameters")
	float maxLife = 100;
	UPROPERTY(EditAnywhere, Category = "PlayerParameters")
	int coleccionable = 0;
	
	//UFUNCTION(BlueprintCallable)
	//virtual void Init() override; //Se ejecuta al iniciar el gameInstance
};
