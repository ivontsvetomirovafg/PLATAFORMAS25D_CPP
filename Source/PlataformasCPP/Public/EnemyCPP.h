// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyCPP.generated.h"

UCLASS()
class PLATAFORMASCPP_API AEnemyCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	bool death;
	float life = 100;
	float damage = 10;
	float horizontal; 
	
	FTimerHandle timer;
	
	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* pawnSensing;
	
	//ANIMS
	UPROPERTY(EditAnywhere, Category = Animations)
	UAnimMontage* punchEnemyMontage;
	UPROPERTY(EditAnywhere, Category = Animations)
	UAnimMontage* hitEnemyMontage;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnVerPawn(APawn* pawn);
	
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID aiID, EPathFollowingResult::Type result);
	void TakeDamage(float _damage);
};

