// Fill out your copyright notice in the Description page of Project Settings.


#include "PDNormalMonsterManager.h"
#include "../Monster/PDMonster1AIController.h"

UPDNormalMonsterManager* UPDNormalMonsterManager::InstanceNM = nullptr;

UPDNormalMonsterManager::UPDNormalMonsterManager()
{
	Reset();
}

void UPDNormalMonsterManager::BeginDestroy()
{
	Super::BeginDestroy();
	if (InstanceNM)
	{
		InstanceNM = nullptr;
	}
}

void UPDNormalMonsterManager::Reset()
{
	Key = 0;
	MonsterMap.Empty();
	StatMap.Empty();
	MonsterCount = 0;
}

UPDNormalMonsterManager* UPDNormalMonsterManager::Get()
{
	if (InstanceNM == nullptr)
		InstanceNM = NewObject<UPDNormalMonsterManager>();
	return InstanceNM;
}

APDMonster1* UPDNormalMonsterManager::FactoryMonsterSpawn(UWorld* World, FVector SpawnLocation, FRotator Rotator, TArray<FVector> patrol, FActorSpawnParameters SpawnParams)
{
	APDMonster1* TempMonster = nullptr;
	TempMonster = World->SpawnActor<APDMonster1>(APDMonster1::StaticClass(), SpawnLocation, Rotator);
	if (TempMonster)
	{
		//Spawn AIController
		APDMonster1AIController* TempMonsterAI = Cast<APDMonster1AIController>(TempMonster->GetController());
		if (TempMonsterAI)
		{
			TempMonsterAI->Init();
			TempMonsterAI->SetPoint(FVector(-400.f, 1100.f, 250.f), patrol);
		}
		if (!MonsterMap.Contains(Key))
		{
			TempMonster->MonsterCode = Key;
			TempMonster->Stat = new FStat(Key);
			MonsterMap.Emplace(Key, TempMonster);
			StatMap.Emplace(Key, TempMonster->Stat);
			Key++;
			MonsterCount++;
			return TempMonster;
		}
	}
	return nullptr;
}

APDMonster1* UPDNormalMonsterManager::GetMonster(int32 key)
{
	if (!MonsterMap.Contains(key))
		return nullptr;

	return MonsterMap[key];
}

FStat* UPDNormalMonsterManager::GetStat(int32 key)
{
	if (!StatMap.Contains(key))
		return nullptr;
	return StatMap[key];
}

void UPDNormalMonsterManager::RemoveMonster(int32 key)
{
	if (!MonsterMap.Contains(key))
		return;
	MonsterMap.Remove(key);
	MonsterCount--;
	//Should I decrease the key value?
}
