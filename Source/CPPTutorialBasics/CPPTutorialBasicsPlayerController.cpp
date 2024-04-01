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
	}
}


void ACPPTutorialBasicsPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector InputVector = FVector(MovementVector, 0);

	// Get a pointer to the pawn that you're possessing
	APawn* pawn = GetPawn();
	pawn->AddMovementInput(InputVector, speed, false);
}

void ACPPTutorialBasicsPlayerController::FireBullet(const FInputActionValue& Value)
{
	// Check if the player is valid (to avoid the engine to crash)
	if (PlayerCharacter && CanFire)
	{
		PlayerCharacter->ShootBullet();
		CanFire = false;

		// Set a timer
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ACPPTutorialBasicsPlayerController::SetCanFire, true);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeBetweenFires, false);
	}
}

void ACPPTutorialBasicsPlayerController::SetCanFire(bool Value)
{
	//CanFire = true;
	CanFire = Value;
}

