// Fill out your copyright notice in the Description page of Project Settings.


#include "PDRestGameMode.h"
#include "../Character/PDManCharacter.h"
#include "PDRestPlayerController.h"

APDRestGameMode::APDRestGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APDManCharacter::StaticClass();
	PlayerControllerClass = APDRestPlayerController::StaticClass();
}

void APDRestGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void APDRestGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APDRestGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
