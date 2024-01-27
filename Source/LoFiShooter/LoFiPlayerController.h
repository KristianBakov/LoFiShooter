// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoFiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LOFISHOOTER_API ALoFiPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;
	float CurrentRestartDelay = 5.f;

	FTimerHandle RestartTimerHandle;
	class UUWidget_LoseScreen* LoseScreen;
	class UUserWidget* HUDWidget;
	
};
