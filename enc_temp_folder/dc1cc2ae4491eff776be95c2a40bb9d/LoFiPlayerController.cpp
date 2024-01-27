// Fill out your copyright notice in the Description page of Project Settings.


#include "LoFiPlayerController.h"
#include "TimerManager.h"

void ALoFiPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}
