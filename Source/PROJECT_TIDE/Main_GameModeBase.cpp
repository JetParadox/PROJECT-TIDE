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
	CurrentChangeableLightIntensity = StartIntensity;

	if (TurnLightsOnSuffix == "PM")
	{
		TurnLightsOnHours += 12;
	}
	TimeToTurnOn = ((TurnLightsOnHours * 60) + TurnLightsOnMinutes);
	UE_LOG (LogTemp, Warning, TEXT("Lights Will Turn On at Time in Minutes: %d"), TimeToTurnOn);
	
	//Gets all the lights with a specific tag in the level and stores them in an array for future use
	TArray<AActor*> FoundLights;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("TimeChangeableLights"), FoundLights);
	UE_LOG(LogTemp, Warning, TEXT("Found Lights Found in GameMode: %d"), FoundLights.Num());

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
	UE_LOG(LogTemp, Warning, TEXT("Changeable Lights Found in GameMode: %d"), TaggedLights.Num());
}

void AMain_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DayCount > TotalDays && !bIsEndGameTriggered)
	{
		//TODO: Trigger End Game Sequence
		LogAsWarning("End Game Triggered");
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

//
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
 *Updates the Time String in the HUD Widget via the PlayerController reference every time the timer ticks
 */
void AMain_GameModeBase::UpdateTimeStringInGameMode(FString const TimeString, int32 Time, int32 OffsetTime)
{
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		if (UHUDWidget* HudWidget = PlayerController->HudWidget)
		{
			HudWidget->UpdateTime(TimeString);
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("HUD Widget Not Found in GameMode"));
		}
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Not Found in GameMode"));
	}
	TurnLightsOn(Time, OffsetTime);
}

/*
 *Updates the Time String in the HUD Widget via the PlayerController reference every time the timer ticks
 */
void AMain_GameModeBase::UpdateDayCountInGameMode(int32 const Day)
{
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		UHUDWidget* HudWidget = PlayerController->HudWidget;
		if (HudWidget)
		{
			HudWidget->UpdateDay(Day);
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("HUD Widget Not Found in GameMode"));
		}
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Not Found in GameMode"));
	}
	if (TimeActor)
	{
		TimeActor->ResumeTimer();
		TimeActor->ResetTime();
		
	}
}
