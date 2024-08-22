// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PDDataSet.h"
#include "PDGameInstance.generated.h"


UCLASS()
class PROJECTD_API UPDGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPDGameInstance();

	TArray<FStat*>  PlayerStatArray;
	TArray<FStat*>	MonsterStatArray;

	void PlayerStatArrayAdd();
	void MonsterStatArrayAdd();
	
	int32 PlayerCode;
	int32 MonsterCode;

	TArray<FStat*> GetPlayerStatArray() { return PlayerStatArray; }
	TArray<FStat*> GetMonsterStatArray() { return MonsterStatArray; }

	class UDataTable* ItemData; 
public:
	FStat* PlayerStat;
	FStat* GetPlayerStat();

	class UPDCharacterItemInventory* Inventory;
	UPDCharacterItemInventory* GetPlayerInventory();

	class UPDCharacterEquip* Equip;
	UPDCharacterEquip* GetPlayerEquip();
};
