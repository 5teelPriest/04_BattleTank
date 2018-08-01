// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		Cast<ATank>(GetPawn())->AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

		//Cast<ATank>(GetPawn())->Fire();
	}
	

	return;
}