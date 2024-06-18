// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PDEnum.h"
#include "PDMonsterSample.generated.h"

UCLASS()
class PROJECTD_API APDMonsterSample : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APDMonsterSample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	EMonsterBasicState BasicState;
	bool IsAttack;
	float DeathEventDelayTime;
	class FStat* Stat;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Character Movement:Walking")
	float SprintSpeedMuti;
	

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void AttackStart();
	void AttackEnd();

	void AttackCheck();

	void DeathStart();
	void DeathEnd();

	void SprintStart();
	void SprintStop();

	void WeaponDrop();
};
