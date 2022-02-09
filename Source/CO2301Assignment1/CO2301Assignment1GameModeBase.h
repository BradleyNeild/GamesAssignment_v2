// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CO2301Assignment1GameModeBase.generated.h"

/**
 *
 */
UCLASS()
class CO2301ASSIGNMENT1_API ACO2301Assignment1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ACO2301Assignment1GameModeBase();

	UFUNCTION()
		void PointScored();

private:
	UFUNCTION()
		void StartGame();
	UFUNCTION()
		void GameOver();
};
