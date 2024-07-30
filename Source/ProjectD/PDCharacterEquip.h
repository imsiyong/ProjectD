// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "PDEnum.h"
#include "UObject/NoExportTypes.h"
#include "PDCharacterEquip.generated.h"

USTRUCT(BlueprintType)
struct FEquip
{
	GENERATED_USTRUCT_BODY()
public:
	FEquip();

	FEquip& operator=(const FEquip& ref)
	{
		Name = ref.Name;
		ItemCode = ref.ItemCode;
		Texture = ref.Texture;
		Has = ref.Has;
		EquipType = ref.EquipType;
		return *this;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Has;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlotType")
		TEnumAsByte<EEquipType> EquipType;
};


/**
 * 
 */
UCLASS()
class PROJECTD_API UPDCharacterEquip : public UObject
{
	GENERATED_BODY()
public:
	UPDCharacterEquip();

	void AddEquipByType(FString name, int32 itemCode, UTexture2D* texture, EEquipType equipType);
	void AddEquipByIndex(FString name, int32 itemCode, UTexture2D* texture, int32 index);

	void RemoveEquipByType(EEquipType equipType);
	void RemoveEquipByIndex(int32 index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DefaultTexture;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equip")
		TArray<FEquip> Equipments;
};
