#pragma once

#include "CoreMinimal.h"
#include "WindGeneratorType.generated.h"

// NB! Do not add/change meta formatting. It is used in DataTable import.

UENUM(BlueprintType)
enum class EWindGeneratorType : uint8
{
	Invalid = 0,
	Basic UMETA(DisplayName = "Basic"),
	Advanced UMETA(DisplayName = "Advanced"),
	Ultra UMETA(DisplayName = "Ultra")
};
