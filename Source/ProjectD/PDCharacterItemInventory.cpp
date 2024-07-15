// Fill out your copyright notice in the Description page of Project Settings.


#include "PDCharacterItemInventory.h"

UPDCharacterItemInventory::UPDCharacterItemInventory()
{
	MaxCount = 12;
	Inventory.Empty();
	for (int i = 0; i < MaxCount; i++)
	{
		Inventory.Emplace(FItemInventory(i));
	}
}


void UPDCharacterItemInventory::AddItemByIndex(int32 index, FString name, UTexture2D* texture, EInventoryType type)
{
	if (index<0 || index >MaxCount)return;
	Inventory[index].Name = name;
	Inventory[index].Texture = texture;
	Inventory[index].InventoryType = type;
}

void UPDCharacterItemInventory::RemoveItemByIndex(int32 index)
{
	if (index<0 || index >MaxCount)return;
	if (Inventory[index].InventoryType != EInventoryType::None)
	{
		Inventory[index].Name = FString(TEXT(""));
		Inventory[index].Texture = nullptr;
		Inventory[index].InventoryType = EInventoryType::None;
	}
}

void UPDCharacterItemInventory::SwapItemByIndex(int32 indexA, int32 indexB)
{
	FItemInventory ref = FItemInventory(0);
	ref = Inventory[indexA];
	Inventory[indexA] = Inventory[indexB];
	Inventory[indexB] = ref;
}

FItemInventory::FItemInventory()
{
	Index = 0;
	Count = 0;
	InventoryType = EInventoryType::None;
	UTexture2D* refTexture= Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/DownloadAsset/MyTexture/emptytexture.emptytexture")));
	Texture = refTexture;
}

FItemInventory::FItemInventory(int32 index)
{
	Index = index;
	Count = 0;
	InventoryType = EInventoryType::None;
	UTexture2D* refTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/DownloadAsset/MyTexture/emptytexture.emptytexture")));
	Texture = refTexture;
}
