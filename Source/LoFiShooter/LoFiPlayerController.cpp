// Fill out your copyright notice in the Description page of Project Settings.


#include "LoFiPlayerController.h"
#include "TimerManager.h"
#include "UWidget_LoseScreen.h"

void ALoFiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!HUDWidgetClass) return;
	HUDWidget = CreateWidget(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}

void ALoFiPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		if(!WinScreenClass) return;
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		if (!LoseScreenClass) return;
		LoseScreen = CreateWidget<UUWidget_LoseScreen>(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->SetResetTimer(RestartDelay);
			LoseScreen->AddToViewport();
		}

		CurrentRestartDelay = RestartDelay;
	}

	HUDWidget->RemoveFromViewport();
	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);

}