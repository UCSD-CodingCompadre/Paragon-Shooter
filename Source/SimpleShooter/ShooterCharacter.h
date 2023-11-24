// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.h"
#include "ShooterCharacter.generated.h"


UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	Handles taking damage from a line trace
	@param float DamageAmount the damage received
	FDamageEvent DamageEvent the type of damaged received
	AController* EventInstigator the controller that caused the damage
	AActor* DamageCauser the actor that caused the damage
	@return float the damage taken
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/*
	Check if the character is dead
	@param none
	@return bool true if the character is dead
	*/
	UFUNCTION(BlueprintPure)
	bool isDead() const;
	
	/*
	Get the character health value
	@param none
	@return float the health percantage
	*/
	UFUNCTION(BlueprintPure)
	float getHealth() const;

	/*
	Handles the line trace of the gun fired
	@param none
	@return void
	*/
	void handleGunShot();

private: 

	// Hold the rotation rate of the character
	UPROPERTY(EditAnywhere)
	float rotationRate = 90;

	// Hold the max health of the character
	UPROPERTY(EditDefaultsOnly)
	float maxHealth = 100.f;
	
	// Hold the current health of the character
	UPROPERTY(VisibleAnywhere)
	float health;

	// Hold the gun blueprint
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> gunBlueprint;

	// Hold the pointer to the gun created
	UPROPERTY()
	AGun* characterGun;

	/*
	Handles the character movement in the local X axis
	@param float scaleValue the scale value that determines the direction
	@return void
	*/
	void handleCharacterMovementLocalX(float scaleValue);

	/*
	Handles the character look in the local X axis
	@param float scaleValue the scale value that determines the direction
	@return void
	*/
	void handleCharacterLookLocalX(float scaleValue);

	/*
	Handles the character look in the local Y axis
	@param float scaleValue the scale value that determines the direction
	@return void
	*/
	void handleCharacterLookLocalY(float scaleValue);
	
	/*
	Handles the character movement in the local Y axis
	@param float scaleValue the scale value that determines the direction
	@return void
	*/
	void handleCharacterMovementLocalY(float scaleValue);

	/*
	Handles the character jumping
	@param none
	@return void
	*/
	void handleCharacterJump();

	/*
	Handles the character look with the controller in the local Y axis
	@param float scaleValue the scale value that determines the direction
	@return void
	*/
	void handleControllerCharacterLookLocalY(float scaleValue);

	/*
	Handles the character look with the controller in the local X axis
	@param float scaleValue the scale value that determines the direction
	@return void
	*/
	void handleControllerCharacterLookLocalX(float scaleValue);
};
