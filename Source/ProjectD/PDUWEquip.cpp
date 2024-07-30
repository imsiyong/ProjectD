// Fill out your copyright notice in the Description page of Project Settings.


#include "PDUWEquip.h"
#include "Components/Image.h"
#include "PDUISlot.h"
#include "ProjectDCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/WidgetTree.h"

void UPDUWEquip::Init()
{
	Slots.Empty();
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);
	UPDUISlot* UISlot;
	for (auto Widget : Widgets)
	{
		UISlot = Cast<UPDUISlot>(Widget);
		if (!UISlot)continue;
		UISlot->SlotType = ESlotType::Equip;
		Slots.Emplace(UISlot);
	}
}

void UPDUWEquip::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Init();
}

void UPDUWEquip::Refresh()
{
	if (Player == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			Player = Cast<AProjectDCharacter>(PlayerController->GetPawn());
		}
	}
	for (int i = 0; i < 5; i++)
	{
		Slots[i]->Refresh();
	}
	Player->WeaponMountByEquipment();// ¹«±âÀåÂø
}
