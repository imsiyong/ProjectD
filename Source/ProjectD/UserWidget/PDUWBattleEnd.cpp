// Fill out your copyright notice in the Description page of Project Settings.


#include "PDUWBattleEnd.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>

void UPDUWBattleEnd::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BT_End = Cast<UButton>(GetWidgetFromName(TEXT("BT_End")));
	TB_End = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_End")));
	if (BT_End)
	{
		BT_End->OnClicked.AddDynamic(this, &UPDUWBattleEnd::OnClickEnd);
	}
	LevelName = "CharacterSetting";
}

void UPDUWBattleEnd::OnClickEnd()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}
