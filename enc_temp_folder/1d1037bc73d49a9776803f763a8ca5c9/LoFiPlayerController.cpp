// Fill out your copyright notice in the Description page of Project Settings.


#include "LoFiPlayerController.h"
#include "TimerManager.h"
#include "UWidget_LoseScreen.h"

void ALoFiPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	LoseScreen = CreateWidget<UUWidget_LoseScreen>(this, LoseScreenClass);
	if (LoseScreen)
	{
		LoseScreen->SetResetTimer(RestartDelay);
		LoseScreen->AddToViewport();
	}

	CurrentRestartDelay = RestartDelay;
	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);

}