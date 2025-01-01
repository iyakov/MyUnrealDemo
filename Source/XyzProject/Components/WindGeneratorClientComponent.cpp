// Fill out your copyright notice in the Description page of Project Settings.

#include "XyzProject/Actors/WindGeneratorActor.h"
#include "WindGeneratorClientComponent.h"

// Called when the game starts
void UWindGeneratorClientComponent::BeginPlay()
{
	Super::BeginPlay();

	// subscribe for incoming events
	if (IsValid(WindGenerator))
	{
		WindGenerator->OnWindGeneratorSwitched.AddUObject(
			this, &UWindGeneratorClientComponent::OnWindGeneratorSwitchedHandler);		
	}
}

void UWindGeneratorClientComponent::OnWindGeneratorSwitchedHandler(bool bIsOn) const
{
	FString value = bIsOn ? TEXT("On") : TEXT("Off");
	FString name = GetOwner()->GetName();
	FString message = FString::Printf(TEXT("OnWindGeneratorSwitched for %s wind generator is %s"), *name, *value);
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, message);

	// forward to blueprint (NB! It's SLOW) 
	if (OnWindGeneratorClientSwitched.IsBound())
	{
		OnWindGeneratorClientSwitched.Broadcast(bIsOn);
	}
}
