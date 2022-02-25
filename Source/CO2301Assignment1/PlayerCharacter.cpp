// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h" 
#include "Camera/CameraComponent.h"
#include "PlayerProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "MyCustomGameMode.h"
#include "EnemyCharacter.h"
#include "DestructibleComponent.h"
#include "Components/SceneCaptureComponent2D.h"

#include "Crate.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Requirement 8
	MapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Map Arm"));
	MapArm->SetupAttachment(RootComponent);

	MapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Map Camera"));
	MapCamera->SetupAttachment(MapArm);
	MapArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 8.0f;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->CameraRotationLagSpeed = 8.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(20.0f, 0.0f, 0.0f));

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh());
	ProjectileSpawnPoint->SetRelativeLocation(FVector(80.0f, 0.0f, 20.0f));
}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void APlayerCharacter::TurnRight(float Value)
{
	AddControllerYawInput(Value);
}

void APlayerCharacter::TurnUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::Fire1()
{
	//Spawn a projectile at designated spawn point and play a sound effect
	//Requirement 7, 13
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	APlayerProjectile* TempProj = GetWorld()->SpawnActor<APlayerProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	TempProj->SetOwner(this);

	//Play shooting sound
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		ShootSound,
		GetActorLocation(),
		8.0f,
		0.1f,
		0.0f);
}

void APlayerCharacter::Fire2()
{
	//Raycast attack
	AController* ControllerRef = GetController();
	FVector CameraLocation;
	FRotator CameraRotation;
	ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector End = CameraLocation + CameraRotation.Vector() * CastRange;

	FHitResult Hit;
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_Visibility);


	if (bDidHit)
	{

		AActor* HitActor = Hit.GetActor();

		if (HitActor->GetClass()->IsChildOf(AEnemyCharacter::StaticClass()))
		{
			UGameplayStatics::ApplyDamage(
				HitActor, //actor that will be damaged
				CastDamage, //the base damage to apply
				GetController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);

		}
		else if (HitActor->GetClass()->IsChildOf(ACrate::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit box!: %s"), *Hit.GetActor()->GetName());
			//Get destructible component
			UDestructibleComponent* DestructibleMesh = Cast<UDestructibleComponent>(Hit.Component);
			if (DestructibleMesh && HitActor->IsRootComponentMovable())
			{
				//Add impulse force in direction player shot at
				FVector Forward = this->GetActorForwardVector();
				DestructibleMesh->AddImpulse(Forward * CastForce * DestructibleMesh->GetMass());
			}


		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Missed!"));

		}
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ShootSound,
			GetActorLocation(),
			8.0f,
			8.0f,
			0.0f);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//If you are being healed
	if (DamageAmount < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("I got healed"));

		Health -= DamageAmount;
		if (Health > 100.0f)
		{
			Health = 100.0f;
		}
	}
	//If you are taking damage
	else if (!IsInvincible)
	{
		UE_LOG(LogTemp, Warning, TEXT("I got hit"));
		Health -= DamageAmount;

		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			HurtSound,
			GetActorLocation(),
			4.0f,
			1.0f,
			0.0f);

		//If you die
		if (Health <= 0)
		{
			//Call GameOver from GameMode class
			AMyCustomGameMode* currentGameMode = GetWorld()->GetAuthGameMode<AMyCustomGameMode>();

			currentGameMode->GameOver();
			UE_LOG(LogTemp, Warning, TEXT("I DIED!!!"));
		}
		else
		{
			//Grant a short grace period where the player cannot take damage
			//The timer will end the grace period after a short time
			IsInvincible = true;

			GetWorld()->GetTimerManager().SetTimer(GracePeriodTimer, this, &APlayerCharacter::EndGracePeriod, GracePeriodDuration, false);

		}
	}

	return 0.0f;
}

void APlayerCharacter::EndGracePeriod()
{
	IsInvincible = false;
}

