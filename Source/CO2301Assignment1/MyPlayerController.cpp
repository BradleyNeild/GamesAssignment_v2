// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Components/InputComponent.h"
#include "PlayerCharacter.h"
#include "MyCustomGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AMyPlayerController::AMyPlayerController() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = Cast<APlayerCharacter>(GetPawn());
	GameModeRef = Cast<AMyCustomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	//Control bindings
	//Requirement 11
	InputComponent->BindAxis("Forward", this, &AMyPlayerController::CallMoveForward);
	InputComponent->BindAxis("Right", this, &AMyPlayerController::CallMoveRight);
	InputComponent->BindAxis("LookRight", this, &AMyPlayerController::CallTurnRight);
	InputComponent->BindAxis("LookUp", this, &AMyPlayerController::CallTurnUp);

	InputComponent->BindAction("Fire1", IE_Pressed, this, &AMyPlayerController::CallFire1);
	InputComponent->BindAction("Fire2", IE_Pressed, this, &AMyPlayerController::CallFire2);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::CallJump);
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

void AMyPlayerController::CallFire1()
{
	if (MyPawn)
	{
		MyPawn->Fire1();
	}
}

void AMyPlayerController::CallFire2()
{
	if (MyPawn)
	{
		MyPawn->Fire2();
	}
}

float AMyPlayerController::GetHealth()
{
	if (MyPawn)
	{
		return MyPawn->Health;
	}
	else
	{
		return -1.0f;
	}
}
