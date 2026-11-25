// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidgetCPP.h"

#include "MyGameInstance.h"

void UMyUserWidgetCPP::UpdateLifeBar()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	if (IsValid(gameInstance))
	{
		float percent = gameInstance->life/gameInstance->maxLife;
		LifeBar->SetPercent(percent);
	}
}

void UMyUserWidgetCPP::UpdateCoinsText()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	if (IsValid(gameInstance))
	{
		CoinsText->SetText(FText::AsNumber(gameInstance->coleccionable)); //sumar moneda
	}
}
