// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterCPP.h"

#include "EnemyCPP.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "DSP/BufferDiagnostics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "MyGameInstance.h"
//#include "EnhancedLocalPlayerSubsystem.h"

// Sets default values
AMyCharacterCPP::AMyCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera"); //creas la cam
	Camera->SetupAttachment(RootComponent); //esto le indica dónde queremos la cam. 
	
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
void AMyCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (!IsValid(playerController))
	{
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	
	if (!IsValid(subsystem))
	{
		return;
	}
	subsystem->AddMappingContext(mappingContext, 0);
	
	//DEBUG
	//UE_LOG(LogTemp, Log, TEXT("Antonio va a pescar")); --> Log de consola
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,TEXT("BeginPlay del player"));
	
	if (IsValid(punchLeftCollider) && IsValid(punchRightCollider))
	{
		punchLeftCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacterCPP::OnPunchBeginOverlap);
		punchRightCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacterCPP::OnPunchBeginOverlap);
	}
	
	//NUEVO
	gameplayWidget = CreateWidget<UMyUserWidgetCPP>(playerController, myUserWidgetCPPClass);
	if (IsValid(gameplayWidget))
	{
		gameplayWidget->AddToViewport();
		
		GetWorld()->GetTimerManager().SetTimer(timerLifeBar, gameplayWidget, &UMyUserWidgetCPP::UpdateLifeBar, 0.2f);
		GetWorld()->GetTimerManager().SetTimer(timerCoinsText, gameplayWidget, &UMyUserWidgetCPP::UpdateCoinsText, 0.2f);
		
		//gameplayWidget->UpdateLifeBar();
		//gameplayWidget->UpdateCoinsText();
	}
}

// Called every frame
void AMyCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetCharacterMovement()->IsFalling()==false)
	{
		jumping = false;
	}

}

// Called to bind functionality to input
void AMyCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* enhancedComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(enhancedComponent))
	{
		return;
	}
	enhancedComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AMyCharacterCPP::Move); //Bind --> Relaciona el input action con nuestro método. 
	enhancedComponent->BindAction(moveAction, ETriggerEvent::Completed, this, &AMyCharacterCPP::StopMove);
	enhancedComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &AMyCharacterCPP::Jumping);
	//enhancedComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &AMyCharacterCPP::StopJumping);
	enhancedComponent->BindAction(punchAction, ETriggerEvent::Started, this, &AMyCharacterCPP::Punch);
	enhancedComponent->BindAction(pauseAction, ETriggerEvent::Started, this, &AMyCharacterCPP::Pause);
}

void AMyCharacterCPP::Move(const FInputActionValue& value)
{
	horizontal = value.Get<float>();
	AddMovementInput(FVector(horizontal,0,0));
	if (horizontal <0)
	{
		GetMesh()->SetRelativeRotation(FRotator(0,-270,0));
	}
	else if (horizontal > 0)
	{
		GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
	}
}

void AMyCharacterCPP::StopMove()
{
	horizontal = 0;
}

void AMyCharacterCPP::Jumping(const FInputActionValue& value)
{
	if (combo<1)
	{
		Jump();
		jumping = true;
	}
}

/*void AMyCharacterCPP::StopJumping(const FInputActionValue& value)
{
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,TEXT("StopJumping"));
	jumping = false;
}*/

void AMyCharacterCPP::Punch(const FInputActionValue& value)
{
	if (jumping == true)
	{
		return;
	}
	if (!IsValid(punch1Montage))
	{
		return;
	}
	combo += 1;
	
	if (combo == 1)
	{
		PlayAnimMontage(punch1Montage);
		GetWorld()->GetTimerManager().SetTimer(timer,this,&AMyCharacterCPP::ContinueCombo, 
			punch1Montage->GetPlayLength());
	}
}

void AMyCharacterCPP::ContinueCombo()
{
	if (death == true)
	{
		return;
	}
	switch (combo)
	{
		case 1:
		combo = 0;
			break;
		
		case 2:
		PlayAnimMontage(punch2Montage);
		GetWorld()->GetTimerManager().SetTimer(timer,this,&AMyCharacterCPP::ContinueCombo,
			punch2Montage->GetPlayLength());
			break;
		
		case 3:
		PlayAnimMontage(punch3Montage);
		GetWorld()->GetTimerManager().SetTimer(timer,this,&AMyCharacterCPP::ContinueCombo,
			punch3Montage->GetPlayLength());
			break;
		
		default:
		combo = 0;
			break;
	}
}

void AMyCharacterCPP::Pause(const FInputActionValue& value)
{
	
}

void AMyCharacterCPP::OnPunchBeginOverlap(UPrimitiveComponent* overlappedCOmponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	AEnemyCPP* enemy = Cast<AEnemyCPP>(otherActor);
	if (IsValid(enemy))
	{
		enemy->TakeDamage(damage);
	}
}

void AMyCharacterCPP::ActivateColliders()
{
	punchLeftCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	punchRightCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyCharacterCPP::DeactivateColliders()
{
	punchLeftCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	punchRightCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyCharacterCPP::TakeDamage(float _damage)
{
	UMyGameInstance* myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (!IsValid(myGameInstance))
	{
		return;
	}
	myGameInstance->life -= _damage;
	
	APlayerController* playerController = Cast<APlayerController>(Controller);
	DisableInput(playerController);
	
	if (myGameInstance->life <= 0)
	{
		death = true;
		//UI de gameOver
	}
	else
	{
		//hit
		PlayAnimMontage(hitMontage);
		GetWorld()->GetTimerManager().SetTimer(timer,this,&AMyCharacterCPP::RecuperarInputs,
	hitMontage->GetPlayLength());
	}
	
	//Acceder a la UI y actualizar la barra de vida.
	//NUEVO
	gameplayWidget->UpdateLifeBar();
}

void AMyCharacterCPP::RecuperarInputs()
{
	APlayerController* playerController = Cast<APlayerController>(Controller);
	EnableInput(playerController);
}

void AMyCharacterCPP::GetCoin()
{
	UMyGameInstance* myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (!IsValid(myGameInstance))
	{
		return;
	}
	myGameInstance->coleccionable ++;
}




