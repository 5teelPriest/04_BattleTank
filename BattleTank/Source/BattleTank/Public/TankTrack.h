// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
private:

	float MaxTrackDrivingForce = 130000000.0f; //Assuming 65 ton tank that can accelerate from 0 to 45 mph in 5 seconds

};
