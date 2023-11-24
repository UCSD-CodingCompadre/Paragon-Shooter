// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{

    // Call the parent method
    Super::BeginPlay();

    // Get the AI pawn
    aiPawn = GetPawn();

    // Set the player pawn
    playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // Check if the behavior tree is not null
    if(aiBehaviorTree != nullptr) 
    {

        // Run the behavior tree
        RunBehaviorTree(aiBehaviorTree);

        // Get the blackboard component
        aiBlackboard = GetBlackboardComponent();

        // Set the ai's pawn location in the blackboard
        aiBlackboard->SetValueAsVector(TEXT("AIPawnLocation"), aiPawn->GetActorLocation());
    }

}

void AShooterAIController::Tick(float deltaSeconds)
{

    // Call the parent method
    Super::Tick(deltaSeconds);
}

bool AShooterAIController::isDead() const
{

    // Hold the character of the pawn
    AShooterCharacter* playerCharacter = Cast<AShooterCharacter>(GetPawn());

    // Check if there is a character
    if(playerCharacter != nullptr)
    {

        // Check if the character is dead
        return playerCharacter->isDead();
    }

    // Else the AI pawn is dead
    return true;
}
