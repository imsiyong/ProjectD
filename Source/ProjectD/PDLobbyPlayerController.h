// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PDLobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDLobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APDLobbyPlayerController();

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<class UPDLobbyWidgetStat> PDLobbyWidgetStat;
	class UPDLobbyWidgetStat* LobbyWidgetStat;
};
