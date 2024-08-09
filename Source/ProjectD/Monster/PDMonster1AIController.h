// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../PDEnum.h"
#include "../PDDataSet.h"
#include "PDMonster1AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDMonster1AIController : public AAIController
{
	GENERATED_BODY()
public:
	APDMonster1AIController();
	void Init();
	void SetPoint(FVector spawnPoint, TArray<FVector> destination);
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void Tick(float DeltaTime) override;

	APawn* PlayerPawn;
	class APDMonster1* MonsterPawn;
	ENormalMonsterActionState MonsterActionState;
	FVector SpawnPoint;
	TArray<FVector> Destination;

	bool EqualFloatNearby(float actorDest, float dest);
	bool EqualActorXYNearby(AActor* actor, FVector dest);
	bool IsOutOfBound();
	
	void FSMState();

	void ActorSpawn();
	void Patrol();
	void Tracking();
	void Attack();
};
