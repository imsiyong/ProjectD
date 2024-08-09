// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PDBattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDBattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	APDBattleGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
