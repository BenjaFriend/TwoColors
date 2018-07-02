// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Collection Sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->AttachTo(RootComponent);
	CollisionSphere->SetSphereRadius(5.f);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlapEnd);

	RootComponent = CollisionSphere;

	// Create the projectile mesh
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->bCastDynamicShadow = false;		// Disallow mesh to cast dynamic shadows
	ProjectileMesh->CastShadow = false;				// Disallow mesh to cast other shadows
	ProjectileMesh->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.0f;

	// Set default values
	Speed = 3000.f;
	Damage = 20.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::OnConstruction(const FTransform& Transfrom)
{
	Super::OnConstruction(Transfrom);

	MyVelocity = GetActorForwardVector() * Speed;

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the actor with sweep
	SetActorLocation(GetActorLocation() + MyVelocity * DeltaTime, true);

}

void AProjectile::SetDamage(float Value)
{
	Damage = Value;
}

void AProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If I am colliding with my own institgator then do nothing
	if (OtherActor->Instigator == Instigator) return;

	// Check if this is a damageable item
	AEnemy* HitEnemy = Cast<AEnemy>(OtherActor);
	if (HitEnemy)
	{
		// If we are the type of projectile to damage this enemy type...
		if (HitEnemy->GetEnemyType() == EnemyType)
		{
			// Apply damage to that 
			HitEnemy->UpdateDamage(-Damage);
			// Destroy myself
			Destroy();
		}
	}

}

void AProjectile::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// TODO: Not 100% sure if I want to use this or not yet
}