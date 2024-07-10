// Fill out your copyright notice in the Description page of Project Settings.


#include "PDItemInventory.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"
#include <Kismet/GameplayStatics.h>
#include "PDUISlot.h"
#include "ProjectDCharacter.h"
#include "PDCharacterItemInventory.h"

void UPDItemInventory::Init()
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	UPDUISlot* UISlot;
	for (auto Widget : Widgets)
	{
		UISlot = Cast<UPDUISlot>(Widget);
		if (!UISlot)continue;
		Slots.Emplace(UISlot);
	}
	
}

void UPDItemInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Init();
}

void UPDItemInventory::Refresh()
{
	if (Player == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			Player = Cast<AProjectDCharacter>(PlayerController->GetPawn());
		}
	}
	UPDCharacterItemInventory* ref;
	for (int i = 0; i < Player->Inventory.Num(); i++)
	{
		ref = Player->Inventory[i];
		Slots[ref->Index]->Refresh(i);
	}
}
