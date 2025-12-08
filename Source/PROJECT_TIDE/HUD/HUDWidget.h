// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;
class ATimeActor;

/**
 * 
 */
UCLASS()
class PROJECT_TIDE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HUD", meta = (BindWidget))
	UTextBlock* DayCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HUD", meta = (BindWidget))
	UTextBlock* TimeCount;

	UPROPERTY(VisibleAnywhere, Category="Time")
	ATimeActor* TimeActorRef;

	void UpdateTime(FString TimeString);
	void UpdateDay(int32 Day);
};
