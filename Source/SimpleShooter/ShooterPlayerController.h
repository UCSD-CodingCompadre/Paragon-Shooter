// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ShooterPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:


	/*
	Ends the game for the controller
	@param AActor* EndGameFocus the focus actor
	bool bIsWinner true if the game ended with the owner winning
	@return void
	*/
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:

	/*
	Handles the widgets when the game begins
	@param none
	@return void
	*/
	virtual void BeginPlay() override;

private:

	// Hold the lose screen widget blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> loseScreenBlueprint;
	
	// Hold the win screen widget blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> winScreenBlueprint;
	
	// Hold the hud widget blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> hudBlueprint;

	// Hold the restart delay
	UPROPERTY(EditAnywhere)
	float restartDelay = 5.0f;

	// Hold the pointer to the hud widget
	UUserWidget* hudWidget;

	// Hold the restart timer
	FTimerHandle restartTimer;
};
