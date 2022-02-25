// Fill out your copyright notice in the Description page of Project Settings.


#include "Heart.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHeart::AHeart()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	MyCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	MyCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHeart::BeginPlay()
{
	Super::BeginPlay();
	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &AHeart::OnOverlapBegin);


}

//Requirement 15
void AHeart::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		//Heal the player if they touch this
		UGameplayStatics::ApplyDamage(OtherActor, -AmountToHeal, OtherActor->GetInstigatorController(), this, UDamageType::StaticClass());
		Destroy();
	}
	
}

// Called every frame
void AHeart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

