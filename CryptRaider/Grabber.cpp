// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Got Physics Handle: %s"), *PhysicsHandle -> GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Handle"));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UPhysicsHandleComponent* PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();

	 if(PhysicsHandle && PhysicsHandle -> GetGrabbedComponent())
	 {
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle -> SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	 }

}

void UGrabber::Grab()
{
	FVector Start = GetComponentLocation();
	FVector End = Start +(GetForwardVector() * MaxGrabDistance); 
	DrawDebugLine(GetWorld(),Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);
	
	FCollisionShape Sphere = FCollisionShape :: MakeSphere (GrabRadius);
	FHitResult HitResult;

	UPhysicsHandleComponent* PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle == nullptr)
	{
		return;
	}
	//bool HasHit
	if (GetWorld()-> SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent -> SetSimulatePhysics(true);
		HitComponent -> WakeAllRigidBodies();
		HitResult.GetActor() -> Tags.Add("Grabbed");
		HitResult.GetActor() -> DetachFromActor( FDetachmentTransformRules:: KeepWorldTransform);
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Yellow, false, 5);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
	
		PhysicsHandle -> GrabComponentAtLocationWithRotation(
			HitComponent, 
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

	}

}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	
	if(PhysicsHandle && PhysicsHandle -> GetGrabbedComponent())
	{
		PhysicsHandle -> GetGrabbedComponent() -> WakeAllRigidBodies();
		AActor* GrabbedActor = PhysicsHandle -> GetGrabbedComponent() -> GetOwner();
		PhysicsHandle -> ReleaseComponent();
		GrabbedActor  -> Tags.Remove("Grabbed");
	}
}