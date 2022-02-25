// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyCustomGameMode.generated.h"

/**
 *
 */
UCLASS()
class CO2301ASSIGNMENT1_API AMyCustomGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

	

public:
	AMyCustomGameMode();

	virtual void Tick(float DeltaTime) override;

	bool CountTime = false;


	UPROPERTY()
		float TimePlayed = 0.0f;

	UFUNCTION()
		float GetTime();

	UFUNCTION()
		void GameOver();
private:
	UFUNCTION()
		void StartGame();
	

};
