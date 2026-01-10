// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

#define LogAsWarning(x) UE_LOG(LogTemp, Warning, TEXT(x))

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController())
	{		
		//Getting Reference to character for Resets
		PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (PlayerCharacter)
		{
			StartingPlayerLocation = PlayerCharacter->GetActorLocation();
		}

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

// Disable or Enable Day Transition UI
void ABasePlayerController::ShowDayTransitionUI(bool value)
{
	if (IsLocalController())
	{
		if (value == true)
		{
			DayTransitionWidget = CreateWidget<UDaySwitchUI>(this, DayTransitionWidgetClass);
			if (DayTransitionWidget)
			{
				DayTransitionWidget->AddToViewport(10);
			}
			
		} else
		{
			if (DayTransitionWidget)
			{
				DayTransitionWidget->RemoveFromParent();
				DayTransitionWidget = nullptr;
			}
		}
	}
}

// Update Day Transition Timer Value
void ABasePlayerController::UpdateDayTransitionUI(int32 value)
{
	if (DayTransitionWidget)
	{
		DayTransitionWidget->UpdateTimerValue(value);
	}
}


// Open or Close Pause Menu
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

//Reset Player position
void ABasePlayerController::ResetPlayerTransforms()
{
	//Reset Player Position and Rotation at the start of a new day
	if (PlayerCharacter)
	{
		PlayerCharacter->SetActorLocation(StartingPlayerLocation);
	}
}


