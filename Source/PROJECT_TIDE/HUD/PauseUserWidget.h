// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"

#include "PauseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_TIDE_API UPauseUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Pause", meta = (BindWidget))
	UImage* SunIcon;
	UPROPERTY(VisibleAnywhere, Category = "Pause", meta = (BindWidget))
	UImage* MoonIcon;

private:

	bool bIsSunIconShown;

public:
	virtual void NativeConstruct() override;

	void UpdateSunIcon(bool value);
};
