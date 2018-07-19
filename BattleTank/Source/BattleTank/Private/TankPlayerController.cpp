// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = GetControlledTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Tank found!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *PlayerTank->GetName())
	}
}

ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

