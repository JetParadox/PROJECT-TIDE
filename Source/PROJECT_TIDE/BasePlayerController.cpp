// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

#define LogAsWarning(x) UE_LOG(LogTemp, Warning, TEXT(x))

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController())
	{
		HudWidget = CreateWidget<UHUDWidget>(this, HudWidgetClass);
		if (HudWidget)
		{
			HudWidget->AddToViewport(10);
		}
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) )
		{
			for (UInputMappingContext* Context : DefaultMappingContext)
			{
				Subsystem->AddMappingContext(Context, 0);
			}
		}
	}
}

void ABasePlayerController::OpenPause(bool bPause, bool bIsSunIconShown)
{
	if (IsLocalController())
	{
		if (bPause)
		{
			if (!PauseHudWidget && PauseWidgetClass)
			{
				LogAsWarning("ABasePlayerController::OpenPause: Paused")
				PauseHudWidget = CreateWidget<UPauseUserWidget>(this, PauseWidgetClass);
				if (PauseHudWidget)
				{
					PauseHudWidget->AddToViewport(10);  
					PauseHudWidget->SetVisibility(ESlateVisibility::Visible);
					PauseHudWidget->UpdateSunIcon(bIsSunIconShown);
					SetInputMode(FInputModeUIOnly());
					bShowMouseCursor = true;
				}
			}

			SetPause(true);
		} else
		{
			SetPause(false);

			if (PauseHudWidget)
			{
				PauseHudWidget->RemoveFromParent();
				PauseHudWidget = nullptr;
			}

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}
	}
}


