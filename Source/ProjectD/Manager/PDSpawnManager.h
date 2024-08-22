// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PDSpawnManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDSpawnManager : public AActor
{
	GENERATED_BODY()
private:
	static APDSpawnManager* InstanceMM;

	TMap<int32, FVector> SpawnMap;

	TMap<int32, TArray<FVector>> PatrolMap;

	TMap<int32, bool> IsMonsterLived;

	TMap<int32, class APDMonster1*> MonsterMap;
	
	TMap<int32, float> TimerMap;

	int32 Key;
public:
	APDSpawnManager();

	virtual void BeginDestroy() override;

	void SpawnTick(float DeltaSeconds, UWorld* world);
	void ResetData();
	void Init();
	void AddMap(FVector spawn, FVector patrol1, FVector patrol2, FVector patrol3, FVector patrol4);
	void NormalMonsterSpawn(UWorld* world);
	bool LoadSpawnData();
	static APDSpawnManager* Get();
	static void Delete();

	class UDataTable* SpawnData;
};
