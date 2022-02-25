// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Heart.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AEnemyCharacter::OnHit);
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	//If dead
	if (Health <= 0)
	{
		//Create a health pickup and destroy self
		FVector SpawnLocation = RootComponent->GetComponentLocation();
		FRotator SpawnRotation = RootComponent->GetComponentRotation();
		AHeart* spawnedHeart = GetWorld()->SpawnActor<AHeart>(HeartClass, SpawnLocation, SpawnRotation);
		Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("Ouch!!"));
	return 0.0f;
}

void AEnemyCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		//Damage player if touched
		if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
		{
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				10.0f, //the base damage to apply              MAGIC NUMBER!!!!!!!!!!!!!!!!!!!!!!!!!!
				this->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);

		}
	}
}

