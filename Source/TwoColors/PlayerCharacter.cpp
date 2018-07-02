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

}

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
	// Shoot right
	UE_LOG(LogTemp, Warning, TEXT("Shoot right!"));
	// Spawn the right projectile here
	FireProjectile(true);

}

void APlayerCharacter::ShootLeft()
{
	// Shoot left
	UE_LOG(LogTemp, Warning, TEXT("Shoot left!"));

	// Spawn the left projectile here
	FireProjectile(false);
}

void APlayerCharacter::FireProjectile(bool IsRight)
{
	// Fire projectile
	UWorld* const World = GetWorld();
	if (World && RightProjectileClass && LeftProjectileClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		const FRotator SpawnRotation = GetControlRotation();

		const FVector SpawnLocation =
			((Muzzle != nullptr) ? Muzzle->GetComponentLocation() : GetActorLocation());// +SpawnRotation.RotateVector(FVector(100.0f, 0.0f, 10.0f));

		AActor* Projectile = World->SpawnActor<AActor>(
			( IsRight  ? RightProjectileClass : LeftProjectileClass ),
			SpawnLocation,
			SpawnRotation,
			SpawnParams);
	}
}