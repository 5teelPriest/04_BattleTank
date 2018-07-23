// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	return;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	FVector OutLaunchVelocity = FVector(0);
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
		FVector BarrelAimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(BarrelAimDirection);
	}
	
	return;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	
	return;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent * TurretToSet)
{
	Turret = TurretToSet;

	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().ToOrientationRotator();
	FRotator AimRotation = AimDirection.ToOrientationRotator();
	FRotator DeltaRotation = AimRotation - BarrelRotation;
	
	Barrel->Elevate(DeltaRotation.Pitch);

	return;
}
