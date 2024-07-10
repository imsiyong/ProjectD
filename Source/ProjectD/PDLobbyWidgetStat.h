// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDLobbyWidgetStat.generated.h"


class UPDLobbyStatComponent;
/**
 * 
 */
UCLASS()
class PROJECTD_API UPDLobbyWidgetStat : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	void Init();
	
	TArray<UPDLobbyStatComponent*> StatComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BT_Entry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TB_Entry;
	UFUNCTION()
		void OnClickEntry();
	

public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString LevelName;
};
