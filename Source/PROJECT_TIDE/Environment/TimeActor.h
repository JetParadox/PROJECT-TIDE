// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DirectionalLight.h"

#include "TimeActor.generated.h"

class AMain_GameModeBase;

UCLASS()
class PROJECT_TIDE_API ATimeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variables
private:
	UPROPERTY(VisibleAnywhere, Category="Directional Light")
	ADirectionalLight* DirectionalLight;
	
	UPROPERTY(EditAnywhere, Category="Directional Light")
	FRotator StartDirectionalLightRotation = FRotator(-1.0f,180.0f,0.0f);
	
	UPROPERTY(EditAnywhere, Category="Directional Light")
	FRotator EndDirectionalLightRotation = FRotator(-179.0f,180.0f,0.0f);
	
	UPROPERTY(EditAnywhere, Category="Directional Light")
	FLinearColor  StartDirectionalLightColor = FLinearColor(0.939236f,0.761649f,0.504718f,1.000000f);
	
	UPROPERTY(EditAnywhere, Category="Directional Light")
	FLinearColor  EndDirectionalLightColor = FLinearColor(0.131778f,0.200854f,0.352430f,1.000000f);

	UPROPERTY(VisibleAnywhere, Category="Time")
	float Time;

	UPROPERTY(EditAnywhere, Category="Time")
	float PrepTime = 60.0f;

	UPROPERTY(EditAnywhere, Category="Time")
	float GameTime = 180.0f;

	UPROPERTY(EditAnywhere, Category="Time")
	float GameToRealTimeMultiplier = 2.0f;
public:
	UPROPERTY(EditAnywhere, Category="Time")
	int32 StartOffsetHours = 6;

	UPROPERTY(EditAnywhere, Category="Time")
	int32 StartOffsetMinutes = 0;
private:
	UPROPERTY(VisibleAnywhere, Category="GameMode")
	AMain_GameModeBase* GameMode = nullptr;

	int32 TotalInGameTime;
	int32 InGameTime;
	int32 TimeInMinutes;
	int32 TimeInHours;
	int32 NextSuffixSwapTime;
	int32 OffsetTime;
	FString TimeSuffix;
	
	float ElapsedTime = 0.0f;
	float ElapsedColorTime = 0.0f;

	bool bIsLerping = false;
	bool bIsColorChanging = false;
	bool bIsTimeSuffixSwapped = false;

	FString TimeInString;

	FQuat StartQuaternion;
	FQuat EndQuaternion;

	FTimerHandle MainTimerHandle;
	
	//Inline Functions
	
	//Functions
private:
	void UpdateTime();

	

	void RotateDirectionalLight(float DeltaTime);
	void ChangeColorDirectionalLight(float DeltaTime);

	
	void SwapTimeSuffix();

public:
	FString FormatTime(int32 TimeCount);

	void ResetTime();

	void PauseTimer();
	void ResumeTimer();
	
	
	//Getters and Setters
	float GetTime() const { return Time; }
	FString GetTimeString() const { return TimeInString; }
	

};
