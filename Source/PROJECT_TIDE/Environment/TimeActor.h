// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"

#include "TimeActor.generated.h"

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

	UPROPERTY(VisibleAnywhere, Category="Time")
	float Time;

	UPROPERTY(EditAnywhere, Category="Time")
	float PrepTime = 10.0f;

	UPROPERTY(EditAnywhere, Category="Time")
	float GameTime = 10.0f;

	UPROPERTY(EditAnywhere, Category="Time")
	float GameToRealTimeMultiplier = 1.0f;

	int32 TotalInGameTime;
	int32 TimeInSeconds;
	int32 TimeInMinutes;
	
	float ElapsedTime = 0.0f;

	bool bIsLerping = false;

	FQuat StartQuaternion;
	FQuat EndQuaternion;
	
	//Inline Functions
	
	//Functions
private:
	void UpdateTime();

	void ResetTime();

	void RotateDirectionalLight(float DeltaTime);

};
