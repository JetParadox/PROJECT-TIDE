// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_GameModeBase.h"

#include "BasePlayerController.h"
#include "Environment/TimeActor.h"


AMain_GameModeBase::AMain_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMain_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// FString TimeStringAtBeginPlay = CurrentTimeActor->GetTimeString();
	// UpdateTimeStringInGameMode(TimeStringAtBeginPlay);
	
}

void AMain_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMain_GameModeBase::UpdateTimeStringInGameMode(FString const TimeString)
{
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		UHUDWidget* HudWidget = PlayerController->HudWidget;
		if (HudWidget)
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
}
