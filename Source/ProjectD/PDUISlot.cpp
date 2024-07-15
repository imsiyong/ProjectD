// Fill out your copyright notice in the Description page of Project Settings.


#include "PDUISlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ProjectDCharacter.h"
#include "PDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PDCharacterItemInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PDUWDrag.h"
#include "Components/CanvasPanelSlot.h"

void UPDUISlot::Refresh()
{
	if (Player == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			Player = Cast<AProjectDCharacter>(PlayerController->GetPawn());
		}
	}
	if (!Player || !Player->Inventory22->Inventory.IsValidIndex(SlotNum))return;
	FItemInventory data = Player->Inventory22->Inventory[SlotNum];

	if (data.Texture != nullptr)
	{
		SetTexture(data.Texture);
	}

	Count = data.Count;
	if (Count <= 1)
	{
		TB_Count->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TB_Count->SetVisibility(ESlateVisibility::Visible);
		TB_Count->SetText(FText::FromString(FString::FromInt(Count)));
	}

	SlotType = ESlotType::Inventory;
}

void UPDUISlot::SetTexture(UTexture2D* texture)
{
	if (texture == nullptr)
		return;
	Img_Icon->SetBrushFromTexture(texture);
}

FReply UPDUISlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("left mouse button click"));

		switch (SlotType)
		{
		case ESlotType::None:
			return reply.NativeReply;
			break;
		case ESlotType::Inventory:
			reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			break;
		default:
			break;
		}
	}

	return reply.NativeReply;
}

void UPDUISlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (OutOperation == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("drag on"));
		UPDUWDrag* drag = NewObject<UPDUWDrag>();
		OutOperation = drag;
		drag->index = this->SlotNum;

		if (DragSlot != nullptr)
		{
			UPDUISlot* Visual = CreateWidget<UPDUISlot>(Cast<APlayerController>(Player->Controller), DragSlot);
			Visual->SlotType = this->SlotType;
			Visual->SlotNum = this->SlotNum;
			Visual->Player = this->Player;
			Visual->Refresh();
			UCanvasPanelSlot* Scale = Cast<UCanvasPanelSlot>(Visual->Slot);
			if (Scale)
			{
				/*FWidgetTransform Transform = Scale->Get
				Transform.Scale = NewScale;
				Scale->SetRenderTransform(Transform);*/
			}
			drag->DefaultDragVisual = Visual;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("drag failed"));
	}
}

bool UPDUISlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UPDUWDrag* Drag = Cast<UPDUWDrag>(InOperation);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("drag drop End"));
	if (Drag !=nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Swap STart"));
		Player->SwapInventory(SlotNum, Drag->index);
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("NativeOnDrop : error"));
		return false;
	}
}
