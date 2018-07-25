// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("Throttle Value: %.2f"), Throttle)
	
	//TODO Clamp throttle value
	Throttle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	FVector ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);

	return;
}


