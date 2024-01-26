// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	if (BlackboardComponent && PlayerPawn)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
			BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		}
		else
		{
			BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
		}
	}
}
