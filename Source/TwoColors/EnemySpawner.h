// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TWOCOLORS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	/**Returns the WhereToSpawn subobject */
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	/** Find a random point within the BoxComponent */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	/** This function toggles whether or not the spawn volume spawns pickups */
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawningActive(bool bShouldSpawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* The pickup to spawn */
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemy> WhatToSpawn;

	/** The timer handling the spawning of objects */
	FTimerHandle SpawnTimer;

	/* Minimum Spawn delay. Will be divided by the DifficultyScalar every time we spawnma new item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	/* Maximum spawn delay. Will be divided by the DifficultyScalar every time we spawnma new item  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;


private:

	/** Scalar for difficulty over time. Spawn ranges are divided by this every time we spawn something  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	float DifficultyScalar;

	/** Box Component to specify where pickups should be spawned */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	/* Handle spawning a new enemy */
	void SpawnEnemy();

	/* The currrent spawn delay */
	float SpawnDelay;
	
	
};
