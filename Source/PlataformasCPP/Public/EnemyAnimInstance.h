// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCPP.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASCPP_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public: 
	AEnemyCPP* enemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float horizontal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool die;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; 
	
	virtual void NativeInitializeAnimation() override; 
};
