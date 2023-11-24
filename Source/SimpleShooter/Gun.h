// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void pullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Hold the mesh of the gun
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* gunMesh;

	// Hold the muzzle flash particles
	UPROPERTY(EditAnywhere)
	UParticleSystem* muzzleFlashParticles;
	
	// Hold the muzzle flash sound
	UPROPERTY(EditAnywhere)
	USoundBase* muzzleFlashSound;

	// Hold the shot impact particles
	UPROPERTY(EditAnywhere)
	UParticleSystem* shotImpactParticles;

	// Hold the shot impact sound
	UPROPERTY(EditAnywhere)
	USoundBase* shotImpactSound;

	// Hold the max range of the gun
	UPROPERTY(VisibleAnywhere)
	float maxRange = 1500.f;

	// Hold the damage of the gun
	UPROPERTY(VisibleAnywhere)
	float damage = 50.f;

	/*
	Handles if the line trace is valid
	@param FHitResult hitResult the result of the line trace
	FVector shotDirection the direction of the line trace
	@return bool true if the line trace is valid
	*/
	bool isValidLineTrace(FHitResult& hitResult, FVector& shotDirection);

	/*
	Get the controller of the gun owner
	@param none
	@return AController* the pointer to the controller of the gun owner
	*/
	AController* getOwnerController() const;
};
