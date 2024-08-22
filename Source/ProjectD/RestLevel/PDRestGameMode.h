// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PDRestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDRestGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	APDRestGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;
};
