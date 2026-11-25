// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MyUserWidgetCPP.generated.h"


/**
 * 
 */
UCLASS()
class PLATAFORMASCPP_API UMyUserWidgetCPP : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(meta = (BindWidget))
	UProgressBar* LifeBar; //tiene que llamarse igual que tu barra de vida del canvas
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoinsText;
	
	void UpdateLifeBar();
	void UpdateCoinsText();
};
