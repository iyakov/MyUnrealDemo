// Copyright Epic Games, Inc. All Rights Reserved.

#include "XyzProjectGameMode.h"
#include "XyzProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AXyzProjectGameMode::AXyzProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Core/Characters/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AXyzProjectGameMode: PlayerPawnBPClass.Class was not found!"));
	}
}
