// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = FindPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No player tank found!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank: %s"), *PlayerTank->GetName())
	}
}

ATank* ATankAIController::FindPlayerTank() const
{ 
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	return Cast<ATank>(PlayerTank);
}

