// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = GetControlledTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possessing tank!"))
	}
}

ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

