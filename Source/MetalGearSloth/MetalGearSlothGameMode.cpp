// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetalGearSlothGameMode.h"
#include "MetalGearSlothCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMetalGearSlothGameMode::AMetalGearSlothGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
