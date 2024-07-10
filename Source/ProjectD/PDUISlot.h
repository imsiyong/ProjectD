// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDUISlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDUISlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void Refresh(int32 Index);
	void SetTexture(UTexture2D* texture);
public:
	class AProjectDCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SlotNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Count;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Img_Icon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TB_Count;
};
