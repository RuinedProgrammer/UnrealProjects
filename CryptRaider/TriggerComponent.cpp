// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    AActor* Actor = GetAcceptableActor();
    if(Mover == nullptr)
    {
        return;
    }
    
    if(Actor != nullptr)
    {  
        UPrimitiveComponent* Component =Cast<UPrimitiveComponent> (Actor -> GetRootComponent());
        if(Component != nullptr)
        {
            Component -> SetSimulatePhysics(false);
        }
        Actor -> AttachToComponent( this, FAttachmentTransformRules:: KeepWorldTransform);
        Mover -> SetShouldMove(true); 
    }
    else
    {
        Mover -> SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover; 
}
AActor* UTriggerComponent:: GetAcceptableActor() const
{
     /*TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    /*if(Actors.Num()>0)
    {
        //Actors[0].GetActorNameorLabel();
        UE_LOG(LogTemp, Display, TEXT("Got Actor: %s"), *Actors[0] ->GetActorNameOrLabel());
    }
     or
     
    int32 index= 0;
    while (index < Actors.Num())
    {
        UE_LOG(LogTemp, Display, TEXT("Got Actor: %s"), *Actors[index] ->GetActorNameOrLabel());
        ++index;
    }
    
    */
    AActor* ReturnActor = nullptr;
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for(AActor* Actor : Actors)
    {
        bool HasAcceptableTag = Actor -> ActorHasTag(AcceptableActorTag);
        bool IsGrabbed = Actor -> ActorHasTag("Grabbed");
        if(HasAcceptableTag && !IsGrabbed)
        {
            return Actor;
        }
    }
    return nullptr;
}
