// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SubManager.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASCPP_API USubManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public: 
	UPROPERTY()	
	UAudioComponent* audioComponent;

	void PlayMusic(USoundBase* _music);
	void PlaySound(USoundBase* _sound); 
	void ChangeVolume(float _volume);
	void StopMusic();
};
