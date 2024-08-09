// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PDEnum.h"
#include "GameFramework/Character.h"
#include "PDMonsterBase.generated.h"

UCLASS()
class PROJECTD_API APDMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APDMonsterBase();

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
	EMonsterBasicState MonsterBasicState;
	EMonsterGrade MonsterGrade;

	class FStat* Stat;
	int32 MonsterCode;
	bool IsAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Property")
	float DeathDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Property")
	float SprintMultiplier;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void DeathStart();
	virtual void DeathEnd();
};
