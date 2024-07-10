// Fill out your copyright notice in the Description page of Project Settings.


#include "PDUISlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ProjectDCharacter.h"
#include "PDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PDCharacterItemInventory.h"

void UPDUISlot::Refresh(int32 Index)
{
	if (Player == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			Player = Cast<AProjectDCharacter>(PlayerController->GetPawn());
		}
	}
	if (Player && !Player->Inventory.IsValidIndex(Index))
	{
		return;
	}

	UPDCharacterItemInventory* data = Player->Inventory[Index];

	if (data->Texture!=nullptr)
	{
		SetTexture(data->Texture);
	}
	Count = data->Count;
	if (Count <= 1)
	{
		TB_Count->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TB_Count->SetVisibility(ESlateVisibility::Visible);
		TB_Count->SetText(FText::FromString(FString::FromInt(Count)));
	}
}

void UPDUISlot::SetTexture(UTexture2D* texture)
{
	if (texture == nullptr)
		return;
	Img_Icon->SetBrushFromTexture(texture);
}
