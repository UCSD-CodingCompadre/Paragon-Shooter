// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SinglePlayerGameMode.h"
#include "SinglePlayerGameMode_KillThemAll.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASinglePlayerGameMode_KillThemAll : public ASinglePlayerGameMode
{
	GENERATED_BODY()

public:

	/*
	Handles the death of a pawn in the Kill Them All game mode
	@param APawn* pawnKilled the pawn killed
	@return void
	*/
	virtual void PawnKilled(APawn* pawnKilled) override;

private:

	/*
	Handles the game ending depending if the player won
	@param bool playerWon true if the player won the game
	@return void
	*/
	void endGame(bool playerWon);
	
};
