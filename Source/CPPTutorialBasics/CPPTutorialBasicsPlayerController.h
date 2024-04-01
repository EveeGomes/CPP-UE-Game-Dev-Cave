// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CPPTutorialBasicsPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ACPPTutorialBasicsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPPTutorialBasicsPlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Movement Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MovementInput;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireInput;

protected:
	///** True if the controlled character should navigate to the mouse cursor. */
	//uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere)
	float speed;

	void Move(const FInputActionValue& Value);
	void FireBullet(const FInputActionValue& Value);

	class ABaseMagicCharacter* PlayerCharacter;

	bool CanFire = true;

	UPROPERTY(EditAnywhere)
	float TimeBetweenFires = 0.2f;

	void SetCanFire(bool Value);
};


