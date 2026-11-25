// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacterCPP.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASCPP_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public: 
	AMyCharacterCPP* prota;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float horizontal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool jumping;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool die;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //como un update del blueprint de anim.
	
	virtual void NativeInitializeAnimation() override; //como un start del blueprint de anim.
};
