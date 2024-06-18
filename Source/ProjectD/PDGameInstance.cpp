// Fill out your copyright notice in the Description page of Project Settings.


#include "PDGameInstance.h"

UPDGameInstance::UPDGameInstance()
{
	PlayerCode = 0;
	MonsterCode = 0;
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
