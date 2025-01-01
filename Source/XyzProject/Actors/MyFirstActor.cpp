// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFirstActor.h"

// Sets default values
AMyFirstActor::AMyFirstActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();

	SetRandomRotationRate();
	
	FString message = FString::Printf(TEXT("Initial rotation rate is %f"), CurrentRotationRate);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, TextColor, message);
}

// Called every frame
void AMyFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = GetActorRotation();
	rotation.Yaw += CurrentRotationRate * DeltaTime;
	SetActorRotation(rotation);
}

void AMyFirstActor::SetRandomRotationRate()
{
	CurrentRotationRate = FMath::RandRange(MinimumRotationRate, MaximumRotationRate);
}
