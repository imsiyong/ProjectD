// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Monster/PDMonster1.h"
#include "../PDDataSet.h"
#include "PDNormalMonsterManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDNormalMonsterManager : public UObject
{
	GENERATED_BODY()
private:
	static UPDNormalMonsterManager* InstanceNM;

	TMap<int32, APDMonster1*> MonsterMap;

	TMap<int32, FStat*> StatMap;

	int32 Key;

	int32 MonsterCount;
public:
	UPDNormalMonsterManager();
	virtual void BeginDestroy() override;

	void Reset();
	static UPDNormalMonsterManager* Get();

	APDMonster1* FactoryMonsterSpawn(UWorld* World, FVector SpawnLocation, FRotator Rotator, TArray<FVector> patrol, FActorSpawnParameters SpawnParams);

	APDMonster1* GetMonster(int32 key);
	FStat* GetStat(int32 key);

	void RemoveMonster(int32 key);
};
