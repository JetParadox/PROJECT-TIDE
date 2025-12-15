// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"
#include "../Environment/TimeActor.h"

#include "Kismet/GameplayStatics.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TimeActorRef = Cast<ATimeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeActor::StaticClass()));
	if (TimeActorRef != nullptr) {
		FString TimeStringAtStart = TimeActorRef->FormatTime(0);
		UpdateTime(TimeStringAtStart);
	} else {
		UE_LOG(LogTemp, Error, TEXT("TimeActorRef Not Found in HUDWidget"));
	}
	
	UpdateDay(1);
}

void UHUDWidget::UpdateTime(FString TimeString)
{
	TimeCount->SetText(FText::FromString(TimeString));
}

void UHUDWidget::UpdateDay(int32 Day)
{
	DayCount->SetText(FText::FromString(FString::FromInt(Day)));
}


