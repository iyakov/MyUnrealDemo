#pragma once

#include "CoreMinimal.h"
#include "FWindGeneratorType.generated.h"

// NB! Do not add/change meta formatting. It is used in DataTable import.

UENUM(BlueprintType)
enum class FWindGeneratorType : uint8
{
	Basic UMETA(DisplayName = "Basic"),
	Advanced UMETA(DisplayName = "Advanced"),
	Ultra UMETA(DisplayName = "Ultra")
};
