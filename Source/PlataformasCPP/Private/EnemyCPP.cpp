// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"

#include "AIController.h"
#include "MyCharacterCPP.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AEnemyCPP::AEnemyCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	
	punchLeftCollider = CreateDefaultSubobject<USphereComponent>("Left punch");
	punchRightCollider = CreateDefaultSubobject<USphereComponent>("Right punch");
	
	const FAttachmentTransformRules attachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, 
		EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	punchLeftCollider->AttachToComponent(GetMesh(), attachmentRules,"LeftHand");
	punchRightCollider->AttachToComponent(GetMesh(), attachmentRules,"RightHand");
	punchLeftCollider->SetSphereRadius(20);
	punchRightCollider->SetSphereRadius(20);
}

// Called when the game starts or when spawned
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();
	pawnSensing->OnSeePawn.AddDynamic(this, &AEnemyCPP::OnVerPawn);
	
	AAIController* aiController = Cast<AAIController>(GetController());
	if (IsValid(aiController))
	{
		aiController->ReceiveMoveCompleted.AddDynamic(this, &AEnemyCPP::OnMoveCompleted);
	}
	if (IsValid(punchLeftCollider) && IsValid(punchRightCollider))
	{
		punchLeftCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCPP::OnPunchBeginOverlap);
		punchRightCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCPP::OnPunchBeginOverlap);
	}
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCPP::OnVerPawn(APawn* pawn)
{
	AMyCharacterCPP* player = Cast<AMyCharacterCPP>(pawn);
	
	if (IsValid(player))
	{
		AAIController* aiController = Cast<AAIController>(GetController());
		if (IsValid(aiController))
		{
			aiController->MoveToActor(pawn, 100);
		}
	}
}

void AEnemyCPP::OnMoveCompleted(FAIRequestID aiID, EPathFollowingResult::Type result)
{
	if (result == EPathFollowingResult::Success)
	{
		//GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"Success");
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"No he llegado");
	}
}

void AEnemyCPP::TakeDamage(float _damage)
{	
	life -= _damage;
	if (life <= 0)
	{
		death = true;
	}
	else
	{
		//hit
		//PlayAnimMontage(hitEnemyMontage);
		/*if (IsValid(hitEnemyMontage))
		{
			PlayAnimMontage(hitEnemyMontage);
		}*/
	}
	
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Magenta,"Enemy Daño");
}

void AEnemyCPP::OnPunchBeginOverlap(UPrimitiveComponent* overlappedCOmponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	AMyCharacterCPP* player = Cast<AMyCharacterCPP>(otherActor);
	if (IsValid(player))
	{
		player->TakeDamage(damage);
	}
}

void AEnemyCPP::ActivateColliders()
{
	punchLeftCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	punchRightCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AEnemyCPP::DesactivateColliders()
{
	punchLeftCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	punchRightCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
