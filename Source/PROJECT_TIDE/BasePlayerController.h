// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HUD/HUDWidget.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PROJECT_TIDE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TArray<UInputMappingContext*> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UHUDWidget> HudWidgetClass;

public:
	UPROPERTY(VisibleAnywhere, Category="HUD")
	UHUDWidget* HudWidget;

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

public:

	
};
