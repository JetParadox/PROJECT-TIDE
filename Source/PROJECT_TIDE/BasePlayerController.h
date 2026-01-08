// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "HUD/HUDWidget.h"
#include "HUD/PauseUserWidget.h"

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

	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UPauseUserWidget> PauseWidgetClass;

public:
	UPROPERTY(VisibleAnywhere, Category="HUD")
	UHUDWidget* HudWidget;

	UPROPERTY(VisibleAnywhere, Category="HUD")
	UPauseUserWidget* PauseHudWidget;
private:

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

public:
	UFUNCTION(BlueprintCallable, Category="Pause")
	void OpenPause(bool bPause, bool bIsSunIconShown);

};
