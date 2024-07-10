// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDEnum.h"
#include "PDLobbyStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDLobbyStatComponent : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void Init();
	void Refresh();
	void SetStat(float val);
	UFUNCTION()
	void OnButtonClickedPlus();
	UFUNCTION()
	void OnButtonClickedMinus();
	
	class FStat* CharacterStat;
	float DetailStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BT_Plus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BT_Minus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Text_Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Text_Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterStatType")
		TEnumAsByte<ECharacterStatType> CharacterStatType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StatWeight;

};
