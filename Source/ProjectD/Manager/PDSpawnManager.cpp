// Fill out your copyright notice in the Description page of Project Settings.


#include "PDSpawnManager.h"
#include "../PDSpawnPoint.h"
#include "../Monster/PDMonster1.h"
#include "PDNormalMonsterManager.h"

APDSpawnManager* APDSpawnManager::InstanceMM = nullptr;

APDSpawnManager::APDSpawnManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> SD(TEXT("DataTable'/Game/CsvData/SpawnPoint.SpawnPoint'"));
	if (SD.Succeeded())
	{
		SpawnData = SD.Object;
	}
	LoadSpawnData();
}

void APDSpawnManager::BeginDestroy()
{
	Super::BeginDestroy();
}

void APDSpawnManager::SpawnTick(float DeltaSeconds, UWorld* world)
{
	for (auto& temp : MonsterMap)
	{
		temp.Value;
		if (temp.Value->MonsterBasicState == EMonsterBasicState::DEATH)
		{
			TimerMap[temp.Key] += DeltaSeconds;
			if (TimerMap[temp.Key] >= 10.0f)
			{
				TimerMap[temp.Key] = 0.0f;
				FActorSpawnParameters spawnparam;
				temp.Value= UPDNormalMonsterManager::Get()->FactoryMonsterSpawn(world, *SpawnMap.Find(temp.Key), FRotator(0.f, 0.f, 0.f), *PatrolMap.Find(temp.Key), spawnparam);
			}
		}
	}
}

void APDSpawnManager::ResetData()
{
	Key = 0;
	SpawnMap.Empty();
	IsMonsterLived.Empty();
	PatrolMap.Empty();
	MonsterMap.Empty();
	TimerMap.Empty();
}

void APDSpawnManager::Init()
{
	/*ResetData();
	LoadSpawnData();*/
}

void APDSpawnManager::AddMap(FVector spawn, FVector patrol1, FVector patrol2, FVector patrol3, FVector patrol4)
{
	SpawnMap.Add(Key, spawn);
	TArray<FVector> ref;
	ref.Empty();
	if (!patrol1.IsZero())
		ref.Emplace(patrol1);
	if (!patrol2.IsZero())
		ref.Emplace(patrol2);
	if (!patrol3.IsZero())
		ref.Emplace(patrol3);
	if (!patrol4.IsZero())
		ref.Emplace(patrol4);
	PatrolMap.Add(Key, ref);
	IsMonsterLived.Add(Key, false);
	MonsterMap.Add(Key, nullptr);
	TimerMap.Add(Key, 0.0f);
	Key++;
}

void APDSpawnManager::NormalMonsterSpawn(UWorld* world)
{
	FActorSpawnParameters spawnparam;
	for (int i = 0; i < Key; i++)
	{
		if (!*IsMonsterLived.Find(i))
		{
			APDMonster1* temp = UPDNormalMonsterManager::Get()->FactoryMonsterSpawn(world, *SpawnMap.Find(i), FRotator(0.f, 0.f, 0.f), *PatrolMap.Find(i), spawnparam);
			MonsterMap[i] = temp;
		}
	}
}

bool APDSpawnManager::LoadSpawnData()
{
	ResetData();
	if(SpawnData==nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Spawn Data Load Error. : APDSpawnManager.cpp"));
		return false;
	}

	TArray<FSpawnPoint*> Rows;
	SpawnData->GetAllRows<FSpawnPoint>(TEXT("LoadSpawnData"), Rows);

	for (FSpawnPoint* Row : Rows)
	{
		AddMap(Row->SpawnPoint, Row->Patrol1, Row->Patrol2, Row->Patrol3, Row->Patrol4);
	}
	UE_LOG(LogTemp, Log, TEXT("Spawn Data Load Success : APDSpawnManager.cpp"));
	return true;
}

APDSpawnManager* APDSpawnManager::Get()
{
	if (InstanceMM == nullptr)
		InstanceMM = NewObject<APDSpawnManager>();
	return InstanceMM;
}

void APDSpawnManager::Delete()
{
	if (InstanceMM != nullptr)
		InstanceMM = nullptr;
}
