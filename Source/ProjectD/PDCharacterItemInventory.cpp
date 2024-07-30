// Fill out your copyright notice in the Description page of Project Settings.


#include "PDCharacterItemInventory.h"

UPDCharacterItemInventory::UPDCharacterItemInventory()
{
	DefaultTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/DownloadAsset/MyTexture/emptytexture.emptytexture")));
	MaxCount = 12;
	Inventory.Empty();
	for (int i = 0; i < MaxCount; i++)
	{
		Inventory.Emplace(FItemInventory(i));
	}
}


void UPDCharacterItemInventory::AddItem(FString name, int32 itemCode, UTexture2D* texture, EInventoryType type, EEquipType equiptype)
{
	int32 index = 0;
	while (1)
	{
		if (index >= MaxCount)return;
		if (Inventory[index].InventoryType.GetValue() == EInventoryType::None)break;
		index++;
	}
	Inventory[index].Name = name;
	Inventory[index].ItemCode = itemCode;
	Inventory[index].Texture = texture;
	Inventory[index].InventoryType = type;
	Inventory[index].EquipType = equiptype;
}

void UPDCharacterItemInventory::AddItemByIndex(int32 index, FString name, int32 itemCode, UTexture2D* texture, EInventoryType type, EEquipType equiptype)
{
	if (index<0 || index >MaxCount)return;
	Inventory[index].Name = name;
	Inventory[index].ItemCode = itemCode;
	Inventory[index].Texture = texture;
	Inventory[index].InventoryType = type;
	Inventory[index].EquipType = equiptype;
}

void UPDCharacterItemInventory::RemoveItemByIndex(int32 index)
{
	if (index<0 || index >MaxCount)return;
	if (Inventory[index].InventoryType != EInventoryType::None)
	{
		Inventory[index].Name = FString(TEXT(""));
		Inventory[index].ItemCode = -1;
		Inventory[index].Texture = DefaultTexture;
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
	ItemCode = -1;
	InventoryType = EInventoryType::None;
	UTexture2D* refTexture= Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/DownloadAsset/MyTexture/emptytexture.emptytexture")));
	Texture = refTexture;
	EquipType = EEquipType::None;
}

FItemInventory::FItemInventory(int32 index)
{
	Index = index;
	Count = 0;
	ItemCode = -1;
	InventoryType = EInventoryType::None;
	UTexture2D* refTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/DownloadAsset/MyTexture/emptytexture.emptytexture")));
	Texture = refTexture;
	EquipType = EEquipType::None;
}
