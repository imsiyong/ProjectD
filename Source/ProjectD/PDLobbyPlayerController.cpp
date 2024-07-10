// Fill out your copyright notice in the Description page of Project Settings.


#include "PDLobbyPlayerController.h"
#include "PDLobbyWidgetStat.h"

APDLobbyPlayerController::APDLobbyPlayerController()
{
	bShowMouseCursor = true;

	ConstructorHelpers::FClassFinder<UPDLobbyWidgetStat> LW(TEXT("WidgetBlueprint'/Game/UMG/SetStatus.SetStatus_C'"));
	if (LW.Succeeded())
	{
		PDLobbyWidgetStat = LW.Class;
	}
}

void APDLobbyPlayerController::SetupInputComponent()
{
	if (PDLobbyWidgetStat != nullptr)
	{
		LobbyWidgetStat = CreateWidget<UPDLobbyWidgetStat>(this, PDLobbyWidgetStat);
		if (LobbyWidgetStat != nullptr)
		{
			LobbyWidgetStat->AddToViewport();
		}
	}
}
