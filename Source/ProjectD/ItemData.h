// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"


USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemData() {}
	~FItemData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
		int32 ItemCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
		int32 EquipType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
		float Atk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
		float AtkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
		float AtkRange;
};
