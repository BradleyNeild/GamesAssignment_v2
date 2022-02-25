// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyCharacter.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Crate.h"
#include "DestructibleComponent.h"


// Sets default values
APlayerProjectile::APlayerProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetSimulatePhysics(true);
	SetRootComponent(ProjectileMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 10.0f;


}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &APlayerProjectile::OnHit);

}


//Requirement 4, 7, 12, 13
void APlayerProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor)
	{
		//If the projetile hits an enemy
		if (OtherActor->GetClass()->IsChildOf(AEnemyCharacter::StaticClass()) || (OtherActor->GetClass()->IsChildOf(ACrate::StaticClass())))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit!!"));
			AActor* ProjectileOwner = GetOwner();
			//Make sure ProjectileOwner is not null
			if (!ProjectileOwner)
			{
				return;
			}
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				Damage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);

		}
	}

	Destroy();
}

// Called every frame
void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

