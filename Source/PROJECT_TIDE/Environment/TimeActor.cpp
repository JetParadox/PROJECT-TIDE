// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActor.h"

#include "Math/UnrealMathUtility.h"
#include "../Main_GameModeBase.h"


#define LogAsError(x) UE_LOG(LogTemp, Error, TEXT(x))

// Sets default values
ATimeActor::ATimeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Get A Reference to Directional Light
	DirectionalLight = Cast<ADirectionalLight>(	UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));

	
	

}

// Called when the game starts or when spawned
void ATimeActor::BeginPlay()
{
	Super::BeginPlay();

	//Get A Reference to Current GameMode
	GameMode = Cast<AMain_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	//NULL CHECKS
	if (!DirectionalLight) { LogAsError("Directional Light Not Found in TimeActor"); }
	if (!GameMode) { LogAsError("GameMode Not Found in TimeActor"); }
	
	ResetTime();
	FormatTime(InGameTime);
	if (GameMode)
	{
		GameMode->UpdateTimeStringInGameMode(TimeInString);
	}else
	{
		LogAsError("GameMode Not Found in TimeActor At BeginPlay");
	}
	TotalInGameTime = PrepTime + GameTime;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimeActor::UpdateTime, 1.0f,true);	
	
	if (DirectionalLight)
	{
		
		//Speed To Interpolate
		StartQuaternion = StartDirectionalLightRotation.Quaternion();
		EndQuaternion = EndDirectionalLightRotation.Quaternion();
		
		DirectionalLight->SetActorRotation(StartQuaternion);
		DirectionalLight->SetLightColor(StartDirectionalLightColor);
		
	}
}

// Called every frame
void ATimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateDirectionalLight(DeltaTime);
	ChangeColorDirectionalLight(DeltaTime);
}

/*
 *Timer Handle calls this function every second to update the time variables and string
 */
void ATimeActor::UpdateTime()
{
	Time++;
	InGameTime = (Time * GameToRealTimeMultiplier);
	FormatTime(InGameTime);
	if (GameMode)
	{
		GameMode->UpdateTimeStringInGameMode(TimeInString);
	}
}

/*
 *Resets Time Variables to Start Values
 */
void ATimeActor::ResetTime()
{
	Time = 0;
	InGameTime = (Time * GameToRealTimeMultiplier);
	NextSuffixSwapTime = 12;
	TimeInMinutes = StartOffsetMinutes;
	TimeInHours = StartOffsetHours;
	TimeSuffix = "AM";
	ElapsedTime = 0;
	ElapsedColorTime = 0;
	bIsLerping = true;
	bIsColorChanging = true;
	bIsTimeSuffixSwapped = false;
}

/*
 *Changes The Rotation of the Directional Light over Time until Alpha >= 1
 */
void ATimeActor::RotateDirectionalLight(float DeltaTime)
{
	if (!DirectionalLight || !bIsLerping) return;

	ElapsedTime += DeltaTime;
	float Alpha = FMath::Clamp(ElapsedTime / TotalInGameTime, 0.0f, 1.0f);

	// Use shortest path slerp
	FQuat CurrentQuat = FQuat::Slerp(StartQuaternion, EndQuaternion, Alpha);

	DirectionalLight->SetActorRotation(CurrentQuat); 

	if (Alpha >= 1.0f)
	{
		bIsLerping = false;
		DirectionalLight->SetActorRotation(EndQuaternion);
	}
}

/*
 *Changes The Color of the Directional Light over Time until Alpha >= 1
 */
void ATimeActor::ChangeColorDirectionalLight(float DeltaTime)
{
	if (DirectionalLight && bIsColorChanging)
	{
		ElapsedColorTime += DeltaTime;
		float Alpha = FMath::Clamp(ElapsedColorTime / TotalInGameTime, 0.f, 1.f);

		FLinearColor NewColor = FLinearColor::LerpUsingHSV(StartDirectionalLightColor, EndDirectionalLightColor, Alpha);
		DirectionalLight->SetLightColor(NewColor);

		if (Alpha >= 1.f)
		{
			bIsColorChanging = false;
		}
	}
}

/*
 *Converts the passed time into a string format HH:MM AM/PM
 *Returns the string if you want to use it elsewhere
 *Condition for NextSuffixSwapTime is made so that it only swaps once every 12 hours
 *Condition for TimeInHours to reset to 1 after 12 hours because we want to have 12:00 PM instead of 0:00 PM
 */
FString ATimeActor::FormatTime(int32 TimeCount)
{
	TimeInMinutes = StartOffsetMinutes +( FMath::Fmod(TimeCount, 60.0f));
	TimeInHours = StartOffsetHours + ( (TimeCount) / 60);
	
	if (TimeInHours >= NextSuffixSwapTime)
	{
		NextSuffixSwapTime += 12;
		SwapTimeSuffix();
	}
	if (TimeInHours >= 13)
	{
		TimeInHours -= NextSuffixSwapTime-12;
	}
	if (TimeInHours <= 9)
	{
		if (TimeInMinutes <= 9)
		{
			TimeInString = FString::Printf(TEXT("0%d:0%d %s"), TimeInHours, TimeInMinutes, *TimeSuffix);
		} else
		{
			TimeInString = FString::Printf(TEXT("0%d:%d %s"), TimeInHours, TimeInMinutes, *TimeSuffix);
		}
	} else
	{
		if (TimeInMinutes <= 9)
		{
			TimeInString = FString::Printf(TEXT("%d:0%d %s"), TimeInHours, TimeInMinutes, *TimeSuffix);
		} else
		{
			TimeInString = FString::Printf(TEXT("%d:%d %s"), TimeInHours, TimeInMinutes, *TimeSuffix);
		}
	}
	return TimeInString;
	
}

/*
 *Swaps the time suffix between AM and PM
 */
void ATimeActor::SwapTimeSuffix()
{
	if (TimeSuffix == "AM"){
		TimeSuffix = "PM";
	} else if (TimeSuffix == "PM"){
		TimeSuffix = "AM";
	}
	
}

