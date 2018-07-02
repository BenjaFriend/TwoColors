// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	EnemyType = EEnemyType::ENone;

	Health = 100.f;
}


void AEnemy::UpdateDamage(float Damage)
{
	Health += Damage;

	if (Health <= 0.f)
	{
		Die();
	}
}

void AEnemy::Die()
{

	// Just destory myself for now
	Destroy();
}