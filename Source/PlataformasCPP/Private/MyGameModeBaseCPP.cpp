// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBaseCPP.h"

AMyGameModeBaseCPP::AMyGameModeBaseCPP()
{
	//Buscamos nuestro player en las carpetas del juego
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn (TEXT ("/Game/BluprintCPP/CharacterCPP"));
	
	if (PlayerPawn.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawn.Class;
	}
}
