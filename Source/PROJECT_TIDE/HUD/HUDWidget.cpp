// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"
#include "../Environment/TimeActor.h"

#include "Kismet/GameplayStatics.h"

#define LogAsWarning(x) UE_LOG(LogTemp, Warning, TEXT(x))

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TimeActorRef = Cast<ATimeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeActor::StaticClass()));
	if (TimeActorRef != nullptr) {
		FString TimeStringAtStart = TimeActorRef->FormatTime(0);
		UpdateTime(TimeStringAtStart);
	}
	
	UpdateDay(1);
	
	//Have Sun Icon Shown at Start
	isSunShown(true);
}

void UHUDWidget::isSunShown(bool bShowSun)
{
	UE_LOG(LogTemp, Warning, TEXT(" UHUDWidget::isSunShown: bShowSun Value: %d"), bShowSun);
	if (bShowSun)
	{
		if (SunIcon && MoonIcon)
		{
			SunIcon->SetVisibility(ESlateVisibility::Visible);
			MoonIcon->SetVisibility(ESlateVisibility::Hidden);
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT(" UHUDWidget::isSunShown: SunIcon or MoonIcon Not Found in HUDWidget"));
		}
	} else
	{
		if (SunIcon && MoonIcon)
		{
			SunIcon->SetVisibility(ESlateVisibility::Hidden);
			MoonIcon->SetVisibility(ESlateVisibility::Visible);
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT(" UHUDWidget::isSunShown: SunIcon or MoonIcon Not Found in HUDWidget"));
		}
	}
}

void UHUDWidget::UpdateTime(FString TimeString)
{
	TimeCount->SetText(FText::FromString(TimeString));
}

void UHUDWidget::UpdateDay(int32 Day)
{
	DayCount->SetText(FText::FromString(FString::FromInt(Day)));
}

void UHUDWidget::UpdateResourceCountsInHUD(int32 Fish, int32 Trash, int32 Customer, int32 Currency)
{
	FString FishString = FString::FromInt(Fish);
	FString TrashString = FString::FromInt(Trash);
	FString CustomerString = FString::FromInt(Customer);
	FString CurrencyString = FString::FromInt(Currency);

	//Adding leading zero if less than 10
	Fish <=9 ? FishString = "0" + FishString : FishString;
	Trash <=9 ? TrashString = "0" + TrashString : TrashString;
	Customer <=9 ? CustomerString = "0" + CustomerString : CustomerString;
	Currency <=9 ? CurrencyString = "0" + CurrencyString : CurrencyString;

	//Updating Text Blocks
	FishCount->SetText(FText::FromString(FishString));
	TrashCount->SetText(FText::FromString(TrashString));
	CustomerCount->SetText(FText::FromString(CustomerString));
	CurrencyCount->SetText(FText::FromString(CurrencyString));
}


