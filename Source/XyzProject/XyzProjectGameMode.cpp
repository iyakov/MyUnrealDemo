// Copyright Epic Games, Inc. All Rights Reserved.

#include "XyzProjectGameMode.h"
#include "XyzProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AXyzProjectGameMode::AXyzProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
