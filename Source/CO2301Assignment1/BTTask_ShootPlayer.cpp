// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
	APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UGameplayStatics::ApplyDamage(
		PlayerPawn, //actor that will be damaged
		Damage, //the base damage to apply              MAGIC NUMBER!!!!!!!!!!!!!!!!!!!!!!!!!!
		AIActor->GetInstigatorController(), //controller that caused the damage
		AIActor, //Actor that actually caused the damage
		UDamageType::StaticClass() //class that describes the damage that was done
	);
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		ShootSound,
		AIActor->GetActorLocation(),
		4.0f,
		1.0f,
		0.0f);

	return EBTNodeResult::Succeeded;
}
