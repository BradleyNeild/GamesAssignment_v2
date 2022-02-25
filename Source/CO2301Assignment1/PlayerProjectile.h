// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UProjectileMovementComponent;
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.generated.h"



UCLASS()
class CO2301ASSIGNMENT1_API APlayerProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 10000.0f;
	UPROPERTY(EditAnywhere)
		float Damage = 40.0f;
	UPROPERTY(EditAnywhere)
		float Force = 1000.0f;
private:
	//Requirement 13
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
