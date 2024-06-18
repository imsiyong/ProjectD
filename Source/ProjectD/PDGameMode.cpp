// Fill out your copyright notice in the Description page of Project Settings.


#include "PDGameMode.h"
#include "PDCharacter1.h"
#include "PDPlayerController.h"
#include "ProjectDCharacter.h"

APDGameMode::APDGameMode()
{
	//DefaultPawnClass = APDCharacter1::StaticClass();
	DefaultPawnClass = AProjectDCharacter::StaticClass();
	PlayerControllerClass = APDPlayerController::StaticClass();
}