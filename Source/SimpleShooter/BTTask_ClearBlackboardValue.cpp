// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{

    // Set the name of the node
    NodeName = TEXT("Clear Blackboard Values");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{

    // Call the parent method
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Clear the value of the blackboard component using the selected key
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    // Return succeeded
    return EBTNodeResult::Succeeded;
}

