// Fill out your copyright notice in the Description page of Project Settings.


#include "PDPlayerController.h"
#include "PDUWBattleStatus.h"
#include "PDItemInventory.h"

APDPlayerController::APDPlayerController()
{
	ConstructorHelpers::FClassFinder<UPDUWBattleStatus> BS(TEXT("WidgetBlueprint'/Game/UMG/BattleStatus.BattleStatus_C'"));
	if (BS.Succeeded())
	{
		PDUWBattleStatus = BS.Class;
	}

	ConstructorHelpers::FClassFinder<UPDItemInventory> II(TEXT("WidgetBlueprint'/Game/UMG/Inventory.Inventory_C'"));
	if (II.Succeeded())
	{
		PDItemInventory = II.Class;
	}
}

void APDPlayerController::SetupInputComponent()
{
	if (PDUWBattleStatus != nullptr)
	{
		BattleStatusWidget = CreateWidget<UPDUWBattleStatus>(this, PDUWBattleStatus);
		if (BattleStatusWidget != nullptr)
		{
			BattleStatusWidget->AddToViewport();
		}
	}
	if (PDItemInventory != nullptr)
	{
		ItemInventory = CreateWidget<UPDItemInventory>(this, PDItemInventory);
		if (ItemInventory != nullptr)
		{
			ItemInventory->AddToViewport();
		}
	}
}
