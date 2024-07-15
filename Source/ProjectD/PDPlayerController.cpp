// Fill out your copyright notice in the Description page of Project Settings.


#include "PDPlayerController.h"
#include "PDUWBattleStatus.h"
#include "PDItemInventory.h"
#include "PDMonsterSample.h"
#include "PDUWBattleEnd.h"
#include "ProjectDCharacter.h"
#include "PDUISlot.h"

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
	InventoryVisible = false;

	ConstructorHelpers::FClassFinder<UPDUWBattleEnd> BE(TEXT("WidgetBlueprint'/Game/UMG/UEndBattle.UEndBattle_C'"));
	if (BE.Succeeded())
	{
		PDUWBattleEnd = BE.Class;
		
	}
	BattleEndVisible = false;

}

void APDPlayerController::BeginPlay()
{
}

void APDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
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
			ItemInventory->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (PDUWBattleEnd != nullptr)
	{
		BattleEnd = CreateWidget<UPDUWBattleEnd>(this, PDUWBattleEnd);
		if (BattleEnd != nullptr)
		{
			BattleEnd->AddToViewport();
			BattleEnd->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	InputComponent->BindAction("BattleEnd", IE_Pressed, this, &APDPlayerController::ToggleBattleEnd);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &APDPlayerController::ToggleInventory);
}

void APDPlayerController::CheckMonsterDeath()
{
	UE_LOG(LogTemp, Log, TEXT("monster Death on start"));
}

void APDPlayerController::ToggleBattleEnd()
{
	if (BattleEnd)
	{
		BattleEndVisible = !BattleEndVisible;
		if (BattleEndVisible)
		{
			bShowMouseCursor = true;
			BattleEnd->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			bShowMouseCursor = false;
			BattleEnd->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	ItemInventory->Refresh();
}

void APDPlayerController::ToggleInventory()
{
	if (ItemInventory)
	{
		AProjectDCharacter* PDC = Cast<AProjectDCharacter>(GetPawn());
		InventoryVisible = !InventoryVisible;
		if (InventoryVisible)
		{
			bShowMouseCursor = true;
			PDC->MouseInputValid = false;
			ItemInventory->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			bShowMouseCursor = false;
			PDC->MouseInputValid = true;
			ItemInventory->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
