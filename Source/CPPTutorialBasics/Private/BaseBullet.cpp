// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
	BulletFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	// Set the root component to be the BulletFX:
	SetRootComponent(BulletFX);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	// Now, attach the collision sphere to the bullet effect sound (making the sphere a child of the soundfx)
	CollisionSphere->SetupAttachment(BulletFX); // After adding the #include "NiagaraComponent.h" it understands that a Niagara Component is also a Scene component and stops complaining!


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

