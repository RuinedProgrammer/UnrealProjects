// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskShoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"
 
UMyBTTaskShoot ::UMyBTTaskShoot()
 {
    NodeName = TEXT("Shoot";)
 }

EBTNodeResult::Type UMyBTTaskShoot:: ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super:: ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return  EBTNodeResult::Failed;
    }
    
    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner() -> GetPawn());
    if (Character == nullptr)
    {
        return  EBTNodeResult::Failed;
    }

    Character ->Shoot();

    return  EBTNodeResult::Succeeded;
}