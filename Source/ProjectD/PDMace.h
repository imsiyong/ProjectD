// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PDItem.h"
#include "PDMace.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDMace : public APDItem
{
	GENERATED_BODY()
public:
	APDMace();

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void EquipmentMount() override;

};
