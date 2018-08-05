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
	UE_LOG(LogTemp, Warning, TEXT("On Ground"))

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
	if (!ensure(TankRoot)) { return; }
	Throttle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	FVector ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);

	return;
}



