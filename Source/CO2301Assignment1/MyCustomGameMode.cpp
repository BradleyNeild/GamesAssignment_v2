// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCustomGameMode.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMyCustomGameMode::AMyCustomGameMode() {
	PlayerControllerClass = AMyPlayerController::StaticClass();
	PrimaryActorTick.bCanEverTick = true;

}

void AMyCustomGameMode::Tick(float DeltaTime)
{
	//Keep track of how long the player has been alive
	//Requirement 6
	if (CountTime)
	{
		TimePlayed += DeltaTime;
	}
}

void AMyCustomGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

float AMyCustomGameMode::GetTime()
{
	return TimePlayed;
}

void AMyCustomGameMode::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Started!"));
	//Start counting time now that the player is in-game
	CountTime = true;

}

void AMyCustomGameMode::GameOver()
{
	//Stop counting time
	CountTime = false;
	UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
}