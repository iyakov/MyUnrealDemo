// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XyzProject/Data/Types/WindGeneratorPropertyVariant.h"
#include "WindGeneratorPropertyDataAsset.generated.h"

enum class EWindGeneratorType;
struct FWindGeneratorPropertyVariant;

/**
 * 
 */
UCLASS()
class XYZPROJECT_API UWindGeneratorPropertyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EWindGeneratorType, FWindGeneratorPropertyVariant> PropertyVariants;
	
};
