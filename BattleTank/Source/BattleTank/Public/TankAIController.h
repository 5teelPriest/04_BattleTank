// Copyright Fisher-Studios 2018

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Logic that controls behavior of AI tanks on the battlefield
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void Tick(float DeltaTime) override;

private:

	//How close AI moves to player before stopping
	float AcceptanceRadius = 1000.0f;
};
