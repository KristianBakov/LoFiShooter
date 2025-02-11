// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearblackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class LOFISHOOTER_API UBTTask_ClearblackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ClearblackboardValue();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
