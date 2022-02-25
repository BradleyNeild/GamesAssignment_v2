// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RandomWillShoot.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "Math/UnrealMathUtility.h"

void UBTService_RandomWillShoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 5% chance to shoot at player
	if (FMath::RandRange(1, 100) > 95)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	}
}