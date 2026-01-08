// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_GameModeBase.h"

#include "BasePlayerController.h"
#include "Environment/TimeActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Light.h"            
#include "Components/LightComponent.h"

#define LogAsWarning(x) UE_LOG(LogTemp, Warning, TEXT(x))

AMain_GameModeBase::AMain_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AMain_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bIsEndGameTriggered = false;
	bIsSunIconShown = true;
	CurrentChangeableLightIntensity = StartIntensity;
	
	TimeToTransitionIcon = ConvertTimeToInt32(IconTransitionHours, IconTransitionMinutes, IconTransitionOnSuffix);
	TimeToTurnOn  = ConvertTimeToInt32(TurnLightsOnHours, TurnLightsOnMinutes, TurnLightsOnSuffix);
	
	UE_LOG (LogTemp, Warning, TEXT("AMain_GameModeBase::BeginPlay: Lights Will Turn On at Time in Minutes: %d"), TimeToTurnOn);
	
	//Gets all the lights with a specific tag in the level and stores them in an array for future use
	TArray<AActor*> FoundLights;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("TimeChangeableLights"), FoundLights);
	UE_LOG(LogTemp, Warning, TEXT("AMain_GameModeBase::BeginPlay: Found Lights Found in GameMode: %d"), FoundLights.Num());

	for (AActor* Actor : FoundLights)
	{
		if (ALight* Light = Cast<ALight>(Actor))
		{
			TaggedLights.Add(Light);
			if (ULightComponent* LightComp = Light->GetLightComponent())
			{
				
				LightComp->SetIntensity(0.0f);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("AMain_GameModeBase::BeginPlay: Changeable Lights Found in GameMode: %d"), TaggedLights.Num());

}

void AMain_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DayCount > TotalDays && !bIsEndGameTriggered)
	{
		//TODO: Trigger End Game Sequence
		LogAsWarning("AMain_GameModeBase::Tick: End Game Triggered");
		bIsEndGameTriggered = true;
	}
}

/*
 *Increases the Day Count by 1 and updates the HUD Widget via the PlayerController reference
 *Also passes the Current TimeActor reference to the GameMode for future use if needed
 */
void AMain_GameModeBase::IncreaseDayCount(ATimeActor *CurrentTimeActor)
{
	TimeActor = CurrentTimeActor;
	DayCount++;
	CurrentChangeableLightIntensity = StartIntensity;
	for (ALight* Light : TaggedLights)
	{
		if (ULightComponent* LightComp = Light->GetLightComponent())
		{
			LightComp->SetIntensity(0.0f);
		}
	}
	UpdateDayCountInGameMode(DayCount);
}

/*
 *Turn on Lights at Specified Time
 *Offset Time is added to the Time parameter to account for any starting time offsets in the TimeActor
 */
void AMain_GameModeBase::TurnLightsOn(int32 Time, int32 OffsetTime)
{
	//Turn on Lights at Specified Time
	if (Time+OffsetTime >= TimeToTurnOn )
	{
		for (ALight* Light : TaggedLights)
		{
			if (ULightComponent* LightComp = Light->GetLightComponent())
			{
				LightComp->SetIntensity(CurrentChangeableLightIntensity);
				CurrentChangeableLightIntensity = FMath::Min(CurrentChangeableLightIntensity + IntensityStepIncrementValue, MaxIntensity);
			}
		}
	}
}

/*
 *Transition Icons at Specified Time
 *Offset Time is added to the Time parameter to account for any starting time offsets in the TimeActor
 */
void AMain_GameModeBase::CheckTransitionIcon(int32 Time, int32 OffsetTime)
{
	//Transition Icons at Specified Time
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	HudWidget = PlayerController->HudWidget;
	if (Time+OffsetTime >= TimeToTransitionIcon && bIsSunIconShown )
	{
		if (PlayerController && HudWidget)
		{
			LogAsWarning("AMain_GameModeBase::CheckTransitionIcon: Sun Icon To Moon in GameMode");
			bIsSunIconShown = false;
			HudWidget->isSunShown(bIsSunIconShown);
		} else
		{
			LogAsWarning("AMain_GameModeBase::CheckTransitionIcon: PlayerController or HUDWidget Not Found in GameMode");
		}
	}
}

/*
    *Converts given time in Hours, Minutes and Suffix to total minutes in int32 format
*/
int32 AMain_GameModeBase::ConvertTimeToInt32(int32 Hours, int32 Minutes, FString Suffix)
{
	if (Suffix == "PM")
	{
		Hours += 12;
	}
	return ((Hours * 60) + Minutes);
}

/*
 *Updates the Time String in the HUD Widget via the PlayerController reference every time the timer ticks
 */
void AMain_GameModeBase::UpdateTimeStringInGameMode(FString const TimeString, int32 Time, int32 OffsetTime)
{
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	HudWidget = PlayerController->HudWidget;
	if (PlayerController && HudWidget)
	{
			HudWidget->UpdateTime(TimeString);
	} else
	{
		LogAsWarning(" AMain_GameModeBase::UpdateTimeStringInGameMode: PlayerController && Hud Widget Not Found in GameMode");
	}
	TurnLightsOn(Time, OffsetTime);
	CheckTransitionIcon(Time, OffsetTime);
}

/*
 *Updates the Time String in the HUD Widget via the PlayerController reference every time the timer ticks
 */
void AMain_GameModeBase::UpdateDayCountInGameMode(int32 const Day)
{
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	HudWidget = PlayerController->HudWidget;
	bIsSunIconShown = true;
	if (PlayerController)
	{
		if (HudWidget)
		{
			HudWidget->UpdateDay(Day);
			HudWidget->isSunShown(bIsSunIconShown);
		} else
		{
			UE_LOG(LogTemp, Error, TEXT(" AMain_GameModeBase::UpdateDayCountInGameMode: HUD Widget Not Found in GameMode"));
		}
	} else
	{
		UE_LOG(LogTemp, Error, TEXT(" AMain_GameModeBase::UpdateDayCountInGameMode: PlayerController Not Found in GameMode"));
	}
	if (TimeActor)
	{
		TimeActor->ResumeTimer();
		TimeActor->ResetTime();
		
	}
}

void AMain_GameModeBase::PauseGame()
{
	if (PlayerController)
	{
		PlayerController->OpenPause(true, bIsSunIconShown);
	}
}

void AMain_GameModeBase::ResumeGame()
{
}
