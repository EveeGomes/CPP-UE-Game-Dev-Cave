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

	// Have similar code to what we have in SetShootTrue/False methods in order to get a reference to MovementRot:

	//ABaseMagicCharacter* Character = Cast<ABaseMagicCharacter>(GetPawn());
	//Character = Cast<ABaseMagicCharacter>(GetPawn());/////// this is also already initialized in BeginPlay(), should it be initialized again?

	if (PlayerCharacter)
	{
		PlayerCharacter->MovementRot = InputVector.Rotation();
	}

	// Get a pointer to the pawn that you're possessing
	APawn* pawn = GetPawn();
	pawn->AddMovementInput(InputVector, speed, false);
}

void ACPPTutorialBasicsPlayerController::FireBullet(const FInputActionValue& Value)
{
	FVector Direction = FVector(Value.Get<FVector2D>(), 0);
	PlayerCharacter->ShootBullet(Direction);
}

void ACPPTutorialBasicsPlayerController::SetShootTrue()
{
	//ABaseMagicCharacter* Character = Cast<ABaseMagicCharacter>(GetPawn());
	// Instead of creating a pointer, use the one that's a member of the this class!
	//PlayerCharacter = Cast<ABaseMagicCharacter>(GetPawn());/////// this is also already initialized in BeginPlay(), should it be initialized again?
	if (PlayerCharacter)
	{
		PlayerCharacter->SetShootTrue();
	}
}

void ACPPTutorialBasicsPlayerController::SetShootFalse()
{
	//ABaseMagicCharacter* Character = Cast<ABaseMagicCharacter>(GetPawn());
	//Character = Cast<ABaseMagicCharacter>(GetPawn());/////// this is also already initialized in BeginPlay(), should it be initialized again?
	if (PlayerCharacter)
	{
		PlayerCharacter->SetShootFalse();
	}
}


void ACPPTutorialBasicsPlayerController::Tick(float DeltaTime)
{	
}

