// Fill out your copyright notice in the Description page of Project Settings.


#include "PDGameInstance.h"
#include "ItemData.h"

UPDGameInstance::UPDGameInstance()
{
	PlayerCode = 0;
	MonsterCode = 0;
	static ConstructorHelpers::FObjectFinder<UDataTable> IT(TEXT("DataTable'/Game/CsvData/ItemData.ItemData'"));
	if (IT.Succeeded())
	{
		ItemData = IT.Object;
	}
	
}

void UPDGameInstance::PlayerStatArrayAdd()
{
	class FStat* ref = new FStat(PlayerCode++);
	PlayerStatArray.Add(ref);
}

void UPDGameInstance::MonsterStatArrayAdd()
{
	class FStat* ref = new FStat(MonsterCode++);
	MonsterStatArray.Add(ref);
}
