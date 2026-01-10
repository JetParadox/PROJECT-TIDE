// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DaySwitchUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_TIDE_API UDaySwitchUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* TimerValue;

	void UpdateTimerValue(int32 Value);
};

