// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TWOCOLORS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	* Update the health of the player
	* @param Value    The amount to update the players health by -- Can be positve or negative
	*/
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float Value);

	/** Returns true if players health is above 0 */
	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	/** Blueprint event to handle VFX and sounds */
	UFUNCTION(BlueprintImplementableEvent, Category = "Health", meta = (DisplayName = "Player Death ~ The Player has died"))
	void DeathEvent();

	/** Return the health of the player**/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const { return Health; }

	/** Return the starting health of the player **/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetStartHealth() const { return StartHealth; }

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/** Current health of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float Health;

	/** The health that the player starts with */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float StartHealth;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	///////////////////////////////////////////////////////////
	// Functions

	/** Handle player input on the vertical plane */
	void MoveForward(float Value);

	/** Handle player input on the horizontal plane */
	void MoveRight(float Value);
	
	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Handle the shooting of color bound to the right axis */
	void ShootRight();

	/** Handle shooting of the input bound to the left trigger */
	void ShootLeft();

	/** 
	* Fires a projectile 
	* @param IsRight  If true fire hte right projectile, else, fire the left
	*/
	void FireProjectile(bool IsRight);

	/** Handle the death of the player */
	void Die();


	///////////////////////////////////////////////////////////
	// Components

	/** The projectile that the right side shoots */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> RightProjectileClass;

	/** The projectile that this rifle shoots */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> LeftProjectileClass;

	/** The muzzle where the projectiles will come out of */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Muzzle;

};
