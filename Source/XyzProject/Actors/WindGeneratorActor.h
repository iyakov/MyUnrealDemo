// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZProject/Data/Types/WindGeneratorType.h"
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
	bool bIsWindGeneratorOn = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AXYZ")
	EWindGeneratorType WindGeneratorType = EWindGeneratorType::Advanced; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AXYZ")
	class UWindGeneratorPropertyDataAsset* WindGeneratorPropertySettings;
	
	UFUNCTION(BlueprintCallable)
	void SwitchWindGenerator(bool bIsOn);
};
