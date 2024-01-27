// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget_LoseScreen.h"
#include "Components/TextBlock.h"


void UUWidget_LoseScreen::NativeConstruct()
{
	Super::NativeConstruct();
	bIsResetTimerActive = true;
}

void UUWidget_LoseScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(bIsResetTimerActive)
	{
		ResetTimer -= InDeltaTime;
		LoseLevelText->SetText(FText::FromString("Level will restart in " + FString::FromInt(ResetTimer) + " seconds."));

		if(ResetTimer <= 0)
		{
			bIsResetTimerActive = false;
			ResetTimer = 0;
		}
	}
}

void UUWidget_LoseScreen::SetResetTimer(float TimeToReset)
{
	ResetTimer = TimeToReset;
}
