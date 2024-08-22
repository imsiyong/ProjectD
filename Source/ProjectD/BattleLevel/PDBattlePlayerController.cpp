// Fill out your copyright notice in the Description page of Project Settings.


#include "PDBattlePlayerController.h"
#include "../UserWidget/PDUWBattleStatus.h"

APDBattlePlayerController::APDBattlePlayerController()
{
	ConstructorHelpers::FClassFinder<UPDUWBattleStatus> BS(TEXT("WidgetBlueprint'/Game/UMG/BattleStatus.BattleStatus_C'"));
	if (BS.Succeeded())
	{
		PDUWBattleStatus = BS.Class;
	}
}

void APDBattlePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APDBattlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (PDUWBattleStatus)
	{
		BattleStatusWidget = CreateWidget<UPDUWBattleStatus>(this, PDUWBattleStatus);
		if (BattleStatusWidget)
		{
			BattleStatusWidget->AddToViewport();
		}
	}
}
