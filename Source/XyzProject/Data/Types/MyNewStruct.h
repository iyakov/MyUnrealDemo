#pragma once

#include "MyNewEnum.h"
#include "MyNewStruct.generated.h"

USTRUCT(BlueprintType)
struct FMyNewStruct
{
	GENERATED_BODY() 

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, UIMin = 1, ClampMax = 10, UIMax = 10))
	int32 SomeIntValue = 5;

	UPROPERTY(EditAnywhere)
	FMyNewEnum SomeEnumValue = FMyNewEnum::Two;

	UPROPERTY(EditAnywhere)
	TArray<float> SomeArray = {1,2,3};

	UPROPERTY(EditAnywhere)
	TSet<int8> SomeSet = {1,2,2,3,3,3};

	UPROPERTY(EditAnywhere)
	TMap<FString, int32> SomeMap = {
		{TEXT("One"), 1},
		{TEXT("two"), 2},
		{TEXT("three"), 3}
	};
};
