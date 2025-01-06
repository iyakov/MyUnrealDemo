// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFirstModuleActorChild.h"

// NB! Disables Development and Shipping optimizations for this method (Example)
#pragma optimize("", off)
void AMyFirstModuleActorChild::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Hello from Child"));
}
#pragma optimize("", on)
