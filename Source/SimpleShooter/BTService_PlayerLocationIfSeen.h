// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_PlayerLocationIfSeen();	

protected:

	/*
	The service running every tick
	@param UBehaviorTreeComponent OwnerComp the behavior tree of the service
	unit8* NodeMemory the location of the service in the behavior tree
	float DeltaSeconds the time of the frame 
	*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
