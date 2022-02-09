// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class APlayerPawn;
class ACO2301Assignment1GameModeBase;

UCLASS()
class CO2301ASSIGNMENT1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		ACO2301Assignment1GameModeBase* GameModeRef;

		virtual void Tick(float DeltaTime) override;
		virtual void SetupInputComponent();

	UFUNCTION()
		virtual void CallMoveForward(float Value);
	UFUNCTION()
		virtual void CallMoveRight(float Value);

	UFUNCTION()
		virtual void CallTurnRight(float Value);
	UFUNCTION()
		virtual void CallTurnUp(float Value);

	UFUNCTION()
		virtual void CallJump();
	UFUNCTION()
		virtual void CallStopJumping();

	APlayerPawn* MyPawn;
};
