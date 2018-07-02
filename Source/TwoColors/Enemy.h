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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Return the mesh for the pickup **/
	FORCEINLINE EEnemyType GetEnemyType() const { return EnemyType; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	EEnemyType EnemyType;

};
