// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APlayerProjectile;
class USceneCaptureComponent2D;

UCLASS()
class CO2301ASSIGNMENT1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRight(float Value);
	void TurnUp(float Value);
	void Fire1();
	void Fire2();
	void EndGracePeriod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		float Health = 100.0f;


private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY()
	bool IsInvincible = false;

	UPROPERTY()
		FTimerHandle GracePeriodTimer;

	UPROPERTY()
		float GracePeriodDuration = 0.3f;

	UPROPERTY(EditAnywhere)
		float CastRange = 10000.0f;

	UPROPERTY(EditAnywhere)
		float CastDamage = 50.0f;

	UPROPERTY(EditAnywhere)
		float CastForce = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "SpringArm")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "SpringArm")
		USpringArmComponent* MapArm;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APlayerProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
		USoundBase* ShootSound;

	UPROPERTY(EditAnywhere)
		USoundBase* HurtSound;

	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* MapCamera;
};