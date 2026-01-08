// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseUserWidget.h"

#define LogAsWarning(x) UE_LOG(LogTemp, Warning, TEXT(x))

void UPauseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LogAsWarning("UPauseUserWidget::NativeConstruct: PauseMenu Created")
	SetVisibility(ESlateVisibility::Visible);
}

void UPauseUserWidget::UpdateSunIcon(bool value)
{
		if (value)
		{
			if (SunIcon && MoonIcon)
			{
				SunIcon->SetVisibility(ESlateVisibility::Visible);
				MoonIcon->SetVisibility(ESlateVisibility::Hidden);
			}
		} else
		{
			if (SunIcon && MoonIcon)
			{
				SunIcon->SetVisibility(ESlateVisibility::Hidden);
				MoonIcon->SetVisibility(ESlateVisibility::Visible);
			}
		}
}
