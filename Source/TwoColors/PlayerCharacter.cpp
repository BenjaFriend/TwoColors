// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Projectile.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;

	// Create the projectile mesh
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StartHealth = 100.f;
	Health = StartHealth;
}

//////////////////////////////////////////////////////////////////////////
// Input

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup action bindings for shooting
	PlayerInputComponent->BindAction("ShootRight", IE_Pressed, this, &APlayerCharacter::ShootRight);
	PlayerInputComponent->BindAction("ShootLeft", IE_Pressed, this, &APlayerCharacter::ShootLeft);

	// Setup axis bindings for movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);

}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}

}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::ShootRight()
{
	// Spawn the right projectile here
	FireProjectile(true);

}

void APlayerCharacter::ShootLeft()
{
	// Spawn the left projectile here
	FireProjectile(false);
}

////////////////////////////////////////////////////////////////////////////
// Gameplay

void APlayerCharacter::FireProjectile(bool IsRight)
{
	// Fire projectile
	UWorld* const World = GetWorld();
	if (World && RightProjectileClass && LeftProjectileClass)
	{
		// Set the paramaters so that we know who the owner of this projectile is
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		
		// Use the current rotation o fhte player
		const FRotator SpawnRotation = GetControlRotation();

		// Use the muzzle location or the players current location if hta tis null
		const FVector SpawnLocation =
			((Muzzle != nullptr) ? Muzzle->GetComponentLocation() : GetActorLocation());

		// Spawn the actor
		AProjectile* Projectile = World->SpawnActor<AProjectile>(
			( IsRight  ? RightProjectileClass : LeftProjectileClass ),
			SpawnLocation,
			SpawnRotation,
			SpawnParams);
	}
}

void APlayerCharacter::UpdateHealth(float Value)
{
	Health += Value;

	// Check if we are dead
	if (Health <= 0.f)
	{
		Die();
	}
}

bool APlayerCharacter::IsDead() const
{
	return Health > 0.f;
}

void APlayerCharacter::Die()
{


	// Tell the game mode that we have died
	UE_LOG(LogTemp, Error, TEXT("Player Die!"));


}