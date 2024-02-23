// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Simple_ShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API ASimple_ShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKiller(APawn* PawnKilled);
	
};
