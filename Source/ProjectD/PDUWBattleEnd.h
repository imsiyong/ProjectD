// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDUWBattleEnd.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDUWBattleEnd : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BT_End;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TB_End;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString LevelName;

	UFUNCTION()
		void OnClickEnd();
};
