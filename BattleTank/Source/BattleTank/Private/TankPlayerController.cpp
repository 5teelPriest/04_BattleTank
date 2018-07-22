// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"

//This section executes once when the game is started
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possessing tank!"))
	}
}

//This section
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

void ATankPlayerController::AimAtCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
		//TODO Tell controlled tank to aim at this point
	}

	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenPosition = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection = GetLookDirection(ScreenPosition);
	OutHitLocation = GetLookVectorHitLocation(LookDirection);

	return true;
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

FVector ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	);
	
	return HitResult.Location;
}
