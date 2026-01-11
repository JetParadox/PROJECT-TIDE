// Fill out your copyright notice in the Description page of Project Settings.


#include "DaySwitchUI.h"

inline void UDaySwitchUI::UpdateTimerValue(int32 Value)
{
	if (Value > 0)
	{
		TimerValue->SetText(FText::AsNumber(Value));
	} else
	{
		TimerValue->SetText(FText::FromString("GO!"));
	}
}