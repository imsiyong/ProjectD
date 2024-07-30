// Fill out your copyright notice in the Description page of Project Settings.


#include "PDCharacterEquip.h"

UPDCharacterEquip::UPDCharacterEquip()
{
	DefaultTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/DownloadAsset/MyTexture/emptytexture.emptytexture")));
	Equipments.Empty();
	for (int32 i = 0; i < 5; i++)
	{
		FEquip ref = FEquip();
		ref.EquipType = static_cast<EEquipType>(i);
		ref.Texture = DefaultTexture;
		Equipments.Emplace(ref);
	}
}

FEquip::FEquip()
{
	Name = FString(TEXT(""));
	ItemCode = -1;
	Texture = nullptr;
	EquipType = EEquipType::None;
	Has = false;
}

void UPDCharacterEquip::AddEquipByType(FString name,int32 itemCode, UTexture2D* texture, EEquipType equipType)
{
	int32 index = static_cast<int32>(equipType);
	Equipments[index].Name = name;
	Equipments[index].ItemCode = itemCode;
	Equipments[index].Texture = texture;
	Equipments[index].Has = true;
}

void UPDCharacterEquip::AddEquipByIndex(FString name, int32 itemCode, UTexture2D* texture, int32 index)
{
	Equipments[index].Name = name;
	Equipments[index].ItemCode = itemCode;
	Equipments[index].Texture = texture;
	Equipments[index].Has = true;
}

void UPDCharacterEquip::RemoveEquipByType(EEquipType equipType)
{
	int32 index = static_cast<int32>(equipType);
	Equipments[index].Name = FString(TEXT(""));
	Equipments[index].ItemCode = -1;
	Equipments[index].Texture = DefaultTexture;
	Equipments[index].Has = false;
}

void UPDCharacterEquip::RemoveEquipByIndex(int32 index)
{
	Equipments[index].Name = FString(TEXT(""));;
	Equipments[index].ItemCode = -1;
	Equipments[index].Texture = DefaultTexture;
	Equipments[index].Has = false;
}

