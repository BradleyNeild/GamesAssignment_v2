// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyCharacter;

UCLASS()
class CO2301ASSIGNMENT1_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

	void SpawnEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemyCharacter> DefaultEnemyClass;

	UPROPERTY()
		FTimerHandle SpawnTimer;
	UPROPERTY()
		float TimerDuration = 2.0f;

};
