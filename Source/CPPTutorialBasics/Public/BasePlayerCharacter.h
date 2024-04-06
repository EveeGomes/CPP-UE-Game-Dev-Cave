// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMagicCharacter.h"
#include "BasePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CPPTUTORIALBASICS_API ABasePlayerCharacter : public ABaseMagicCharacter
{
	GENERATED_BODY()
	
	// If I add the following, the player won't rotate when moving
public:
	//FRotator ShootRot;
	//FRotator MovementRot;

	//virtual void Tick(float DeltaTime) override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
