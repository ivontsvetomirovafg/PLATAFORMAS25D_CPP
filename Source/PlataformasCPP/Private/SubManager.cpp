// Fill out your copyright notice in the Description page of Project Settings.


#include "SubManager.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void USubManager::PlayMusic(USoundBase* _music)
{
	audioComponent = UGameplayStatics::SpawnSound2D(this, _music, 1.0f, 1.0f, 0.0f);
}

void USubManager::PlaySound(USoundBase* _sound)
{
	UGameplayStatics::PlaySound2D(this, _sound);
}

void USubManager::ChangeVolume(float _volume)
{
	//audioComponent->VolumeMultiplier(_volume);
}

void USubManager::StopMusic()
{
	audioComponent->Stop();
}

