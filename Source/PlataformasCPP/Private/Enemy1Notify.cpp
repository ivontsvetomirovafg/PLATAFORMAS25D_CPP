// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1Notify.h"

#include "EnemyCPP.h"

void UEnemy1Notify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	AEnemyCPP* myEnemyCPP = Cast<AEnemyCPP>(MeshComp->GetOwner());
	if (IsValid(myEnemyCPP))
	{
		myEnemyCPP->ActivateColliders();
	}
}

void UEnemy1Notify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	AEnemyCPP* myEnemyCPP = Cast<AEnemyCPP>(MeshComp->GetOwner());
	if (IsValid(myEnemyCPP))
	{
		myEnemyCPP->DesactivateColliders();
	}
}

void UEnemy1Notify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TimeDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, TimeDeltaTime, EventReference);
}
