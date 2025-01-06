// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "XyzProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class XYZPROJECT_API UXyzProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	const FColor& GetPlayerColor();
	
private:
	FColor PlayerColor = FColor::Black;
};
