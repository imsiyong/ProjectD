// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APDPlayerController();

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<class UPDUWBattleStatus> PDUWBattleStatus;
	
	class UPDUWBattleStatus* BattleStatusWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<class UPDItemInventory> PDItemInventory;

	class UPDItemInventory* ItemInventory;

};
