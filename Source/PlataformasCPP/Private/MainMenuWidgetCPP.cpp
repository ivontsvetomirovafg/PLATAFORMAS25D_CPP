// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidgetCPP.h"

#include "Kismet/GameplayStatics.h"

void UMainMenuWidgetCPP::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidgetCPP::PlayButtonClicked);
}

void UMainMenuWidgetCPP::PlayButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "NewMap");
}

void UMainMenuWidgetCPP::ExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
