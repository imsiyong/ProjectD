// Fill out your copyright notice in the Description page of Project Settings.


#include "PDUWBattleStatus.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void UPDUWBattleStatus::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PB_Hp = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_Hp")));
	PB_Hp->SetPercent(1);
}

void UPDUWBattleStatus::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPDUWBattleStatus::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPDUWBattleStatus::SetHpBar(float hpPercent)
{
	if (!PB_Hp)return;
	PB_Hp->SetPercent(hpPercent);
}
