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
	SpawnLocation->SetupAttachment(GetMesh());

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

FVector ABaseMagicCharacter::CalculateMovementBlending()
{
	FVector Movement = MovementRot.Vector();
	FVector Shooting = ShootRot.Vector();

	// x component
	float RodProd = FVector::DotProduct(Movement, Shooting);
	// y component
	FVector BlendVector = Movement - Shooting * RodProd;

	FVector OutputVector = FVector(RodProd, BlendVector.Length(), 0);


	return OutputVector * 100;
}

void ABaseMagicCharacter::SetShootTrue()
{
	IsShooting = true;
}

void ABaseMagicCharacter::SetShootFalse()
{
	IsShooting = false;
}

void ABaseMagicCharacter::SetCanFire(bool Value)
{
	CanFire = Value;
}

AActor* ABaseMagicCharacter::ShootBullet(FVector Direction)
{
	ShootRot = Direction.Rotation();

	if (CanFire)
	{
		CanFire = false;

		// Set a timer
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ABaseMagicCharacter::SetCanFire, true);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeBetweenFires, false);

		// THIS SHOULD BE INSIDE THE IF STATEMENT!!!!!!! AND OUTSIDE THE IF STATEMENT RETURN NULLPTR!!!!! 
		// IT SOLVED THE WAY THE BULLET/POWER WAS SHOT AND COLLIDING ALL THE TIME
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
	SetActorRotation(Direction.Rotation());

	return nullptr;
}

float ABaseMagicCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HP -= DamageAmount;
	if (HP <= 0)
	{
		Destroy();
	}
	return DamageAmount;
}

// Called every frame
void ABaseMagicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsShooting)
	{
		SetActorRotation(ShootRot);
	}
	else
	{
		SetActorRotation(MovementRot);
	}

}

// Called to bind functionality to input
void ABaseMagicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

