// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterCharacter.h"
#include "AIController.h"


UBTTask_Shoot::UBTTask_Shoot()
{

    // Set the name for the node
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{

    // Call the parent method
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Hold the ai controller 
    AAIController* aiController = OwnerComp.GetAIOwner();

    // Check if the ai controller is null and return failed
    if(aiController == nullptr) return EBTNodeResult::Failed;

    // Get the character from the controller
    AShooterCharacter* aiShooterCharacter = Cast<AShooterCharacter>(aiController->GetPawn());

    // Check if the character is null and return failed
    if(aiShooterCharacter == nullptr) return EBTNodeResult::Failed;

    // Use the character to handle the gun shot
    aiShooterCharacter->handleGunShot();

    // Return succeeded
    return EBTNodeResult::Succeeded;
}
