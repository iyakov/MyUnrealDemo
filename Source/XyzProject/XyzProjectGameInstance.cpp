// Fill out your copyright notice in the Description page of Project Settings.


#include "XyzProjectGameInstance.h"

const FColor& UXyzProjectGameInstance::GetPlayerColor()
{
	// Try to generate a ramdom color non-blocking way
	for (int i = 0; i < 100 && PlayerColor == FColor::Black; ++i)
	{
		PlayerColor = FColor::MakeRandomColor();
	}

	return PlayerColor;
}
