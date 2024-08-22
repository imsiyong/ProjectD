// Fill out your copyright notice in the Description page of Project Settings.


#include "PDBattleGameMode.h"
#include "../ProjectDCharacter.h"
#include "../Manager/PDSpawnManager.h"
#include "../Character/PDManCharacter.h"
#include "PDBattlePlayerController.h"

APDBattleGameMode::APDBattleGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APDManCharacter::StaticClass();
	PlayerControllerClass = APDBattlePlayerController::StaticClass();
	APDSpawnManager::Get()->LoadSpawnData();
}

void APDBattleGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	APDSpawnManager::Get()->NormalMonsterSpawn(GetWorld());
}

void APDBattleGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	APDSpawnManager::Delete();
}

void APDBattleGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	APDSpawnManager::Get()->SpawnTick(DeltaSeconds, GetWorld());
}
