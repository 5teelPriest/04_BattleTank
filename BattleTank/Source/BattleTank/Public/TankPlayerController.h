// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	//Executes once when game is started
	virtual void BeginPlay() override;

	//Exexutes every game tick
	virtual void Tick(float DeltaTime);

public:

	//Ensures player controller is possessing a tank pawn
	ATank* GetControlledTank() const;

private:

	//Moves barrel to aim towards the on-screen crosshair
	void AimAtCrosshair();

	//Finds in-world location of crosshair and checks if it's hitting something
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	
};
