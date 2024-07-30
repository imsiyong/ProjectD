// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDUWEquip.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDUWEquip : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init();

	virtual void NativeOnInitialized() override;

	void Refresh();

	class AProjectDCharacter* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Img_Background;

	TArray<class UPDUISlot*> Slots;
};
