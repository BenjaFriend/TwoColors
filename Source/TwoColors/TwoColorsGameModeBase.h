// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwoColorsGameModeBase.generated.h"

// enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	ELeft,
	ERight,
	ENone
};

/**
 * 
 */
UCLASS()
class TWOCOLORS_API ATwoColorsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
	
	
};
