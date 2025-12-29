// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Environment/TimeActor.h"

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

	//Days Settings
	UPROPERTY(EditAnywhere, Category="Time Settings")
	int32 TotalDays = 5.0f;
	
	UPROPERTY(VisibleAnywhere, Category="Time Settings")
	int32 DayCount = 1;
	
	UPROPERTY(VisibleAnywhere, Category="Time Settings")
	int32 CurrentTime = 0;

	//Changeable Lights Settings
	UPROPERTY(EditAnywhere, Category="Lights Settings")
	int32 TurnLightsOnHours = 0.0f;
	
	UPROPERTY(EditAnywhere, Category="Lights Settings")
	int32 TurnLightsOnMinutes = 0.0f;
	
	UPROPERTY(EditAnywhere, Category="Lights Settings")
	FString TurnLightsOnSuffix = "PM";
	
	UPROPERTY(EditAnywhere, Category="Lights Settings")
	float StartIntensity = 10.0f;

	UPROPERTY(EditAnywhere, Category="Lights Settings")
	float MaxIntensity = 30.0f;

	UPROPERTY(EditAnywhere, Category="Lights Settings")
	float IntensityStepIncrementValue = 5.0f;

	UPROPERTY(VisibleAnywhere, Category="Lights Settings")
	float CurrentChangeableLightIntensity = 0.0f;

	int32 TimeToTurnOn;
	
	bool bIsEndGameTriggered = false;

	// References
	ABasePlayerController* PlayerController = nullptr;
	ATimeActor* TimeActor = nullptr;
	
	TArray<ALight*> TaggedLights;

public:
	// Variables
	// Functions
	void UpdateTimeStringInGameMode(FString const TimeString, int32 Time, int32 OffsetTime);
	void UpdateDayCountInGameMode(int32 const Day);
	void IncreaseDayCount(ATimeActor *CurrentTimeActor);
	void TurnLightsOn( int32 Time, int32 OffsetTime);
};
