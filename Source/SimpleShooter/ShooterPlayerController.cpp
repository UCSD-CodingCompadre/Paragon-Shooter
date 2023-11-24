// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"

void AShooterPlayerController::BeginPlay()
{

    // Call the parent method
    Super::BeginPlay();

    // Create the hud widget
    hudWidget = CreateWidget(this, hudBlueprint);

    // Check if the hud widget was created sucessfully 
    if(hudWidget != nullptr)
    {

        // Add the widget to the viewport
        hudWidget->AddToViewport(); 
    }
}  

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{

    // Call the parent method
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    // Check if the player won the game
    if(bIsWinner)
    {

        // Hold the win screen widget
        UUserWidget* winScreenWidget = CreateWidget(this, winScreenBlueprint);

        // Check if the win screen widget was created sucessfully
        if(winScreenWidget != nullptr)
        {

            // Add the win screen widget to the viewport
            winScreenWidget->AddToViewport();

            // Remove the hud widget from the viewport
            hudWidget->RemoveFromParent();
        }
    }

    // Else the player lost
    else
    {

        // Hold the lose screen widget
        UUserWidget* loseScreenWidget = CreateWidget(this, loseScreenBlueprint);

        // Check if the lose screen widget was created sucessfully
        if(loseScreenWidget != nullptr)
        {

            // Add the lose screen widget to the viewport
            loseScreenWidget->AddToViewport();

            // Remove the hud widget from the viewport
            hudWidget->RemoveFromParent();
        }
    }

    // Set the timer to restart the level
    GetWorldTimerManager().SetTimer(restartTimer, this, &APlayerController::RestartLevel, restartDelay);
} 



