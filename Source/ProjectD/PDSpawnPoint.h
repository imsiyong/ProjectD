// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "PDSpawnPoint.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSpawnPoint : public FTableRowBase
{
	GENERATED_BODY()
public:
	FSpawnPoint() {}
	~FSpawnPoint() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector SpawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector Patrol1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector Patrol2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector Patrol3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector Patrol4;

};
