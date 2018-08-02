// Copyright Fisher-Studios 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

//Logic that controls behavior of AI tanks on the battlefield
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:	

	UTankAimingComponent * TankAimingComponent = nullptr;

	//How close AI moves to player before stopping
	float AcceptanceRadius = 1000.0f;
};
