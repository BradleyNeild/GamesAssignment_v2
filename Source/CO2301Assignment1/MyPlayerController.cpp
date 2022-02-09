// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Components/InputComponent.h"
//#include "MyMovementComponent.h"
#include "PlayerPawn.h"
#include "CO2301Assignment1GameModeBase.h"

AMyPlayerController::AMyPlayerController() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = Cast<APlayerPawn>(GetPawn());
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis("Forward", this, &AMyPlayerController::CallMoveForward);
	InputComponent->BindAxis("Right", this, &AMyPlayerController::CallMoveRight);
	InputComponent->BindAxis("LookRight", this, &AMyPlayerController::CallTurnRight);
	InputComponent->BindAxis("LookUp", this, &AMyPlayerController::CallTurnUp);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::CallJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::CallStopJumping);
}

void AMyPlayerController::CallMoveForward(float Value)
{
	if (MyPawn)
	{
		MyPawn->MoveForward(Value);
	}
}

void AMyPlayerController::CallMoveRight(float Value)
{
	if (MyPawn)
	{
		MyPawn->MoveRight(Value);
	}
}

void AMyPlayerController::CallTurnRight(float Value)
{
	if (MyPawn)
	{
		MyPawn->TurnRight(Value);
	}
}

void AMyPlayerController::CallTurnUp(float Value)
{
	if (MyPawn)
	{
		MyPawn->TurnUp(Value);
	}
}

void AMyPlayerController::CallJump()
{
	if (MyPawn)
	{
		MyPawn->Jump();
	}
}

void AMyPlayerController::CallStopJumping()
{
	if (MyPawn)
	{
		MyPawn->StopJumping();
	}
}
