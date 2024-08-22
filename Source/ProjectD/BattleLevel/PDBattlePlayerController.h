// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PDBattlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDBattlePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APDBattlePlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<class UPDUWBattleStatus> PDUWBattleStatus;
	class UPDUWBattleStatus* BattleStatusWidget;
};
