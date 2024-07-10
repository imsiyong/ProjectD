// Fill out your copyright notice in the Description page of Project Settings.


#include "PDLobbyWidgetStat.h"
#include "PDLobbyStatComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"
#include "PDGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UPDLobbyWidgetStat::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Init();
	BT_Entry = Cast<UButton>(GetWidgetFromName(TEXT("BT_Entry")));
	TB_Entry = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Entry")));
	if (BT_Entry)
	{
		BT_Entry->OnClicked.AddDynamic(this, &UPDLobbyWidgetStat::OnClickEntry);
	}
	LevelName = "ThirdPersonExampleMap";
}

void UPDLobbyWidgetStat::Init()
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	UPDLobbyStatComponent* StatComponent;
	for (auto Widget : Widgets)
	{
		StatComponent = Cast<UPDLobbyStatComponent>(Widget);
		if (!StatComponent)continue;
		StatComponents.Add(StatComponent);
	}
}

void UPDLobbyWidgetStat::OnClickEntry()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}

