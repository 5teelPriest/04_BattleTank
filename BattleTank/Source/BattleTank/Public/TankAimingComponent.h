// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for firing state to determine crosshair color
UENUM()
enum class EFiringStatus : uint8
{
	LOCKED,
	AIMING,
	RELOADING,
	OUT_OF_AMMO
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UTankBarrel* Barrel = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringStatus GetFiringStatus();

	UPROPERTY(BlueprintReadOnly)
		uint8 AmmoRemaining = 3;


protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::RELOADING;
	
private:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving(FVector AimDirection);

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 100000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.0f;

	double LastFireTime = 0.0;

	FVector AimDirection = FVector(0);
};