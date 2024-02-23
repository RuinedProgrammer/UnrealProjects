// Fill out your copyright notice in the Description page of Project Settings.


#include "TTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UTTask_ClearBlackboardValue ::UTTask_ClearBlackboardValue()
 {
    NodeName = TEXT("Clear Blackboarde Value";)
 }

EBTNodeResult::Type UTTask_ClearBlackboardValue:: ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
      Super:: ExecuteTask(OwnerComp, NodeMemory);
      OwnerComp.GetBlackboardComponent() -> ClearValue(GetSelectedBlackboardKey());
      return  EBTNodeResult::Succeeded;
}