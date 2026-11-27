// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidgetCPP.h"
#include "GameFramework/Character.h"
#include "MyCharacterCPP.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAnimMontage;
class USphereComponent;

UCLASS()
class PLATAFORMASCPP_API AMyCharacterCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	int combo = 0;
	bool jumping;
	
	UPROPERTY(EditAnywhere, Category = Variables)
	float damage = 20;
	
	bool die;
	float horizontal; 
	bool death;
	FTimerHandle timer;
	FTimerHandle timerLifeBar;
	FTimerHandle timerCoinsText;
	
	UPROPERTY(EditAnywhere, Category = Components)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category = Components)
	USphereComponent* punchLeftCollider;
	
	UPROPERTY(EditAnywhere, Category = Components)
	USphereComponent* punchRightCollider;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* mappingContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* moveAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* jumpAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* punchAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* pauseAction;
	
	UPROPERTY(EditAnywhere, Category = Animations)
	UAnimMontage* punch1Montage;
	UPROPERTY(EditAnywhere, Category = Animations)
	UAnimMontage* punch2Montage;
	UPROPERTY(EditAnywhere, Category = Animations)
	UAnimMontage* punch3Montage;
	UPROPERTY(EditAnywhere, Category = Animations)
	UAnimMontage* hitMontage;
	
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UMyUserWidgetCPP> myUserWidgetCPPClass; //Esto coge una clase
	
	UPROPERTY(EditAnywhere, Category = UI)
	UMyUserWidgetCPP* gameplayWidget; //Esto coge un objeto
	
	UPROPERTY(EditAnywhere, Category = Audio)
	USoundBase* jumpSFX;
	UPROPERTY(EditAnywhere, Category = Audio)
	USoundCue* hitSFX;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move (const FInputActionValue& value);
	void StopMove();
	void Jumping (const FInputActionValue& value);
	void Punch (const FInputActionValue& value);
	void ContinueCombo();
	void Pause (const FInputActionValue& value);
	//void StopJumping (const FInputActionValue& value);
	
	UFUNCTION()
	void OnPunchBeginOverlap(UPrimitiveComponent* overlappedCOmponent, AActor* otherActor, 
		UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);
	
	void ActivateColliders();
	void DeactivateColliders();
	void TakeDamage(float _damage);
	void RecuperarInputs();
	void GetCoin();
};

