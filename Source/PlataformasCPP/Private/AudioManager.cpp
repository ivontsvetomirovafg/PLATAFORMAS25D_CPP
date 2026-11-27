// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AAudioManager::PlayMusic(USoundBase* _music)
{
	audioComponent = UGameplayStatics::SpawnSound2D(this, _music, 1.0f, 1.0f, 0.0f);
}

void AAudioManager::PlaySound(USoundBase* _sound)
{
	UGameplayStatics::PlaySound2D(this, _sound);
}

void AAudioManager::ChangeVolume(float _volume)
{
	//audioComponent->VolumeMultiplier(_volume);
}

void AAudioManager::StopMusic()
{
	audioComponent->Stop();
}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

