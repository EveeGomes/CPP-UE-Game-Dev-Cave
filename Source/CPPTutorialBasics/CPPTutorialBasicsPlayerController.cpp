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

ACPPTutorialBasicsPlayerController::ACPPTutorialBasicsPlayerController()
{}

void ACPPTutorialBasicsPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

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

		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ACPPTutorialBasicsPlayerController::Move);

	}
}


void ACPPTutorialBasicsPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector InputVector = FVector(MovementVector, 0);

	// Get a pointer to the pawn that you're possessing
	APawn* pawn = GetPawn();
	pawn->AddMovementInput(InputVector, speed, false);

	// the following won't work!
	//GetPawn()->AddMovementInput(InputVector, speed, false);



	/**
	//////////////////////////////////////////////////////////////////////////////////////////////
	// https://forums.unrealengine.com/t/how-to-set-up-enhanced-input-for-aplayercontroller-in-c/1220649/22 // 

	//// input is a Vector2D
	//FVector2D MovementVector = Value.Get<FVector2D>();

	//// find out which way is forward
	//const FRotator Rotation = GetControlRotation();
	//const FRotator YawRotation(0, Rotation.Yaw, 0);

	//// get forward vector
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//// get right vector 
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//// add movement 
	//APawn* pawn = GetPawn();
	//pawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	//pawn->AddMovementInput(RightDirection, MovementVector.X);
	*/
}

