// Copyright Epic Games, Inc. All Rights Reserved.


#include "UESandboxGameModeBase.h"
#include "SandboxPawn.h"

AUESandboxGameModeBase::AUESandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
}
