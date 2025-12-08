// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Kismet/GameplayStatics.h"

#include "Main_GameModeBase.generated.h"

class ATimeActor;
class ABasePlayerController;
/**
 * 
 */
UCLASS()
class PROJECT_TIDE_API AMain_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMain_GameModeBase();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	int32 DayCount;

	ABasePlayerController* PlayerController;

public:
	// Variables
	// Functions
	void UpdateTimeStringInGameMode(FString const TimeString);
};
