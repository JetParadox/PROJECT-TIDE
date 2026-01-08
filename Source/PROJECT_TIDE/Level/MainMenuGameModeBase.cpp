// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#define LogAsWarning(x) UE_LOG(LogTemp, Warning, TEXT(x))
#define LogAsError(x) UE_LOG(LogTemp, Error, TEXT(x))

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this,0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		MainMenuHudWidget = CreateWidget<UMainMenuUserWidget>(PlayerController, MainMenuHudWidgetClass);
		if (MainMenuHudWidget)
		{
			MainMenuHudWidget->AddToViewport(1);
			PlayerController->SetInputMode(FInputModeUIOnly());
			LogAsWarning("AMainMenuGameModeBase::BeginPlay Added Widget to Viewport.")
		}
		LogAsWarning("AMainMenuGameModeBase::BeginPlay Created Widget")
	}
}
