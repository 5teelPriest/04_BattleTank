// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	OutHitLocation = FVector(1.0, 1.0, 1.0);
	//Find in-world location of crosshair

	//Draw trace line to that location
	//Determine if it's hitting anything

	return true;
}
