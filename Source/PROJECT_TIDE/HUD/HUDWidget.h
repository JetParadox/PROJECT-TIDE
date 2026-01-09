// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
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
	//Icon
	UPROPERTY(VisibleAnywhere, Category="Icons", meta = (BindWidget))
	UImage* SunIcon;
	
	UPROPERTY(VisibleAnywhere, Category="Icons", meta = (BindWidget))
	UImage* MoonIcon;
	
	//Time Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HUD", meta = (BindWidget))
	UTextBlock* DayCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HUD", meta = (BindWidget))
	UTextBlock* TimeCount;

	//Resource Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Resource", meta = (BindWidget))
	UTextBlock* FishCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Resource", meta = (BindWidget))
	UTextBlock* TrashCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Resource", meta = (BindWidget))
	UTextBlock* CustomerCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Resource", meta = (BindWidget))
	UTextBlock* CurrencyCount;

	UPROPERTY(VisibleAnywhere, Category="Time")
	ATimeActor* TimeActorRef;

	void isSunShown(bool bShowSun);

	void UpdateTime(FString TimeString);
	void UpdateDay(int32 Day);

	void UpdateResourceCountsInHUD(int32 Fish, int32 Trash, int32 Customer, int32 Currency);
};
