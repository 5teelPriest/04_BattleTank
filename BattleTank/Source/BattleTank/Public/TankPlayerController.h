// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	//Executes once when game is started
	virtual void BeginPlay() override;

	//Exexutes every game tick
	virtual void Tick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingCompReference);

public:

	//Ensures player controller is possessing a tank pawn
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Crosshair Location")
		float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Crosshair Location")
		float CrosshairYLocation = 0.33333f;

	//Moves barrel to aim towards the on-screen crosshair
	void AimAtCrosshair();

	//Finds in-world location of crosshair and checks if it's hitting something
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	FVector GetLookDirection(FVector2D ScreenCoordinates) const;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
