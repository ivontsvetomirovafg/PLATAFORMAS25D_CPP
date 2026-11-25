// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (IsValid(prota))
	{
		horizontal = FMath::Abs(prota->horizontal);
		jumping= prota->jumping; //que el jumping de la variable sea igual a la del prota
		die = prota-> death; 
	}
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	prota = Cast<AMyCharacterCPP>(TryGetPawnOwner());
}
