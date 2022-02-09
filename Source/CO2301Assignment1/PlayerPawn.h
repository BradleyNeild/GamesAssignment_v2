// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CO2301ASSIGNMENT1_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void TurnRight(float Value);
	UFUNCTION()
		void TurnUp(float Value);
	UFUNCTION()
		void Jump();
	UFUNCTION()
		void StopJumping();



	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float RotationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
		USpringArmComponent* SpringArm;
};
