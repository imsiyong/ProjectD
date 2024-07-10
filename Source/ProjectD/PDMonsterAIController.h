// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PDEnum.h"
#include "PDDataSet.h"
#include "PDMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	APDMonsterAIController();

	virtual void PostInitializeComponents() override;

	void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	void Tick(float DeltaTime);

	void Init();

	APlayerController* MSPlayerController;
	APawn* PlayerPawn;
	class APDMonsterSample* MonsterPawn;
	EMonsterActionState MonsterActionState;
	FVector Destination;

	bool EqualFloatNearby(float actorDest, float dest);
	bool EqualActorXYNearby(AActor* actor, FVector dest);

	void FSMState();

	void SetDest();
	void MoveToDest();
	void CheckDist();
	void CheckField();
	void MoveToCenter();
	void Attack();
};
