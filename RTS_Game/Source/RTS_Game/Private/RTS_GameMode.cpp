// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "RTS_GameMode.h"
#include "UObject/ConstructorHelpers.h"

ARTS_GameMode::ARTS_GameMode()
{
	// use our custom PlayerController class
//	PlayerControllerClass = ARTS_PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/RTS_CharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/RTS_PlayerControllerBP"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}