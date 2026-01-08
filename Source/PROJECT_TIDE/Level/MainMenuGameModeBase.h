// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	TSubclassOf<UUserWidget> MainMenuHudWidgetClass;
	
	UPROPERTY(VisibleAnywhere, Category="HUD")
	UUserWidget* MainMenuHudWidget;
private:
	APlayerController* PlayerController;
};
