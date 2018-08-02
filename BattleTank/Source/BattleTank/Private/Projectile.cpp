// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMotion = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Motion"));
	ProjectileMotion->bAutoActivate = false;

	return;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	return;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	return;
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	if (!ensure(ProjectileMotion)) { return; }
	ProjectileMotion->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMotion->Activate();
	
	return;
}

