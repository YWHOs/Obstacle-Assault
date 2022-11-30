// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();

	FString myString = "My string value";

	// ulog 입력
	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %s"), *myString);
}

// Called every frame
void AMovingPlatform::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
	MovePlatform(_deltaTime);
	RotatePlatform(_deltaTime);
}

void AMovingPlatform::MovePlatform(float _deltaTime)
{
	// Reverse direction of motion if gone too far
	if(ShouldPlatformReturn())
	{
		FVector moveDirection = platformVelocity.GetSafeNormal();
		startLocation = startLocation + moveDirection * moveDistance;
		SetActorLocation(startLocation);
		platformVelocity = -platformVelocity;
	}
	else
	{
		// Move platform forwards
			// Get current location
		FVector currentLocation = GetActorLocation();
			// Add vector to that location
		currentLocation = currentLocation + (platformVelocity * _deltaTime);
		SetActorLocation(currentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float _deltaTime)
{
	// FRotator currentRotation = GetActorRotation();
	// currentRotation = currentRotation + rotationVelocity * _deltaTime;
	// SetActorRotation(currentRotation);
	AddActorLocalRotation(rotationVelocity * _deltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > moveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(startLocation, GetActorLocation());
}