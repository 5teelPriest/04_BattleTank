// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Elevate();

private:

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesElevation = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinDegreesElevation = 0.0f;

};
