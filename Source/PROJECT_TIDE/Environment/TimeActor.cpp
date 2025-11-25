// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActor.h"

#include "Math/UnrealMathUtility.h"

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
	
	//NULL CHECKS
	if (!DirectionalLight) { LogAsError("Directional Light Not Found"); }
	
	ResetTime();
	TotalInGameTime = PrepTime + GameTime;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimeActor::UpdateTime, 1.0f,true);	
	
	if (DirectionalLight)
	{
		
		//Speed To Interpolate
		StartQuaternion = StartDirectionalLightRotation.Quaternion();
		EndQuaternion = EndDirectionalLightRotation.Quaternion();
		
		DirectionalLight->SetActorRotation(StartQuaternion);
		UE_LOG(LogTemp, Warning, TEXT("Start Directional Light Set to: %s"), *DirectionalLight->GetActorRotation().Euler().ToString());
		
	}
}

// Called every frame
void ATimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateDirectionalLight(DeltaTime);
}

void ATimeActor::UpdateTime()
{
	Time++;
	TimeInSeconds = FMath::Fmod(Time, 60.0f);
	TimeInMinutes = Time / 60;
	FString TimeInString;
	if (TimeInSeconds <= 9)
	{
		TimeInString = FString::Printf(TEXT("%d:0%d"), TimeInMinutes, TimeInSeconds);
	} else
	{
		TimeInString = FString::Printf(TEXT("%d:%d"), TimeInMinutes, TimeInSeconds);
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Time : %s"), *TimeInString));
	
}

void ATimeActor::ResetTime()
{
	Time = 0.0f;
	TimeInSeconds = 0;
	TimeInMinutes = 0;
	ElapsedTime = 0;
	bIsLerping = true;
}

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
		UE_LOG(LogTemp, Warning, TEXT("Rotation finished: %s"), *DirectionalLight->GetActorRotation().ToCompactString());
	}
}

