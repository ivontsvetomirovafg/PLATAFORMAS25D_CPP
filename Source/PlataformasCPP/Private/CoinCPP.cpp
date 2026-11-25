// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinCPP.h"
#include "MyCharacterCPP.h"

// Sets default values
ACoinCPP::ACoinCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoinCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoinCPP::OnCoinBeginOverlap(UPrimitiveComponent* overlappedCOmponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	AMyCharacterCPP* myCharacter = Cast<AMyCharacterCPP>(otherActor);
	if (IsValid (myCharacter))
	{
		myCharacter->GetCoin();
	}
}

