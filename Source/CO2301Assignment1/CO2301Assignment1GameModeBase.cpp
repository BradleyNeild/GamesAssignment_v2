// Copyright Epic Games, Inc. All Rights Reserved.


#include "CO2301Assignment1GameModeBase.h"
#include "MyPlayerController.h"


ACO2301Assignment1GameModeBase::ACO2301Assignment1GameModeBase() {
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void ACO2301Assignment1GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

void ACO2301Assignment1GameModeBase::PointScored()
{
	UE_LOG(LogTemp, Warning, TEXT("Point Scored!"));

}

void ACO2301Assignment1GameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Started!"));

}

void ACO2301Assignment1GameModeBase::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
}
