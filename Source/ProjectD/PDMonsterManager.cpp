// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonsterManager.h"
#include "PDMonsterAIController.h"

UPDMonsterManager* UPDMonsterManager::InstanceMM=nullptr;

UPDMonsterManager::UPDMonsterManager()
{
    Key = 0;
    MonsterMap.Empty();
    MonsterCount = 0;
}

void UPDMonsterManager::BeginDestroy()
{
    Super::BeginDestroy();
    if (InstanceMM)
    {
        InstanceMM = nullptr;
    }
}

UPDMonsterManager* UPDMonsterManager::Get()
{
    if (InstanceMM == nullptr)
        InstanceMM = NewObject<UPDMonsterManager>();

    return InstanceMM;
}

APDMonsterSample* UPDMonsterManager::FactoryMonsterSpawn(UWorld* World, FVector SpawnLocation, FRotator Rotator, FActorSpawnParameters SpawnParams)
{
    APDMonsterSample* Monster = nullptr;
    Monster = World->SpawnActor<APDMonsterSample>(APDMonsterSample::StaticClass(), SpawnLocation, Rotator);
    if (Monster)
    {
        APDMonsterAIController* MonsterAI = Cast<APDMonsterAIController>(Monster->GetController());
        if (MonsterAI)
        {
            MonsterAI->Init();
        }
        if (!MonsterMap.Contains(Key))
        {
            Monster->MonsterCode = Key;
            MonsterMap.Emplace(Key, Monster);
            Key++;
            MonsterCount++;
            return Monster;
        }
    }
    return nullptr;
}

APDMonsterSample* UPDMonsterManager::GetMonster(int32 key)
{
    if (!MonsterMap.Contains(key))
        return nullptr;
    return MonsterMap[key];
}

void UPDMonsterManager::RemoveMonster(int32 key)
{
    if (!MonsterMap.Contains(key))
        return;
    MonsterMap.Remove(key);
    MonsterCount--;
}
