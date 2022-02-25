// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyCharacter.h"
#include "MyCustomGameMode.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::SpawnEnemy()
{
	//Spawn an enemy at this location
	FVector SpawnLocation = RootComponent->GetComponentLocation();
	FRotator SpawnRotation = RootComponent->GetComponentRotation();
	AEnemyCharacter* spawnedEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(DefaultEnemyClass, SpawnLocation, SpawnRotation);

	//Create a new timer to spawn an enemy, taking into account the time the player has survived from the GameMode to increase the rate of enemies spawned
	//Requirement 6
	AMyCustomGameMode* currentGameMode = GetWorld()->GetAuthGameMode<AMyCustomGameMode>();

	TimerDuration = (15.0f - (sqrt(currentGameMode->TimePlayed)));
	if (TimerDuration < 1.5f)
	{
		TimerDuration = 1.5f;
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, TimerDuration, false);

	UE_LOG(LogTemp, Warning, TEXT("Created timer of %f"),TimerDuration);

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	//Start spawning first enemy
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, TimerDuration, false);

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




