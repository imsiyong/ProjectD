// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PDCharacterItemInventory.generated.h"

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
		int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;
};
