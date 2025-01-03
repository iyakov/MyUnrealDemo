#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"
#include "WindGeneratorSettingsRow.generated.h"

USTRUCT(BlueprintType)
struct FWindGeneratorSettingsRow : public FTableRowBase
{
	GENERATED_BODY() 

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	float RotationSpeed = 120.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	float CooldownTime = 5.0f;
};
