// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "SinglePlayerGameMode.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{

	// Call the parent method
	Super::BeginPlay();
	
	// Hold the character gun created
	characterGun = GetWorld()->SpawnActor<AGun>(gunBlueprint);

	// Hide the default gun
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// Attach the fun to the weapon socket
	characterGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_socket"));

	// Set the owner of the gun to the pawn
	characterGun->SetOwner(this);

	// Set the current health
	health = maxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{

	// Call the parent method
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	// Call the parent moethod
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the MovementX axis to the input component
	PlayerInputComponent->BindAxis(TEXT("MovementX"), this, &AShooterCharacter::handleCharacterMovementLocalX);

	// Bind the LookUp axis to the input component
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::handleCharacterLookLocalY);

	// Bind the MovementY axis to the input component
	PlayerInputComponent->BindAxis(TEXT("MovementY"), this, &AShooterCharacter::handleCharacterMovementLocalY);

	// Bind theLookRight axis to the input component
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::handleCharacterLookLocalX);

	// Bind the ControllerLookUp axis to the input component
	PlayerInputComponent->BindAxis(TEXT("ControllerLookUp"), this, &AShooterCharacter::handleControllerCharacterLookLocalY);

	// Bind the ControllerLookRight axis to the input component
	PlayerInputComponent->BindAxis(TEXT("ControllerLookRight"), this, &AShooterCharacter::handleControllerCharacterLookLocalX);

	// Bind the ShootGun action to the input component
	PlayerInputComponent->BindAction(TEXT("ShootGun"), EInputEvent::IE_Pressed, this, &AShooterCharacter::handleGunShot);

	// Bind the Jump action to the input component
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterCharacter::handleCharacterJump);
}

void AShooterCharacter::handleCharacterMovementLocalX(float scaleValue)
{

	// Add the movement in the local x axis
	AddMovementInput(GetActorForwardVector() * scaleValue);
}

void AShooterCharacter::handleCharacterLookLocalY(float scaleValue)
{

	// Add the rotation in the local pitch
	AddControllerPitchInput(scaleValue);
}

void AShooterCharacter::handleCharacterMovementLocalY(float scaleValue)
{

	// Add the movement in the local y axis
	AddMovementInput(GetActorRightVector() * scaleValue);
}

void AShooterCharacter::handleCharacterLookLocalX(float scaleValue)
{

	// Add the rotation in the local yaw
	AddControllerYawInput(scaleValue);
}

void AShooterCharacter::handleCharacterJump()
{

	// Call the characters jump method
	ACharacter::Jump();
}

void AShooterCharacter::handleControllerCharacterLookLocalY(float scaleValue)
{

	// Add the rotation using the controller in the local pitch
	AddControllerPitchInput(scaleValue * rotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::handleControllerCharacterLookLocalX(float scaleValue)
{

	// Add the rotation using the controller in the local yaw
	AddControllerYawInput(scaleValue * rotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::handleGunShot()
{

	// Pull the trigger on the gun actor
	characterGun->pullTrigger();
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	// Hold the damage applied
	float damageApplied = Super::TakeDamage( DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	// Subtract the damage from the health
	health-=damageApplied;

	// Check if the pawn is dead
	if(isDead())
	{
		
		// Disable the capsule component's collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Hold the game mode
		ASinglePlayerGameMode* gameMode = GetWorld()->GetAuthGameMode<ASinglePlayerGameMode>();

		// Check if the game mode is not null
		if(gameMode != nullptr)
		{

			// Handle the pawn death using the game mode
			gameMode->PawnKilled(this);
		}

		// Detatch the controller
		DetachFromControllerPendingDestroy();
	}

	// Return the current health
	return health;
}

bool AShooterCharacter::isDead() const
{

	// Return if the health is less than or equal to 0
	return health <= 0;
}

float AShooterCharacter::getHealth() const
{

	// Return the health percentage
	return health/maxHealth;
}



