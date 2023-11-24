// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "ShooterAIController.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the root component of the gun
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Set the mesh component of the gun
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun_Mesh"));

	// Attach the mesh component to the root component
	gunMesh->SetupAttachment(RootComponent);

}

void AGun::pullTrigger()
{

	// Spawn the muzzle flash particles
	UGameplayStatics::SpawnEmitterAttached(muzzleFlashParticles,  gunMesh, TEXT("MuzzleFlashSocket"));

	// Spawn the muzzle flash sound
	UGameplayStatics::SpawnSoundAttached(muzzleFlashSound, gunMesh, TEXT("MuzzleFlashSocket"));

	// Hold the result of the shot
	FHitResult shotResult;

	// Hold the direction of the shot
	FVector shotDirection;

	// Hold if the line trace was valid
	bool hasHit = isValidLineTrace(shotResult,  shotDirection);

	// If there is no hit return
	if(!hasHit) return;

	// Spawn the shot impact particles
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), shotImpactParticles,shotResult.ImpactPoint, shotDirection.Rotation());

	// Spawn the shot impact sound
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), shotImpactSound, shotResult.ImpactPoint, shotDirection.Rotation());

	// Get the controller of the gun owner
	AController* ownerController = getOwnerController();

	// Check if the controller belongs to the AI
	if (ownerController->IsA(AShooterAIController::StaticClass()))
	{
		// Set the new damage
		damage = 10.f;
	}

	// Hold the damage event
	FPointDamageEvent damageEvent(damage, shotResult, shotDirection, nullptr);

	// Hold the actor hit
	AActor* actorHit = shotResult.GetActor();

	// Return if there is no actor hit
	if(actorHit == nullptr) return;

	// Call the take damage function of the actor
	actorHit->TakeDamage(damage, damageEvent, ownerController, this);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{

	// Call the parent method
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{

	// Call the parent method
	Super::Tick(DeltaTime);
}

bool AGun::isValidLineTrace(FHitResult& hitResult, FVector& shotDirection)
{

	// Return false if the gun owner has no controller
	if(getOwnerController() == nullptr) return false;

	// Hold the view point location of the shot
	FVector viewPointLocation;

	// Hold the view point rotation of the shot
	FRotator viewPointRotation; 

	// Update the viewpoints
	getOwnerController()->GetPlayerViewPoint(viewPointLocation, viewPointRotation);

	// Set the shot direction
	shotDirection = -viewPointRotation.Vector();

	// Hold the end of the shot location
	FVector endOfShotLocation = viewPointLocation + viewPointRotation.Vector() * maxRange;

	// Hold the collision params
	FCollisionQueryParams params;

	// Add the gun to the collision params
	params.AddIgnoredActor(this);

	// Add the gun owner to the collision params
	params.AddIgnoredActor(GetOwner());

	// Return th result of the line trace 
	return GetWorld()->LineTraceSingleByChannel(hitResult, viewPointLocation, endOfShotLocation, ECollisionChannel::ECC_GameTraceChannel1, params);
}

AController* AGun::getOwnerController() const
{

	// Hold the pawn owner of the gun
	APawn* ownerPawn = Cast<APawn>(GetOwner());

	// Return nullptr if there is no pawn owner
	if(ownerPawn == nullptr) return nullptr;

	// Else return the controller
	return ownerPawn->GetController();
}

