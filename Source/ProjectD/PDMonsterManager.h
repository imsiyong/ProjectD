// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PDMonsterSample.h"
#include "PDMonsterManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDMonsterManager : public UObject
{
	GENERATED_BODY()
private:
	static UPDMonsterManager* InstanceMM;

	TMap<int32, APDMonsterSample*> MonsterMap;

	int32 Key;

	int32 MonsterCount;

public:
	UPDMonsterManager();
	virtual void BeginDestroy() override;
	static UPDMonsterManager* Get();

	APDMonsterSample* FactoryMonsterSpawn(UWorld* World, FVector SpawnLocation, FRotator Rotator, FActorSpawnParameters SpawnParams);

	APDMonsterSample* GetMonster(int32 key);

	void RemoveMonster(int32 key);



};
