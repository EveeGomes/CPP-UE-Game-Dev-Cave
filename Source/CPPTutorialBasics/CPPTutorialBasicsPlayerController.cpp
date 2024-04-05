// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPTutorialBasicsPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "CPPTutorialBasicsCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseMagicCharacter.h"

ACPPTutorialBasicsPlayerController::ACPPTutorialBasicsPlayerController()
{}

void ACPPTutorialBasicsPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Get the spawned character, cast it to a BaseMagicCharacter and assign it to PlayerCharacter
	PlayerCharacter = Cast<ABaseMagicCharacter>(GetPawn());

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

void ACPPTutorialBasicsPlayerController::SetupInputComponent()
{

	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Movement Bidings
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ACPPTutorialBasicsPlayerController::Move);

		// Shooting Bidings
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Triggered, this, &ACPPTutorialBasicsPlayerController::FireBullet);
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Started, this, &ACPPTutorialBasicsPlayerController::SetShootTrue);
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Completed, this, &ACPPTutorialBasicsPlayerController::SetShootFalse);
	}
}


void ACPPTutorialBasicsPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector InputVector = FVector(MovementVector, 0);
	MovementRot = InputVector.Rotation();

	// Get a pointer to the pawn that you're possessing
	APawn* pawn = GetPawn();
	pawn->AddMovementInput(InputVector, speed, false);
}

void ACPPTutorialBasicsPlayerController::FireBullet(const FInputActionValue& Value)
{
	// Check if the player is valid (to avoid the engine to crash)
	if (PlayerCharacter)
	{
		// Set character's rotation
		FVector Direction = FVector(Value.Get<FVector2D>(), 0);
		ShootRot = Direction.Rotation();

		if (CanFire)
		{
			PlayerCharacter->ShootBullet();
			CanFire = false;

			// Set a timer
			FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ACPPTutorialBasicsPlayerController::SetCanFire, true);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeBetweenFires, false);
		}
	}
}

void ACPPTutorialBasicsPlayerController::SetCanFire(bool Value)
{
	//CanFire = true;
	CanFire = Value;
}

void ACPPTutorialBasicsPlayerController::SetShootTrue()
{
	IsShooting = true;
}

void ACPPTutorialBasicsPlayerController::SetShootFalse()
{
	IsShooting = false;
}

FVector ACPPTutorialBasicsPlayerController::CalculateMovementBlending()
{
	FVector Movement = MovementRot.Vector();
	FVector Shooting = ShootRot.Vector();

	// x component
	float RodProd = FVector::DotProduct(Movement, Shooting);
	// y component
	FVector BlendVector = Movement - Shooting * RodProd;

	FVector OutputVector = FVector(RodProd, BlendVector.Length(), 0);


	return OutputVector*100;
}

void ACPPTutorialBasicsPlayerController::Tick(float DeltaTime)
{
	if (IsShooting)
	{
		PlayerCharacter->SetActorRotation(ShootRot);
	}
	else
	{
		PlayerCharacter->SetActorRotation(MovementRot);
	}
	
}

