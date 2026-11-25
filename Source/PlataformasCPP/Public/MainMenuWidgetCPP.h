// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidgetCPP.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASCPP_API UMainMenuWidgetCPP : public UUserWidget
{
	GENERATED_BODY()	
	
protected:	
	virtual void NativeConstruct() override;

public: 	
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;
	
	UFUNCTION()
	void PlayButtonClicked();
	
	UFUNCTION()
	void ExitButtonClicked();
};
