// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/PlayerCameraManager.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

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
		UE_LOG(LogTemp, Warning, TEXT("Target Location: %s"), *HitLocation.ToString())
		//TODO Tell controlled tank to aim at this point
	}

	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenPosition = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection = GetLookDirection(ScreenPosition);
	OutHitLocation = GetLookVectorHitLocation(LookDirection);
	//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString())

	return true;
}

FVector ATankPlayerController::GetLookDirection(FVector2D ScreenCoordinates)
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

FVector ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection)
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
