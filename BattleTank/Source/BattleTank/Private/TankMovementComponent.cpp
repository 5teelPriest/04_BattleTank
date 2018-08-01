// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	return;
}

void UTankMovementComponent::IntendForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	return;
}

void UTankMovementComponent::IntendRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	return;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AITankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AITankForwardIntendVector = MoveVelocity.GetSafeNormal();

	float AITankForwardThrow = FVector::DotProduct(AITankForwardVector, AITankForwardIntendVector);
	IntendForward(AITankForwardThrow);
	float AITankRightThrow = FVector::CrossProduct(AITankForwardVector, AITankForwardIntendVector).Z;
	IntendRight(AITankRightThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s velocity: %s"), *GetOwner()->GetName(), *MoveVelocity.GetSafeNormal().ToString())

	return;
}