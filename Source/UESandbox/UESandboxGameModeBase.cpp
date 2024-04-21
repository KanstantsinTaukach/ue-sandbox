// Copyright Epic Games, Inc. All Rights Reserved.


#include "UESandboxGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

AUESandboxGameModeBase::AUESandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}
