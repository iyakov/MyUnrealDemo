// Fill out your copyright notice in the Description page of Project Settings.

#include "WindGeneratorActor.h"

void AWindGeneratorActor::SwitchWindGenerator(bool bIsOn)
{
	bIsWindGeneratorOn = bIsOn;

	// notify clients
	if (OnWindGeneratorSwitched.IsBound())
	{
		OnWindGeneratorSwitched.Broadcast(bIsWindGeneratorOn);
	}
}

float AWindGeneratorActor::GetCooldownTimeFromRotationSpeed(float inRotationSpeed) const
{
	float result = 0;

	if (IsValid(CooldownTimeCurve))
	{
		result = CooldownTimeCurve->GetFloatValue(inRotationSpeed);

		FString message = FString::Printf(TEXT("Wind Generator: %f cooldown for %f speed"), result, inRotationSpeed);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, message);
	}

	return result;
}
