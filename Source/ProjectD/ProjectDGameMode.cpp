// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectDGameMode.h"
#include "ProjectDCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectDGameMode::AProjectDGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
