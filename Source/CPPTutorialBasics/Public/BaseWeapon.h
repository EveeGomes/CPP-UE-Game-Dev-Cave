// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class CPPTUTORIALBASICS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	// To be used in the BaseMagicCharacter to get the reference of the player
	void SetPlayerPointer(ACharacter* PlayerPtr);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage;

	UFUNCTION(BlueprintCallable)
	void WeaponShoot();

	// Used to get a reference for the player
	ACharacter* Player;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
