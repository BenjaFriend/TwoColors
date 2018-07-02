// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TwoColorsGameModeBase.h"

#include "Projectile.generated.h"

UCLASS()
class TWOCOLORS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Called when an instance of this class is placed (in editor) or spawned.
	* @param The transform the actor was constructed at
	*/
	virtual void OnConstruction(const FTransform& Transform) override;

	////////////////////////////////////////////////////////////////////
	// Accessors

	/** Public accessor for the projectile mesh */
	FORCEINLINE class UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Public accessor for sphere component */
	FORCEINLINE class USphereComponent* GetCollisionSphere() const { return CollisionSphere; }
	/** Public accessor for speed */
	FORCEINLINE float GetSpeed() const { return Speed; }
	/** Public accessor for damage */
	FORCEINLINE float GetDamage() const { return Damage; }
	/** Return the mesh for the pickup **/
	FORCEINLINE EEnemyType GetEnemyType() const { return EnemyType; }
	/** Setter for the damage value */
	void SetDamage(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Method to handle collisions with this object */
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Method to hand enving the overlap with something */
	UFUNCTION()
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
private:

	/** Static mesh to represent the projectile */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile", Meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ProjectileMesh;

	/** The collision sphere on this projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", Meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;

	/** How fast that this projectile is going to move */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", Meta = (AllowPrivateAccess = "true"))
	float Speed;

	/** The current velocity used to move this projectile in Tick */
	FVector MyVelocity;

	/** How much damage this projectile does to damagable items on impact */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", Meta = (AllowPrivateAccess = "true"))
	float Damage;

	/** The type of enemy that this object will do damage to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	EEnemyType EnemyType;
};
