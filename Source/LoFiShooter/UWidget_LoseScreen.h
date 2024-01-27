// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWidget_LoseScreen.generated.h"

/**
 * 
 */
UCLASS()
class LOFISHOOTER_API UUWidget_LoseScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LoseLevelText;

	UFUNCTION()
	void SetResetTimer(float TimeToReset);

private:
	bool bIsResetTimerActive = false;
	float ResetTimer = 5.0f;
};
