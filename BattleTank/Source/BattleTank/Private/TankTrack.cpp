// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;

	return;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

	return;
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	CurrentThrottle = 0.0f;

	return;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!ensure(TankRoot)) { return; }
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	FVector CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();
	float TankMass = TankRoot->GetMass();
	FVector CorrectionForce = TankMass * CorrectionAcceleration / 2.0f;
	TankRoot->AddForce(CorrectionAcceleration);

	return;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);

	return;
}

void UTankTrack::DriveTrack()
{
	if (!ensure(TankRoot)) { return; }
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * MaxTrackDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
	return;
}



