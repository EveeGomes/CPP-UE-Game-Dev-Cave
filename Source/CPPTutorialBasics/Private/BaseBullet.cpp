// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
	BulletFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	SetRootComponent(BulletFX);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(BulletFX);

	//
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::BeginOverLap);
	
}

void ABaseBullet::BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactParticles, GetActorLocation());
	BulletHit();

	// ApplyDamage asks for a controller, so we put it in a variable:
	AController* PlayerController = GetInstigator()->GetController();
	UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, PlayerController, this, DamageType);
	Destroy();
}

void ABaseBullet::BulletHit()
{
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

}

