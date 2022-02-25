// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WalkerAIController.generated.h"

/**
 *
 */
UCLASS()
class CO2301ASSIGNMENT1_API AWalkerAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWalkerAIController();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;

	void FindPlayer();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		FTimerHandle FindPathTimer;
	UPROPERTY()
		float TimerDuration = 0.5f;

};
