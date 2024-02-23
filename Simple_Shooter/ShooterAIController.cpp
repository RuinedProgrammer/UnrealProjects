// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController:: BeginPlay()
{
    Super::BeginPlay();

   //APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

   
    
    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent() -> SetValueAsVector(TEXT("StartLocation"), GetPawn() -> GetActorLocation());
    }

    
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    /*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    //MoveToActor(PlayerPawn, 200);
    if(LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent() -> SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn -> GetActorLocation());
        GetBlackboardComponent() -> SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn -> GetActorLocation());
    }

    else
    {
        GetBlackboardComponent() -> ClearValue(TEXT("PlayerLocation"));
    }
*/
        
}

bool AShooterAIController::Ded() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter -> Ded();
    }
    return true;
}