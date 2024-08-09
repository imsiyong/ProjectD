// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PDMonsterBase.h"
#include "PDMonster1.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDMonster1 : public APDMonsterBase
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APDMonster1();

	void Init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

public:
	virtual void DeathStart() override;
	virtual void DeathEnd() override;

	class UPDMonster1Instance* Monster1Instance;

	void BasicAttackStart();
	void JumpAttackStart();
	void AttackEnd();
	void AttackCheck();

	void ReactStart();
	void FindStart();

	void SprintStart();
	void SprintStop();

	void WeaponDrop();
};
