// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDUWBattleStatus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDUWBattleStatus : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* PB_Hp;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* IMG_Character;

	void SetHpBar(float hpPercent);
};
