#pragma once

#include "MyNewEnum.generated.h"

UENUM(BlueprintType)
enum class FMyNewEnum : uint8
{
	One UMETA(DisplayName = "Value 1"),
	Two UMETA(DisplayName = "Value 2"),
	Three UMETA(DisplayName = "Value 3")
};
