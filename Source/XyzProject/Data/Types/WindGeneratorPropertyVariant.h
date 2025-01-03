#pragma once

#include "WindGeneratorPropertyVariant.generated.h"

USTRUCT(BlueprintType)
struct FWindGeneratorPropertyVariant
{
	GENERATED_BODY() 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Transform;
};
