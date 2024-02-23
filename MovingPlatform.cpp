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

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);

}

void AMovingPlatform :: MovePlatform(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Reverse direction if gone too far
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrLocation = GetActorLocation();
		CurrLocation = CurrLocation + PlatformVelocity ;
		SetActorLocation(CurrLocation);
	}
}

void AMovingPlatform :: RotatePlatform(float DeltaTime) 
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform :: ShouldPlatformReturn() 
{
	float DistanceMoved =	FVector :: Dist(StartLocation, GetActorLocation());
	return DistanceMoved > MovedDistance;
}
