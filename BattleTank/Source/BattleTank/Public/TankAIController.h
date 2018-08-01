// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void Tick(float DeltaTime) override;

private:

	//How close AI moves to player before stopping
	float AcceptanceRadius = 10000.0f;
};
