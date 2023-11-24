// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SinglePlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASinglePlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	/*
	Base method that handles the death of a pawn
	@param APawn* pawnKilled the pawn killed
	@return void
	*/
	virtual void PawnKilled(APawn* pawnKilled);
};
