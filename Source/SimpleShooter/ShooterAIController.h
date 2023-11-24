// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:	

	// Called every frame
	virtual void Tick(float deltaSeconds) override;

	/*
	Check if the pawn is dead
	@param none
	@return bool true if the pawn is dead
	*/
	bool isDead() const;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

private:

	// Hold the AI's behavior tree
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* aiBehaviorTree;

	// Hold the AI's blackboard
	UPROPERTY(VisibleAnywhere)
	class UBlackboardComponent* aiBlackboard;

	// Hold a pointer to the AI pawn
	UPROPERTY()
	APawn* aiPawn;

	// Hold a pointer to the player pawn
	UPROPERTY()
	APawn* playerPawn;

	// Hold if the player pawn is in view
	UPROPERTY()
	bool playerPawnIsVisible = false;

};
