// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ShootPlayer.generated.h"

/**
 *
 */
UCLASS()
class CO2301ASSIGNMENT1_API UBTTask_ShootPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		float Damage = 5.0f;

	UPROPERTY(EditAnywhere)
		USoundBase* ShootSound;
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
