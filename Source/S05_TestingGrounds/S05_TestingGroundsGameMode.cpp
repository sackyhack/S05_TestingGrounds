// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "S05_TestingGroundsGameMode.h"
#include "S05_TestingGroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AS05_TestingGroundsGameMode::AS05_TestingGroundsGameMode()
{
	// Set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behavior/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Use our custom HUD class
	HUDClass = AS05_TestingGroundsHUD::StaticClass();
}