// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTask_Shoot();

protected:

	/*
	The task to be exectured in the ai behavior tree
	@param UBehaviorTreeComponent OwnerComp the behavior tree 
	unit8* NodeMemory the node memory of the task in the behavior tree
	@return EBTNodeResult::Type the result of the task
	*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
