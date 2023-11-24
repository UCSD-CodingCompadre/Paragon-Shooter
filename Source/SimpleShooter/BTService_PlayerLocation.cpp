// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{

    // Set the name of the node
    NodeName = TEXT("Update Player Pawn Location");    
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    // Call the parent method
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Hold the player pawn
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // Return if the player pawn is null
    if(playerPawn == nullptr) return;

    // Set the blackboard value using the player pawn location
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerPawn->GetActorLocation());
}

