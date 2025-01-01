// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindGeneratorActor.generated.h"

UCLASS()
class XYZPROJECT_API AWindGeneratorActor : public AActor
{
	GENERATED_BODY()

public:
	DECLARE_EVENT_OneParam(AWindGeneratorActor, FOnWindGeneratorSwitchedSignature, bool);
	FOnWindGeneratorSwitchedSignature OnWindGeneratorSwitched;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AXYZ")
	bool bIsGeneratorOn = true;

	UFUNCTION(BlueprintCallable)
	void SwitchWindGenerator(bool bIsOn);
};
