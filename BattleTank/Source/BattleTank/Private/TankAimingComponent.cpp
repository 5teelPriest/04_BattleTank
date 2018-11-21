// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	return;
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();

	return;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (AmmoRemaining == 0)
	{
		FiringStatus = EFiringStatus::OUT_OF_AMMO;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::RELOADING;
	}
	else if (!IsBarrelMoving(AimDirection))
	{
		FiringStatus = EFiringStatus::AIMING;
	}
	else
	{
		FiringStatus = EFiringStatus::LOCKED;
	}

	return;
}

EFiringStatus UTankAimingComponent::GetFiringStatus()
{
	return FiringStatus;
}

bool UTankAimingComponent::IsBarrelMoving(FVector AimDirection)
{
	if (AimDirection.Equals(Barrel->GetForwardVector()))
	{
		return true;
	}
	return false;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchVelocity = FVector(0);
	if (!ensure(Barrel)) { return; }
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	
	return;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;

	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	FRotator BarrelRotation = Barrel->GetForwardVector().ToOrientationRotator();
	FRotator AimRotation = AimDirection.ToOrientationRotator();
	FRotator DeltaRotation = AimRotation - BarrelRotation;
	Barrel->Elevate(DeltaRotation.Pitch);
	if (FMath::Abs(DeltaRotation.Yaw) < 180.0f)
	{
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	}
	
	return;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (!(FiringStatus == EFiringStatus::RELOADING || FiringStatus == EFiringStatus::OUT_OF_AMMO))
	{
		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBlueprint,
				SpawnLocation,
				SpawnRotation
				);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		AmmoRemaining -= 1;
	}

	return;
}