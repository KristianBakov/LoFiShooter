// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "LoFiPlayerCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	if (!AIOwner) return EBTNodeResult::Failed;


	ALoFiPlayerCharacter* PlayerCharacter = Cast<ALoFiPlayerCharacter>(AIOwner->GetPawn());
	if (!PlayerCharacter) return EBTNodeResult::Failed;

	PlayerCharacter->Shoot();

	return EBTNodeResult::Succeeded;
}
