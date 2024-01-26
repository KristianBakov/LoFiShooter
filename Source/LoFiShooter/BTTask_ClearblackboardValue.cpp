// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearblackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearblackboardValue::UBTTask_ClearblackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearblackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
