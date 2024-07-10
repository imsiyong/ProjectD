// Fill out your copyright notice in the Description page of Project Settings.


#include "PDLobbyStatComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PDGameInstance.h"


void UPDLobbyStatComponent::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (UGameInstance* GameInstace = GetGameInstance())
	{
		UPDGameInstance* PDGameInstance = Cast<UPDGameInstance>(GameInstace);
		if (PDGameInstance)
		{
			if (PDGameInstance->GetPlayerStatArray().Num() == 0)
			{
				PDGameInstance->PlayerStatArrayAdd();
				CharacterStat = PDGameInstance->GetPlayerStatArray().Top();
			}
			else
			{
				CharacterStat = PDGameInstance->GetPlayerStatArray().Top();
			}
		}
	}
	BT_Plus = Cast<UButton>(GetWidgetFromName(TEXT("BT_Plus")));
	BT_Minus = Cast<UButton>(GetWidgetFromName(TEXT("BT_Minus")));
	if (BT_Plus)
	{
		BT_Plus->OnClicked.AddDynamic(this, &UPDLobbyStatComponent::OnButtonClickedPlus);
	}
	if (BT_Minus)
	{
		BT_Minus->OnClicked.AddDynamic(this, &UPDLobbyStatComponent::OnButtonClickedMinus);
	}
	Text_Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Count")));
	Text_Stat = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Stat")));

	Init();
	Refresh();
}

void UPDLobbyStatComponent::Init()
{
	switch (CharacterStatType)
	{
	case ECharacterStatType::Atk:
		Text_Stat->SetText(FText::FromString("Atk"));
		DetailStat = CharacterStat->Atk;
		break;
	case ECharacterStatType::AtkSpeed:
		Text_Stat->SetText(FText::FromString("AtkSpeed"));
		DetailStat = CharacterStat->AtkSpeed;
		break;
	case ECharacterStatType::Def:
		Text_Stat->SetText(FText::FromString("Def"));
		DetailStat = CharacterStat->Def;
		break;
	case ECharacterStatType::Hp:
		Text_Stat->SetText(FText::FromString("Hp"));
		DetailStat = CharacterStat->MaxHp;
		break;
	default:
		break;
	}
}

void UPDLobbyStatComponent::Refresh()
{
	Text_Count->SetText(FText::AsNumber(DetailStat));
}

void UPDLobbyStatComponent::SetStat(float val)
{
	switch (CharacterStatType)
	{
	case ECharacterStatType::Atk:
		CharacterStat->Atk += (val*StatWeight);
		DetailStat = CharacterStat->Atk;
		break;
	case ECharacterStatType::AtkSpeed:
		CharacterStat->AtkSpeed += (val * StatWeight);
		DetailStat = CharacterStat->AtkSpeed;
		break;
	case ECharacterStatType::Def:
		CharacterStat->Def += (val * StatWeight);
		DetailStat = CharacterStat->Def;
		break;
	case ECharacterStatType::Hp:
		CharacterStat->MaxHp += (val * StatWeight);
		CharacterStat->CurHp += (val * StatWeight);
		DetailStat = CharacterStat->MaxHp;
		break;
	default:
		break;
	}
}

void UPDLobbyStatComponent::OnButtonClickedPlus()
{
	SetStat(1.0f);
	Refresh();
	UE_LOG(LogTemp, Log, TEXT("plus %f"), DetailStat);
}

void UPDLobbyStatComponent::OnButtonClickedMinus()
{
	SetStat(-1.0f);
	Refresh();
	UE_LOG(LogTemp, Log, TEXT("minus %f"), DetailStat);
}
