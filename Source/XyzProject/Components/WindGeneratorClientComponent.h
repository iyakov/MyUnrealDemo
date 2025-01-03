// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindGeneratorClientComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWindGeneratorClientSwitchedSignature, bool, bIsOn);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class XYZPROJECT_API UWindGeneratorClientComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditInstanceOnly, Category="AXYZ")
	class AWindGeneratorActor* WindGenerator;

	UPROPERTY(BlueprintAssignable, Category="AXYZ")
	FWindGeneratorClientSwitchedSignature OnWindGeneratorClientSwitched;
	
	UFUNCTION()
	void OnWindGeneratorSwitchedHandler(bool bIsOn) const;
};
