// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController())
	{
		HudWidget = CreateWidget<UHUDWidget>(this, HudWidgetClass);
		if (HudWidget)
		{
			HudWidget->AddToViewport();
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
