// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Simple_ShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AKillEmAllGameMode : public ASimple_ShooterGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKiller(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
	
};
