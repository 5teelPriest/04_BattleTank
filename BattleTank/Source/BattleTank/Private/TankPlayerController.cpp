// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "Tank.h"

//This section executes once when the game is started
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (TankAimingComponent)
	{
		FoundAimingComponent(TankAimingComponent);
	}

	return;
}

//This section
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();

	return;
}

void ATankPlayerController::AimAtCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		TankAimingComponent->AimAt(HitLocation);
	}

	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenPosition = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection = GetLookDirection(ScreenPosition);
	bool bHaveHit = GetLookVectorHitLocation(LookDirection, OutHitLocation);
	if (bHaveHit)
	{
		return true;
	}
	
	return false;
}

FVector ATankPlayerController::GetLookDirection(FVector2D ScreenCoordinates) const
{
	FVector CameraWorldPosition;
	FVector LookDirection;

	DeprojectScreenPositionToWorld
	(
		ScreenCoordinates.X,
		ScreenCoordinates.Y,
		CameraWorldPosition,
		LookDirection
	);
	
	return LookDirection;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	bool bHaveHit = GetWorld()->LineTraceSingleByChannel
		(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
		);
	if (bHaveHit)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);

	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();

	return;
}
