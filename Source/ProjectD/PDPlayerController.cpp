// Fill out your copyright notice in the Description page of Project Settings.


#include "PDPlayerController.h"
#include "PDUWBattleStatus.h"
#include "PDItemInventory.h"
#include "PDMonsterSample.h"
#include "PDUWBattleEnd.h"
#include "ProjectDCharacter.h"
#include "PDUISlot.h"
#include "PDUWEquip.h"

APDPlayerController::APDPlayerController()
{
	bShowMouseCursor = true;
	ToggleCount = 0;
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
	ConstructorHelpers::FClassFinder<UPDUWEquip> EQ(TEXT("WidgetBlueprint'/Game/UMG/UEquip.UEquip_C'"));
	if (EQ.Succeeded())
	{
		PDUWEquip = EQ.Class;
	}
	EquipVisible = false;
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
	}
	if (PDUWBattleEnd != nullptr)
	{
		BattleEnd = CreateWidget<UPDUWBattleEnd>(this, PDUWBattleEnd);
	}
	if (PDUWEquip != nullptr)
	{
		Equip = CreateWidget<UPDUWEquip>(this, PDUWEquip);
	}
	InputComponent->BindAction("BattleEnd", IE_Pressed, this, &APDPlayerController::ToggleBattleEnd);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &APDPlayerController::ToggleInventory);
	InputComponent->BindAction("Equip", IE_Pressed, this, &APDPlayerController::ToggleEquip);
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
			ToggleMousePointer(true);
			BattleEnd->AddToViewport();
		}
		else
		{
			ToggleMousePointer(false);
			BattleEnd->RemoveFromViewport();
		}
	}
}

void APDPlayerController::ToggleInventory()
{
	if (ItemInventory)
	{
		ItemInventory->Refresh();
		AProjectDCharacter* PDC = Cast<AProjectDCharacter>(GetPawn());
		InventoryVisible = !InventoryVisible;
		if (InventoryVisible)
		{
			ToggleMousePointer(true);
			PDC->MouseInputValid = false;
			ItemInventory->AddToViewport();
		}
		else
		{
			ToggleMousePointer(false);
			PDC->MouseInputValid = true;
			ItemInventory->RemoveFromViewport();
		}
	}
}

void APDPlayerController::ToggleEquip()
{
	if (Equip)
	{
		Equip->Refresh();
		AProjectDCharacter* PDC = Cast<AProjectDCharacter>(GetPawn());
		EquipVisible = !EquipVisible;
		if (EquipVisible)
		{
			ToggleMousePointer(true);
			PDC->MouseInputValid = false;
			Equip->AddToViewport();
		}
		else
		{
			ToggleMousePointer(false);
			PDC->MouseInputValid = true;
			Equip->RemoveFromViewport();
		}
	}
}

void APDPlayerController::ToggleMousePointer(bool isEnable)
{
	if (isEnable)
	{
		ToggleCount++;
	}
	else
	{
		ToggleCount--;
	}
	if (ToggleCount <= 0)
	{
		if(bShowMouseCursor)
			bShowMouseCursor = false;
	}
	else
	{
		if(!bShowMouseCursor)
			bShowMouseCursor = true;
	}
	if (ToggleCount < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Toggle Count error : minus"));
	}
}
