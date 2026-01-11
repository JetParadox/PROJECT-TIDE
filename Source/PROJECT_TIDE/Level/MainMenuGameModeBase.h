// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MainMenuUserWidget.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_TIDE_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UMainMenuUserWidget> MainMenuHudWidgetClass;
	
	UPROPERTY(VisibleAnywhere, Category="HUD")
	UMainMenuUserWidget* MainMenuHudWidget;
private:
	APlayerController* PlayerController;
};
