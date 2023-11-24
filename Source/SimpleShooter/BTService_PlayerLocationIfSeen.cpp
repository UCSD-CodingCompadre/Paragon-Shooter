// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"


UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{

    // Set the node name
    NodeName = TEXT("Update Player Pawn Location If Seen");    
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    // Call the parent method
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Hold the player pawn
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // Return if the player pawn is null
    if(playerPawn == nullptr) return;

    // Hold the ai controller 
    AAIController* aiController = OwnerComp.GetAIOwner();

    // Return if the ai controller is null
    if(aiController == nullptr) return;

    // Hold the blackboard component
    UBlackboardComponent* aiBlackboard = OwnerComp.GetBlackboardComponent();

    // Check if the ai controller has the player pawn in sight
    if(aiController->LineOfSightTo(playerPawn)) 
    {

        // Set the blackboard value using the player pawn
        aiBlackboard->SetValueAsObject(GetSelectedBlackboardKey(), playerPawn);
    }

    // Else we can clear the value
    else
    {

        // Clear the blackboard value
        aiBlackboard->ClearValue(GetSelectedBlackboardKey());
    }
}

