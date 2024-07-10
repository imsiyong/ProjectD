// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDItemInventory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDItemInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init();

	virtual void NativeOnInitialized() override;

	void Refresh();

	class AProjectDCharacter* Player;

	TArray<class UPDUISlot*> Slots;
};
