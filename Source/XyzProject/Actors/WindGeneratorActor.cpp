// Fill out your copyright notice in the Description page of Project Settings.

#include "WindGeneratorActor.h"


void AWindGeneratorActor::SwitchWindGenerator(bool bIsOn)
{
	bIsGeneratorOn = bIsOn;

	// notify clients
	if (OnWindGeneratorSwitched.IsBound())
	{
		OnWindGeneratorSwitched.Broadcast(bIsGeneratorOn);
	}
}
