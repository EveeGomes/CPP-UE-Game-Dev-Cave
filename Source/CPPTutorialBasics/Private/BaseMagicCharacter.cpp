// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMagicCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseWeapon.h"
#include "BaseBullet.h"


// Sets default values
ABaseMagicCharacter::ABaseMagicCharacter()
{
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));

}

// Called when the game starts or when spawned
void ABaseMagicCharacter::BeginPlay()
{
	Super::BeginPlay();

	ABaseWeapon* WeaponPtr = Cast<ABaseWeapon>(Weapon->GetChildActor());
	if (WeaponPtr)
	{
		WeaponPtr->SetPlayerPointer(this);
	}
}

AActor* ABaseMagicCharacter::ShootBullet()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this; // to keep track of who did the damage

	// Actor pointer set to point to whatever actor is spawned in the world
	AActor* SpawnedActor = GetWorld()->SpawnActor<ABaseBullet>(
		BulletToSpawn,
		SpawnLocation->GetComponentLocation(), 
		GetActorRotation(), 
		SpawnParams);

	return SpawnedActor;
}

// Called every frame
void ABaseMagicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMagicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

