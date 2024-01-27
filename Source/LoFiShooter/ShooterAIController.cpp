// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LoFiPlayerCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		BlackboardComponent = GetBlackboardComponent();
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		if (BlackboardComponent && PlayerPawn)
		{
			BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		}
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
	ALoFiPlayerCharacter* ControlledCharacter = Cast<ALoFiPlayerCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}
