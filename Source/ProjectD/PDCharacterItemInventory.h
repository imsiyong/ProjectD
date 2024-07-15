// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PDEnum.h"
#include "UObject/NoExportTypes.h"

#include "PDCharacterItemInventory.generated.h"


USTRUCT(BlueprintType)
struct FItemInventory
{
	GENERATED_USTRUCT_BODY()
public:
	FItemInventory();
	FItemInventory(int32 index);

	FItemInventory& operator=(const FItemInventory& ref)
	{
		Index = ref.Index;
		Count = ref.Count;
		Name = ref.Name;
		Texture = ref.Texture;
		InventoryType = ref.InventoryType;
		return *this;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlotType")
		TEnumAsByte<EInventoryType> InventoryType;
};
/**
 *
 */

UCLASS()
class PROJECTD_API UPDCharacterItemInventory : public UObject
{
	GENERATED_BODY()
public:
	UPDCharacterItemInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FItemInventory> Inventory;
public:
	UFUNCTION()
		void AddItemByIndex(int32 index,FString name, UTexture2D* texture, EInventoryType type);
	UFUNCTION()
		void RemoveItemByIndex(int32 index);
	UFUNCTION()
		void SwapItemByIndex(int32 indexA, int32 indexB);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;
};
