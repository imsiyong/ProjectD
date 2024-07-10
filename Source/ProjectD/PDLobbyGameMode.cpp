// Fill out your copyright notice in the Description page of Project Settings.


#include "PDLobbyGameMode.h"
#include "PDLobbyPlayerController.h"
#include "PDLobbyCharacter.h"

APDLobbyGameMode::APDLobbyGameMode()
{
	DefaultPawnClass = APDLobbyCharacter::StaticClass();
	PlayerControllerClass = APDLobbyPlayerController::StaticClass();
}