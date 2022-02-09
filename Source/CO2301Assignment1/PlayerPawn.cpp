// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h" 

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	SetRootComponent(PlayerMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArm->SetupAttachment(PlayerMesh);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 5.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(20.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::TurnUp(float Value)
{
	if (Controller && Value != 0.0f)
	{
		float RotateAmount = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	}
}

void APlayerPawn::TurnRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		float RotateAmount = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
		FRotator Rotation = FRotator(0.0f, RotateAmount, 0.0f);
		FQuat DeltaRotation = FQuat(Rotation);
		AddActorLocalRotation(DeltaRotation, true);
	}
}

void APlayerPawn::MoveForward(float Value)
{

	if (Controller && Value != 0.0f)
	{
		FVector DeltaLocation = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);
		AddActorLocalOffset(DeltaLocation, true);
	}
}

void APlayerPawn::MoveRight(float Value)
{

	if (Controller && Value != 0.0f)
	{
		FVector DeltaLocation = FVector(0.0f, Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f);
		AddActorLocalOffset(DeltaLocation, true);
	}
}

void APlayerPawn::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Point Scored!"));

}

void APlayerPawn::StopJumping()
{

}