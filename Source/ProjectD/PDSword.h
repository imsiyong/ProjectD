// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PDItem.h"
#include "PDSword.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDSword : public APDItem
{
	GENERATED_BODY()
public:
	APDSword();

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
