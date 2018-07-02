// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TwoColorsGameModeBase.h"

#include "Enemy.generated.h"



UCLASS()
class TWOCOLORS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	/** Update the damage done to this enemy  */
	UFUNCTION(BlueprintCallable)
	void UpdateDamage(float Damage);

	/** Return the mesh for the pickup **/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EEnemyType GetEnemyType() const { return EnemyType; }

	/** Return the mesh for the pickup **/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const { return Health; }

private:

	/** Handle the death of this enemy */
	UFUNCTION(BlueprintCallable)
	void Die();
	
	/** The enym type of this object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	EEnemyType EnemyType;

	/** The current health of this enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	float Health;

};
