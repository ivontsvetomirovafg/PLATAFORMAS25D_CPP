// Fill out your copyright notice in the Description page of Project Settings.


#include "PunchNotifyState.h"

#include "MyCharacterCPP.h"

void UPunchNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	//Se ejecuta cuando empieza el notifyState
	AMyCharacterCPP* myCharacterCPP = Cast<AMyCharacterCPP>(MeshComp->GetOwner());
	if (IsValid(myCharacterCPP))
	{
		myCharacterCPP->ActivateColliders();
	}
}

void UPunchNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	//Se ejecuta cuando termina el notifyState
	AMyCharacterCPP* myCharacterCPP = Cast<AMyCharacterCPP>(MeshComp->GetOwner());
	if (IsValid(myCharacterCPP))
	{
		myCharacterCPP->DeactivateColliders();
	}
}

void UPunchNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TimeDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, TimeDeltaTime, EventReference);
	//Se ejecuta cada frame que el notifyState esté activo
}
