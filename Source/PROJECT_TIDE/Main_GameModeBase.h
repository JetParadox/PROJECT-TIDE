// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Environment/TimeActor.h"
#include "HUD/HUDWidget.h"
#include "HUD/PauseUserWidget.h"

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

	UPROPERTY(EditAnywhere, Category="Lights Settings")
	int32 IconTransitionHours = 0.0f;
	
	UPROPERTY(EditAnywhere, Category="Lights Settings")
	int32 IconTransitionMinutes = 0.0f;
	
	UPROPERTY(EditAnywhere, Category="Lights Settings")
	FString IconTransitionOnSuffix = "PM";


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

	//Time Transition Variables
	int32 TimeToTurnOn;
	int32 TimeToTransitionIcon;

	//Resource variables
	int32 FishCount = 0;
	int32 TrashCount = 0;
	int32 CustomerCount = 0;
	int32 CurrencyCount = 0;
	
	bool bIsEndGameTriggered = false;
	bool bIsSunIconShown = true;

	// References
	ABasePlayerController* PlayerController = nullptr;
	ATimeActor* TimeActor = nullptr;
	UHUDWidget* HudWidget = nullptr;
	UPauseUserWidget* PauseWidget = nullptr;
	
	TArray<ALight*> TaggedLights;

public:
	// Variables
	// Functions
	void UpdateTimeStringInGameMode(FString const TimeString, int32 Time, int32 OffsetTime);
	void UpdateDayCountInGameMode(int32 const Day);
	void IncreaseDayCount(ATimeActor *CurrentTimeActor);
	void TurnLightsOn( int32 Time, int32 OffsetTime);
	void CheckTransitionIcon( int32 Time, int32 OffsetTime);

	//Resource Setter Functions
	UFUNCTION(BlueprintCallable)
	void SetFishCount(int32 const Fish);
	UFUNCTION(BlueprintCallable)
	void SetTrashCount(int32 const Trash);
	UFUNCTION(BlueprintCallable)
	void SetCustomerCount(int32 const Customer);
	UFUNCTION(BlueprintCallable)
	void SetCurrencyCount(int32 const Currency);
	
	void UpdateResourceCountsInGameMode(int32 Fish, int32 Trash, int32 Customer, int32 Currency);

	//Trash Clearing Function
	void ResetTrash();

	//Pause Function
	void PauseGame();

	//Inline Functions
	bool IsSunIconShown() { return bIsSunIconShown;};

private:
	int32 ConvertTimeToInt32(int32 Hours, int32 Minutes, FString Suffix);
};
