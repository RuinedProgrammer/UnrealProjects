// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKiller(APawn* PawnKilled)
{
    Super:: PawnKiller(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled -> GetController());
    if(PlayerController != nullptr)
    {
        EndGame(false);
    }
    //for loop over ShooterAI in World:
    //  Not Ded?
        //return
    //EndGame
    for(AShooterAIController* Controller: TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller -> Ded())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillEmAllGameMode:: EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller -> IsPlayerController() == bIsPlayerWinner;
        Controller -> GameHasEnded(Controller -> GetPawn(), bIsWinner);
      
    }
}