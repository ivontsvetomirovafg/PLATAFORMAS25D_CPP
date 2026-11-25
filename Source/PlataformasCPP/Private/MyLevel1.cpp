// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevel1.h"

#include "EngineUtils.h"

void AMyLevel1::BeginPlay()
{
	Super::BeginPlay();
	
	//TActorIterator --> Contienen toda la info del level.
	for (TActorIterator<AActor> actor (GetWorld()); actor; ++actor)
	{
		if (actor->ActorHasTag("Meta"))
		{
			winTrigger = actor->FindComponentByClass<UBoxComponent>(); 
		}
	}
	
	if (IsValid(winTrigger))
	{
		winTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMyLevel1::Win);
	}
}

void AMyLevel1::Win(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
		int bodyIndex, bool isSweep, const FHitResult& sweepResult)
{
	//ha llegado a la meta
}