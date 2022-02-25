// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkerAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AWalkerAIController::AWalkerAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWalkerAIController::BeginPlay() 
{
	Super::BeginPlay();

	//Run AI behavior tree
	//Requirement 21, 22
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}

}

void AWalkerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Set blackboard PlayerPosition vector to player's position
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());

}

void AWalkerAIController::FindPlayer()
{
	

}
