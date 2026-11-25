// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (IsValid(enemy))
	{
		horizontal = FMath::Abs(enemy->horizontal);
		die = enemy-> death; 
	}
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	enemy = Cast<AEnemyCPP>(TryGetPawnOwner());
}
