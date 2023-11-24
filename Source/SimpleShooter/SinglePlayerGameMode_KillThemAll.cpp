// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayerGameMode_KillThemAll.h"
#include "ShooterPlayerController.h"
#include "ShooterAIController.h"
#include "GameFramework/Controller.h"
#include "EngineUtils.h"

void ASinglePlayerGameMode_KillThemAll::PawnKilled(APawn* pawnKilled)
{

    // Call the parent method
    Super::PawnKilled(pawnKilled);
    
    // Hold the player's controller
    AShooterPlayerController* playerController = Cast<AShooterPlayerController>(pawnKilled->GetController());

    // Check if the player controller is null
    if(playerController != nullptr)
    {

        // End the game with the player losing
        endGame(false);
    }
    
    // Loop through the ai controllers
    for(AShooterAIController* aiController : TActorRange<AShooterAIController>(GetWorld()))
    {

        // Check if there is a controller that is not dead
        if(!aiController->isDead())
        {

            // Return
            return;
        }
    }

    // End the game with the player winning
    endGame(true);
}

void ASinglePlayerGameMode_KillThemAll::endGame(bool playerWon)
{

    // Loop through all the controllers
    for(AController* controller : TActorRange<AController>(GetWorld()))
    {

        // Hold if the player has won
        bool  isPlayerWinning = controller->IsPlayerController() == playerWon;

        // End the game through the controller
        controller->GameHasEnded(controller->GetPawn(), isPlayerWinning);
    }
}
